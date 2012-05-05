-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    RS232_Uart_1_sout : out std_logic;
    RS232_Uart_1_sin : in std_logic;
    RESET : in std_logic;
    GCLK : in std_logic;
    vga_0_Hsync_pin : out std_logic;
    vga_0_Vsync_pin : out std_logic;
    vga_0_R_pin : out std_logic_vector(2 downto 0);
    vga_0_G_pin : out std_logic_vector(2 downto 0);
    vga_0_B_pin : out std_logic_vector(1 downto 0)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      RS232_Uart_1_sout : out std_logic;
      RS232_Uart_1_sin : in std_logic;
      RESET : in std_logic;
      GCLK : in std_logic;
      vga_0_Hsync_pin : out std_logic;
      vga_0_Vsync_pin : out std_logic;
      vga_0_R_pin : out std_logic_vector(2 downto 0);
      vga_0_G_pin : out std_logic_vector(2 downto 0);
      vga_0_B_pin : out std_logic_vector(1 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      RS232_Uart_1_sout => RS232_Uart_1_sout,
      RS232_Uart_1_sin => RS232_Uart_1_sin,
      RESET => RESET,
      GCLK => GCLK,
      vga_0_Hsync_pin => vga_0_Hsync_pin,
      vga_0_Vsync_pin => vga_0_Vsync_pin,
      vga_0_R_pin => vga_0_R_pin,
      vga_0_G_pin => vga_0_G_pin,
      vga_0_B_pin => vga_0_B_pin
    );

end architecture STRUCTURE;

