----------------------------------------------------------------------------------
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity instruction_decoder is
	Port(clk : in std_logic;			
			activate_decoder : in std_logic := '0';
			byte_code_length : in std_logic_vector(31 downto 0);
			mem_rd_addr : out std_logic_vector(9 downto 0);
			mem_rd_data : in std_logic_vector(31 downto 0);
			senddata : out std_logic_vector(7 downto 0) := (others => 'Z');
			do_write : out std_logic := '0';
			busy_send : in std_logic;
			lamp : out  STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
			decoder_complete : out std_logic := '0');
end instruction_decoder;

architecture Behavioral of instruction_decoder is
	type element_type is ( Int, Float, Str, Add, Sub, Div, Mul );		
	type decoder_state is ( Instruction, Native_fn_print, None, Decode_expression );
	
	function encode_element_type(el_type : element_type) return std_logic_vector is
		begin
		if (el_type = Int) then
			return X"12";
		elsif (el_type = Str) then
			return X"11";
		elsif (el_type = Float) then
			return X"10";
		end if;
		return X"00";
	end encode_element_type;
	
	function decode_expression_type(raw_type : in std_logic_vector(7 downto 0)) return element_type is
		begin
		if (raw_type = X"12") then
			return Int;
		elsif (raw_type = X"11") then
			return Str;
		elsif (raw_type = X"10") then
			return Float;
		elsif (raw_type = X"0A") then
			return Add;
		elsif (raw_type = X"0B") then
			return Sub;
		elsif (raw_type = X"0C") then
			return Mul;
		elsif (raw_type = X"0D") then
			return Div;
		end if;
		return Int;
	end decode_expression_type;
	
	signal instruction_state : decoder_state := Instruction;
	signal sub_decoder_state : decoder_state := None;	
	signal expression_result : std_logic_vector(31 downto 0);
	signal expression_type : element_type;
begin
	process(clk)
		variable currentPoint : natural := 0;
		variable lhs_int : integer;
		variable rhs_int : integer;		
		variable decoding_completed : std_logic := '0';
		variable writing : std_logic := '0';
		variable stage_id : natural :=0;
		variable expression_decode_stage_id : natural :=0;
		variable specific_type : element_type;
		variable lhs_type : element_type;
		variable rhs_type : element_type;
		variable wait_mem : std_logic := '0';
	begin
		if (rising_edge(clk)) then 			
			if (activate_decoder = '1' AND decoding_completed = '0') then			
				if (busy_send = '0' AND writing = '0' AND wait_mem='0') then				
					decoder_complete <= '0';
					if (sub_decoder_state = None) then
						if (instruction_state = Instruction) then
							if (mem_rd_data(7 downto 0) = X"01") then
								-- STOP command
								decoding_completed:='1';
								decoder_complete <= '1';						
							elsif (mem_rd_data(7 downto 0) = X"23") then
								-- Native function call command, now test what type of fn
								if (mem_rd_data(15 downto 8) = X"22") then
									-- Print command
									instruction_state <= Native_fn_print;
									currentPoint:=currentPoint+3;
									senddata <= X"03";
									do_write <= '1';
									writing:='1';
									stage_id:=0;
								end if;
							end if;
							currentPoint:=currentPoint+1;
						elsif (instruction_state = Native_fn_print) then
							if (stage_id = 0) then
								specific_type:=decode_expression_type(mem_rd_data(7 downto 0));	
								--lamp <= mem_rd_data(7 downto 0);								
								stage_id:=1;
								if (specific_type = Int OR specific_type = Float OR specific_type = Str) then
									senddata <= mem_rd_data(7 downto 0);
									do_write <= '1';
									writing:='1';
								else
									sub_decoder_state <= Decode_expression;
									expression_decode_stage_id:=0;
									wait_mem:='1'; -- Need to pause a cycle for memory to catch up as 2 cycles for mem (addr & then value back)
								end if;
								currentPoint:=currentPoint+1;
							else								
								if (specific_type = Int OR specific_type = Float) then								
									senddata <= mem_rd_data(7 downto 0); -- Same entry as incrementing current point each time
									if (stage_id = 4) then instruction_state <= Instruction; end if; -- Stop after 4 (sending 4 bytes back)
									stage_id:=stage_id+1;
									currentPoint:=currentPoint+1;
								elsif (specific_type = Str) then
									senddata <= mem_rd_data(7 downto 0);
									if (mem_rd_data(7 downto 0) = X"00") then instruction_state <= Instruction; end if; -- Stop after null terminator
									currentPoint:=currentPoint+1;
								else
									if (stage_id = 1) then
										senddata <= encode_element_type(expression_type);										
									elsif (stage_id = 2) then
										senddata <= expression_result(7 downto 0);
									elsif (stage_id = 3) then
										senddata <= expression_result(15 downto 8);
									elsif (stage_id = 4) then
										senddata <= expression_result(23 downto 16);
									elsif (stage_id = 5) then
										senddata <= expression_result(31 downto 24);
										instruction_state <= Instruction;
									end if;
									stage_id:=stage_id+1;
								end if;
								do_write <= '1';
								writing:='1';
							end if;							
						end if;
					elsif (sub_decoder_state = Decode_expression) then
						-- type not working some how (was not firing back on the rhs_type)
						if (expression_decode_stage_id = 0) then
							lhs_type:=decode_expression_type(mem_rd_data(7 downto 0));
							wait_mem:='1'; -- Will pause for a cycle for memory value to catch up (needed as not working a cycle ahead)
						elsif (expression_decode_stage_id = 1) then
							if (lhs_type = Int) then								
								lhs_int:=to_integer(signed(mem_rd_data));
								currentPoint:=currentPoint+3;
								wait_mem:='1';
							end if;
						elsif (expression_decode_stage_id = 2) then
							rhs_type:=decode_expression_type(mem_rd_data(7 downto 0));
							wait_mem:='1';
						elsif (expression_decode_stage_id = 3) then
							if (rhs_type = Int) then
								rhs_int:=to_integer(signed(mem_rd_data));
								currentPoint:=currentPoint+3;
								if (lhs_type = Int) then
									expression_type <= Int;
									if (specific_type = Add) then									
										expression_result<=std_logic_vector(to_signed(lhs_int + rhs_int, expression_result'length));
									end if;
								end if;							
							end if;
							sub_decoder_state <= None;
						end if;
						expression_decode_stage_id:=expression_decode_stage_id+1;
						currentPoint:=currentPoint+1;
					end if;
					-- lamp <= std_logic_vector(to_unsigned(cc, 8));
					--lamp <= byte_code_length(7 downto 0); --std_logic_vector(to_unsigned(currentPoint, 8)); --"01011010";	
					mem_rd_addr <= std_logic_vector(to_unsigned(currentPoint, mem_rd_addr'length));
					if (currentPoint >= to_integer(unsigned(byte_code_length))) then	
						-- Commented for now as will squash sending data via RS232
						--decoding_completed:='1';
						--decoder_complete <= '1';
					end if;		
				elsif (busy_send = '1' AND writing = '1') then					
					do_write <= '0';
					writing:='0';
				elsif (wait_mem = '1') then
					wait_mem:='0';
				end if;
			elsif (activate_decoder = '0') then
				decoder_complete<='0';
				decoding_completed:='0';
				currentPoint:=0;
				mem_rd_addr <= std_logic_vector(to_unsigned(currentPoint, mem_rd_addr'length));
			end if;			
		end if;
	end process;
end Behavioral;

