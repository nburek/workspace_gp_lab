##############################################################################
## Filename:          C:\workspace_gp_lab\GP_LAB_EDK/drivers/vga_v1_00_a/data/vga_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sat Mar 31 20:54:01 2012 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "vga" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
