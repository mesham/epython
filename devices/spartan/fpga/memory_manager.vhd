----------------------------------------------------------------------------------
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

entity memory_manager is
	port (clk : in std_logic;
				data_in : in std_logic_vector(7 downto 0);
				wr_addr : in std_logic_vector(9 downto 0);
				wr_en : in std_logic;
				
				data_out : out std_logic_vector(31 downto 0);
				rd_addr : in std_logic_vector(9 downto 0));
end memory_manager;

architecture Behavioral of memory_manager is
	type array_1kx8 is array(1024 downto 0) of std_logic_vector(7 downto 0);
	
	signal ram : array_1kx8;
begin
	process(clk)
	begin
		if rising_edge(clk) then
			if (wr_en = '1') then
				ram(to_integer(unsigned(wr_addr))) <= data_in;
			end if;
			data_out(7 downto 0) <= ram(to_integer(unsigned(rd_addr)));
			data_out(15 downto 8) <= ram(to_integer(unsigned(rd_addr))+1);
			data_out(23 downto 16) <= ram(to_integer(unsigned(rd_addr))+2);
			data_out(31 downto 24) <= ram(to_integer(unsigned(rd_addr))+3);
		end if;
	end process;
end Behavioral;

