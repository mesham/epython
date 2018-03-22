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

entity bootstrapper is
	Port(clk : in STD_LOGIC;			
			activate_bootstrapper : in STD_LOGIC := '0';
			epython_host_data : in STD_LOGIC_VECTOR (7 downto 0);
			epython_host_got_data : in STD_LOGIC;
			mem_wr_data : out std_logic_vector(7 downto 0);
			mem_wr_addr : out std_logic_vector(9 downto 0);
			mem_wr_en : out std_logic;
			bootstrapper_complete : inout STD_LOGIC := '0';
			byte_code_length_signal : out std_logic_vector(31 downto 0) := (others => '0'));
end bootstrapper;

architecture Behavioral of bootstrapper is
	signal byte_len_signal : std_logic_vector(31 downto 0) := (others => '0');
	type boot_state is ( Idle, Waiting, PartialLen, FinishedLen, WaitingCode, CompletedBoot );	
	signal state_reg : boot_state := Idle;
begin
	process(clk)		
		variable byte_code_length : natural ;
		variable place_index : natural := 0;
		variable received_byte_code : natural := 0;
	begin	
		if (rising_edge(clk)) then
			if (activate_bootstrapper = '1' AND bootstrapper_complete='0') then
				if (state_reg = FinishedLen) then
					byte_code_length:=to_integer(unsigned(byte_len_signal));
					byte_code_length_signal <= byte_len_signal;
					state_reg <= WaitingCode;				
				end if;				
				if (epython_host_got_data = '1') then
					if (state_reg = Idle) then
						byte_len_signal(31 downto 24) <= epython_host_data;				
						state_reg <= PartialLen;
						place_index:=1;						
					elsif (state_reg = PartialLen) then
						if (place_index = 1) then
							byte_len_signal(23 downto 16) <= epython_host_data;	
						elsif (place_index = 2) then
							byte_len_signal(15 downto 8) <= epython_host_data;	
						elsif (place_index = 3) then
							byte_len_signal(7 downto 0) <= epython_host_data;	
							state_reg <= FinishedLen;
						end if;							
						place_index:=place_index+1;
					elsif (state_reg = WaitingCode OR state_reg = FinishedLen) then
						mem_wr_data <= epython_host_data;						
						mem_wr_en <= '1';
						received_byte_code:=received_byte_code+1;
						mem_wr_addr <= std_logic_vector(to_unsigned(received_byte_code-1, mem_wr_addr'length));
						if (received_byte_code >= byte_code_length) then
							state_reg <= Idle;
							bootstrapper_complete <= '1';
							byte_code_length:=0;
							received_byte_code:=0;
							place_index:=0;							
						end if;
					end if;			
				end if;
			elsif (activate_bootstrapper = '0') then
				bootstrapper_complete<='0';	
				mem_wr_en <= '0';
			end if;
		end if;
	end process;
end Behavioral;

