------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2011 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Sat Mar 31 20:53:39 2012 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_NUM_REG                    -- Number of software accessible registers
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Resetn                -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------

	 Ha: INTEGER := 96;   --Hpulse
	 Hb: INTEGER := 144;  --Hpulse+HBP
	 Hc: INTEGER := 784;  --Hpulse+HBP+Hactive
	 Hd: INTEGER := 800;  --Hpulse+HBP+Hactive+HFP
	 Va: INTEGER := 2;    --Vpulse
	 Vb: INTEGER := 35;   --Vpulse+VBP
	 Vc: INTEGER := 515;  --Vpulse+VBP+Vactive
	 Vd: INTEGER := 525;  --Vpulse+VBP+Vactive+VFP
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_NUM_REG                      : integer              := 1;
    C_SLV_DWIDTH                   : integer              := 32
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
	 clk: IN STD_LOGIC;
    Hsync, Vsync: OUT STD_LOGIC;
	 R, G: OUT STD_LOGIC_VECTOR(2 downto 0);
	 B: OUT STD_LOGIC_VECTOR (1 downto 0);
    -- ADD USER PORTS ABOVE THIS LINE ------------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Resetn                  : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    Bus2IP_BE                      : in  std_logic_vector(C_SLV_DWIDTH/8-1 downto 0);
    Bus2IP_RdCE                    : in  std_logic_vector(C_NUM_REG-1 downto 0);
    Bus2IP_WrCE                    : in  std_logic_vector(C_NUM_REG-1 downto 0);
    IP2Bus_Data                    : out std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Resetn : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic
  	-- VGA sync signal
	signal clk25 : STD_LOGIC;
	signal pixelX : STD_LOGIC_VECTOR (9 downto 0);
	signal pixelY : STD_LOGIC_VECTOR (8 downto 0);
	signal currentPixel : STD_LOGIC_VECTOR(7 downto 0);
	signal pixel_clk : STD_LOGIC;
	-- this is the mouse image rom information
	type displayrom is array(0 to 255) of std_logic_vector(1 downto 0);
	-- the memory that holds the cursor.
	-- 00 - black
	-- 01 - white
	-- 1x - transparent
	constant mouserom: displayrom := (
	"00","00","11","11","11","11","11","11","11","11","11","11","11","11","11","11",
	"00","01","00","11","11","11","11","11","11","11","11","11","11","11","11","11",
	"00","01","01","00","11","11","11","11","11","11","11","11","11","11","11","11",
	"00","01","01","01","00","11","11","11","11","11","11","11","11","11","11","11",
	"00","01","01","01","01","00","11","11","11","11","11","11","11","11","11","11",
	"00","01","01","01","01","01","00","11","11","11","11","11","11","11","11","11",
	"00","01","01","01","01","01","01","00","11","11","11","11","11","11","11","11",
	"00","01","01","01","01","01","01","01","00","11","11","11","11","11","11","11",
	"00","01","01","01","01","01","00","00","00","00","11","11","11","11","11","11",
	"00","01","01","01","01","01","00","11","11","11","11","11","11","11","11","11",
	"00","01","00","00","01","01","00","11","11","11","11","11","11","11","11","11",
	"00","00","11","11","00","01","01","00","11","11","11","11","11","11","11","11",
	"00","11","11","11","00","01","01","00","11","11","11","11","11","11","11","11",
	"11","11","11","11","11","00","01","01","00","11","11","11","11","11","11","11",
	"11","11","11","11","11","00","01","01","00","11","11","11","11","11","11","11",
	"11","11","11","11","11","11","00","00","11","11","11","11","11","11","11","11"
	);
	SIGNAL writeAddress : std_logic_vector (16 downto 0);
	SIGNAL writeData : std_logic_vector (2 downto 0);
	SIGNAL readAddress : std_logic_vector (16 downto 0);
	SIGNAL readData : std_logic_vector (2 downto 0);
	
	component videoMemory IS
	PORT (
		clka : IN STD_LOGIC;
		wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
		addra : IN STD_LOGIC_VECTOR(16 DOWNTO 0);
		dina : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
		clkb : IN STD_LOGIC;
		addrb : IN STD_LOGIC_VECTOR(16 DOWNTO 0);
		doutb : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)
	);
	END component;

  ------------------------------------------
  -- Signals for user logic slave model s/w accessible register example
  ------------------------------------------
  signal slv_reg0                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_reg_write_sel              : std_logic_vector(0 to 0);
  signal slv_reg_read_sel               : std_logic_vector(0 to 0);
  signal slv_ip2bus_data                : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_read_ack                   : std_logic;
  signal slv_write_ack                  : std_logic;

begin
	
		videoMem:  videoMemory
		PORT MAP (
			clka => clk,
			wea => "1",
			addra => writeAddress,
			dina => writeData,
			clkb => clk,
			addrb => readAddress,
			doutb => readData
		);

  --USER logic implementation added here
	Process (clk)
		VARIABLE clk_counter : STD_LOGIC_VECTOR(1 downto 0);
	Begin
		IF (clk'EVENT AND clk='1') THEN
			clk_counter := clk_counter + 1;
			pixel_clk <= clk_counter(1);
		END IF;
	END PROCESS;
	
	process (pixel_clk)
	variable vCount : STD_LOGIC_VECTOR (8 downto 0);
	variable hCount : STD_LOGIC_VECTOR (9 downto 0);
	begin

	-- timing diagram for the horizontal synch signal (HS)
	-- 0                               656    752     799 (pixels)
	-- --------------------------------|______|----------
	-- timing diagram for the vertical synch signal (VS)
	-- 0                        490    492            521 (lines)
	-- -------------------------|______|-----------------

	IF pixel_clk'EVENT AND pixel_clk='1' THEN

		IF (hCount <= 751) AND (hCount >= 656) THEN -- is it time to pulse the horizontal sync signal low
			Hsync <= '0';
		ELSE
			Hsync <= '1';
		END IF;

		IF (vCount<=491) AND (vCount>=490) THEN -- is it time to pulse the vertical sync signal low
			Vsync <= '0';
		ELSE
			Vsync <= '1';
		END IF;

		IF (hCount = 799) THEN 
			-- done with this row, move down to the next one
			hCount := "0000000000"; 

			IF (vCount = 521) THEN
				vCount := "000000000"; -- done outputing the screen, start over
			ELSE
				vCount := vCount + 1; -- increment the row count to track which row you're on
			END IF;

		ELSE
			hCount := hCount + 1; -- move to the next pixel
		END IF;

		IF ((hCount<=640) AND (vCount<=480)) THEN -- are we within the valid pixel display range
			IF (hCount=0) THEN -- don't output anything on the first iteration of each row
				--R <= "000";
				--G <= "000";
				--B <= "00";
			ELSE -- output the pixel data from the Video_Ram
				IF (vCount<216 AND hCount<=384) THEN
					R <= (others => readData(2));
					G <= (others => readData(1));
					B <= (others => readData(0));
				ELSE
					R <= (others => '0');
					G <= (others => '0');
					B <= (others => '0');
				END IF;
			END IF;

			-- change the pixel coordinates so that the Video_Ram will start loading the
			-- value for the next pixel
			pixelX <= hCount;
			pixelY <= vCount;

			-- if you're at the end of the visible row start loading the first pixel for the next visible row
			IF (hCount=640) THEN 
				pixelX <= "0000000000";
				IF (vCount=479) THEN
					pixelY <= "000000000";
				ELSE
					pixelY <= vCount + 1;
				END IF;
			END IF;



		ELSE
			-- turn off the pixel out data because it is either on the front/back porch or the pulse signal
			R <= "000";
			G <= "000";
			B <= "00";
		END IF;
		
		readAddress <= conv_std_logic_vector(conv_integer(vCount)*384 + conv_integer(hCount),17);

	END IF;


	end process;

  ------------------------------------------
  -- Example code to read/write user logic slave model s/w accessible registers
  -- 
  -- Note:
  -- The example code presented here is to show you one way of reading/writing
  -- software accessible registers implemented in the user logic slave model.
  -- Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  -- to one software accessible register by the top level template. For example,
  -- if you have four 32 bit software accessible registers in the user logic,
  -- you are basically operating on the following memory mapped registers:
  -- 
  --    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  --                     "1000"   C_BASEADDR + 0x0
  --                     "0100"   C_BASEADDR + 0x4
  --                     "0010"   C_BASEADDR + 0x8
  --                     "0001"   C_BASEADDR + 0xC
  -- 
  ------------------------------------------
  slv_reg_write_sel <= Bus2IP_WrCE(0 downto 0);
  slv_reg_read_sel  <= Bus2IP_RdCE(0 downto 0);
  slv_write_ack     <= Bus2IP_WrCE(0);
  slv_read_ack      <= Bus2IP_RdCE(0);

  -- implement slave model software accessible register(s)
  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
  begin

    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
      if Bus2IP_Resetn = '0' then
        slv_reg0 <= (others => '0');
      else
        case slv_reg_write_sel is
          when "1" =>
				writeData <= Bus2IP_Data(2 downto 0);
				writeAddress <= Bus2IP_Data(19 downto 3);
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--				    
--                slv_reg0(byte_index*8+7 downto byte_index*8) <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--              end if;
--            end loop;
          when others => null;
        end case;
      end if;
    end if;

  end process SLAVE_REG_WRITE_PROC;

  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel, slv_reg0 ) is
  begin

    case slv_reg_read_sel is
      when "1" => slv_ip2bus_data <= slv_reg0;
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';

end IMP;
