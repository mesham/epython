----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:07:18 12/19/2017 
-- Design Name: 
-- Module Name:    epython - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
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

entity epython is
	Port(clk : in STD_LOGIC;
			tx : out STD_LOGIC;			
			rx : in STD_LOGIC;
			lamp : out  STD_LOGIC_VECTOR (7 downto 0) := "00000000" );
end epython;

architecture Behavioral of epython is
	component rs232_receiver
		Generic(frequency : natural;
               baud : natural);
		Port(clk : in std_logic;
				rx : in std_logic;          
				data :out std_logic_vector(7 downto 0);
				data_strobe : out std_logic);
	end component;
	
	component rs232_sender
		Port(clk : in std_logic;
				databyte : in std_logic_vector(7 downto 0);     
				do_write : in std_logic;
				busy_out : out std_logic;
				tx : out std_logic);
	end component;
	
	component bootstrapper		
		Port(clk : in std_logic;	
				activate_bootstrapper : in STD_LOGIC;
				epython_host_data : out STD_LOGIC_VECTOR (7 downto 0);
				epython_host_got_data : out STD_LOGIC;
				mem_wr_data : out std_logic_vector(7 downto 0);
				mem_wr_addr : out std_logic_vector(9 downto 0);
				mem_wr_en : out std_logic;
				bootstrapper_complete : inout std_logic;
				byte_code_length_signal : out std_logic_vector(31 downto 0));
	end component;
	
	component instruction_decoder
		Port(clk : in STD_LOGIC;			
			activate_decoder : in STD_LOGIC;		
			byte_code_length : in std_logic_vector(31 downto 0);
			mem_rd_addr : out std_logic_vector(9 downto 0);
			mem_rd_data : in std_logic_vector(31 downto 0);
			senddata : out std_logic_vector(7 downto 0);
			do_write : out std_logic;
			lamp : out  STD_LOGIC_VECTOR (7 downto 0);
			busy_send : in std_logic;
			decoder_complete : out STD_LOGIC);
	end component;
	
	component memory_manager
		port (clk : in std_logic;
				data_in : in std_logic_vector(7 downto 0);
				wr_addr : in std_logic_vector(9 downto 0);
				wr_en : in std_logic;
				
				data_out : out std_logic_vector(31 downto 0);
				rd_addr : in std_logic_vector(9 downto 0));
	end component;
	
	signal got_data : std_logic;
	signal busy_send : std_logic;	
	signal my_do_write : std_logic := '0';	
	signal id_do_write : std_logic := '0';	
	signal do_write : std_logic := '0';	
	
	signal id_lamp : STD_LOGIC_VECTOR (7 downto 0) := "00000000";
	signal my_lamp : STD_LOGIC_VECTOR (7 downto 0);	
	
	signal my_senddata : std_logic_vector(7 downto 0) := "00000000";
	signal id_senddata : std_logic_vector(7 downto 0) := "00000000";
	signal senddata : std_logic_vector(7 downto 0) := "00000000";
	signal recvdata : std_logic_vector(7 downto 0) := (others => '0');
	
	signal mem_data_in : std_logic_vector(7 downto 0);
	signal mem_wr_addr : std_logic_vector(9 downto 0) := (others => '0');
	signal mem_wr_en : std_logic;
	signal mem_rd_addr : std_logic_vector(9 downto 0) := (others => '0');          
	signal mem_data_out : std_logic_vector(31 downto 0);
	
	signal byte_code_length : std_logic_vector(31 downto 0) := (others => '0');
	
	signal start_bootstrapper : std_logic := '0';
	signal booting_completed : std_logic := '0';
	
	signal activate_decoder : std_logic := '0';
	signal decoder_complete : std_logic := '0';
	
	type epython_state is ( Idle, Booting, Execute, Executing );	
	signal state_reg : epython_state := Idle;	
begin

	Inst_sender: rs232_sender 
		PORT MAP(clk => clk,
					databyte => senddata,
					busy_out => busy_send,
					do_write => do_write,
					tx => tx);

	Inst_receiver: rs232_receiver 
		GENERIC MAP (frequency => 32000000, baud => 9600) 
		PORT MAP(clk => clk,
					rx => rx,
					data => recvdata,
					data_strobe => got_data);
		
	Inst_bootstrapper: bootstrapper 
		PORT MAP(clk => clk,
					activate_bootstrapper => start_bootstrapper,
					epython_host_data => recvdata,
					epython_host_got_data => got_data,
					mem_wr_data => mem_data_in,
					mem_wr_addr => mem_wr_addr,
					mem_wr_en => mem_wr_en,
					bootstrapper_complete => booting_completed,
					byte_code_length_signal => byte_code_length);	
					
	Inst_instruction_decoder: instruction_decoder
		PORT MAP(clk => clk,
					activate_decoder => activate_decoder,
					byte_code_length => byte_code_length,
					mem_rd_addr => mem_rd_addr,
					mem_rd_data => mem_data_out,
					senddata => id_senddata,
					do_write => id_do_write,
					busy_send => busy_send,
					lamp => id_lamp,
					decoder_complete => decoder_complete);
					
	Inst_memory_manager: memory_manager
		PORT MAP(clk => clk,
					data_in => mem_data_in,
					wr_addr => mem_wr_addr,
					wr_en => mem_wr_en,
					data_out => mem_data_out,
					rd_addr => mem_rd_addr);
					
	senddata <= id_senddata when state_reg = Executing else my_senddata;
	do_write <= id_do_write when state_reg = Executing else my_do_write;
	lamp <= id_lamp ;--when state_reg = Executing else my_lamp;
	process(clk)
		variable writing : std_logic := '0';
	begin
		if (rising_edge(clk)) then			
			if (busy_send = '0' AND writing = '0') then
				if (state_reg = Idle) then					
					state_reg <= Booting;
					my_senddata <= X"00";
					my_do_write <= '1';
					writing := '1';
					start_bootstrapper <= '1';
				elsif (state_reg = Booting AND booting_completed = '1') then
					state_reg <= Execute;
					my_senddata <= X"01";
					my_do_write <= '1';	
					writing := '1';					
					start_bootstrapper <= '0';										
				elsif (state_reg = Execute) then
					state_reg <= Executing;
					activate_decoder <= '1';
				elsif (state_reg = Executing AND decoder_complete = '1') then				
					activate_decoder <= '0';
					my_senddata <= X"02";
					my_do_write <= '1';
					writing := '1';
					state_reg <= Idle;
				end if;
			end if;
			if (state_reg /= Executing AND busy_send = '1' AND writing = '1') then
				my_do_write <= '0';
				writing := '0';
			end if;
		end if;
	end process;
end Behavioral;

