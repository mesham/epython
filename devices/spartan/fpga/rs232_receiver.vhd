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

entity rs232_receiver is
	Generic(frequency : natural;
				baud : natural);
				
	Port(clk : in STD_LOGIC;
        rx : in STD_LOGIC;
        data : out STD_LOGIC_VECTOR (7 downto 0);
        data_strobe : out STD_LOGIC);
end rs232_receiver;

architecture Behavioral of rs232_receiver is
	signal oversampled_bits : std_logic_vector(39 downto 0) := (others => '1');
	signal baud_x4 : unsigned(11 downto 0) := (others => '0');
begin
	process(clk)
	begin
		if rising_edge(clk) then
			data_strobe <= '0';

			if baud_x4 = 0 then
				-- If a start bit is seen then capture the data and reset the shift registers
				if oversampled_bits(39 downto 37) = "000" then
					data_strobe <= '1';
					data <= oversampled_bits(6) & oversampled_bits(10) 
								& oversampled_bits(14) & oversampled_bits(18)
								& oversampled_bits(22) & oversampled_bits(26) 
								& oversampled_bits(30) & oversampled_bits(34);
					oversampled_bits(39 downto 1) <= (others => '1');
					oversampled_bits(0) <= rx;
				else
					-- Just capture another bit in the shift register.
					oversampled_bits <= oversampled_bits(38 downto 0) & rx;
				end if;
			end if;

			-- process the interval counter
			if baud_x4 = frequency / (baud*4) - 1 then
				baud_x4 <= (others => '0');
			else
				baud_x4 <= baud_x4+1;
			end if;
		end if;
	end process;
end Behavioral;

