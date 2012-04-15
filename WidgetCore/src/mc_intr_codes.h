#ifndef ___MCINTR___
#define ___MCINTR___

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

//define ordering of instructions
const u8 BEG		= 0; //begin
const u8 LEN		= 1; //length
const u8 FUNC		= 2; //function
const u8 W_ADDR		= 3; //widget address
const u8 W_MF		= 4; //widget memeber function
const u8 W_MF_P		= 5; //base of widget member function parameters

//define values of instruction
const u8 MC_INTR_WID_STR = 0x01; //start widget instruction
const u8 MC_INTR_GBL_STR = 0x02; //start global instruction



#endif
