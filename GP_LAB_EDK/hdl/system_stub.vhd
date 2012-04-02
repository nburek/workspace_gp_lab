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
    Push_Buttons_4Bits_TRI_I : in std_logic_vector(0 to 3);
    LEDs_8Bits_TRI_O : out std_logic_vector(7 downto 0);
    GCLK : in std_logic;
    DIP_Switches_8Bits_TRI_I : in std_logic_vector(7 downto 0);
    Digilent_SevSeg_Disp_AN_pin : out std_logic_vector(3 downto 0);
    Digilent_SevSeg_Disp_SEG_pin : out std_logic_vector(7 downto 0);
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
      Push_Buttons_4Bits_TRI_I : in std_logic_vector(0 to 3);
      LEDs_8Bits_TRI_O : out std_logic_vector(7 downto 0);
      GCLK : in std_logic;
      DIP_Switches_8Bits_TRI_I : in std_logic_vector(7 downto 0);
      Digilent_SevSeg_Disp_AN_pin : out std_logic_vector(3 downto 0);
      Digilent_SevSeg_Disp_SEG_pin : out std_logic_vector(7 downto 0);
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
      Push_Buttons_4Bits_TRI_I => Push_Buttons_4Bits_TRI_I,
      LEDs_8Bits_TRI_O => LEDs_8Bits_TRI_O,
      GCLK => GCLK,
      DIP_Switches_8Bits_TRI_I => DIP_Switches_8Bits_TRI_I,
      Digilent_SevSeg_Disp_AN_pin => Digilent_SevSeg_Disp_AN_pin,
      Digilent_SevSeg_Disp_SEG_pin => Digilent_SevSeg_Disp_SEG_pin,
      vga_0_Hsync_pin => vga_0_Hsync_pin,
      vga_0_Vsync_pin => vga_0_Vsync_pin,
      vga_0_R_pin => vga_0_R_pin,
      vga_0_G_pin => vga_0_G_pin,
      vga_0_B_pin => vga_0_B_pin
    );

end architecture STRUCTURE;

