----------------------------------------------------------------------------------
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity rs232_sender is
	Port(clk : in std_logic;			
			databyte: in std_logic_vector(7 downto 0);
			do_write : in std_logic := '0';
			busy_out : out std_logic;
			tx : out std_logic);
end rs232_sender;

architecture Behavioral of rs232_sender is
	signal busyshiftreg : std_logic_vector(9 downto 0) := (others => '0');
	signal datashiftreg : std_logic_vector(9 downto 0) := (others => '1');
	signal counter : std_logic_vector(12 downto 0) := (others => '0');	
begin
	tx <= datashiftreg(0);
	busy_out <= busyshiftreg(0);	
	
	count: process(clk)
	begin
		if rising_edge(clk) then			
			if (do_write = '1' OR busyshiftreg(0) = '1') then
				if busyshiftreg(0) = '0' then
					busyshiftreg <= (others => '1');
					datashiftreg <= '1' & databyte & '0';
					counter <= (others => '0');
				else
					if counter = 3332 then
						datashiftreg <= '1' & datashiftreg(9 downto 1);
						busyshiftreg <= '0' & busyshiftreg(9 downto 1);
						counter <= (others => '0');						
					else
						counter <= counter+1;
					end if;
				end if;			
			end if;
		end if;
	end process;
end Behavioral;

