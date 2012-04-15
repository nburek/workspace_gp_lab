#include"common.h"
#include"mc_intr_codes.h"

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

	void isWidget(u8*);
	void isGlobal(u8*);
	u8* readDataStream();
	void parse();
	u16 weldU16(u16 byte1, u16 byte2);
	s16 weldS16(s16 byte1, s16 byte2);
	u32 weldU32(u32 byte1, u32 byte2, u32 byte3, u32 byte4);
	s32 weldU32(s32 byte1, s32 byte2, s32 byte3, s32 byte4);

	void isWidget(u8* byte_codes){
		//channels widget functions
	}

	void isGlobal(u8* byte_codes){
		//runs global functions
	}

	u8* readDataStream(){
	
		u8 code_type = 0;
		//read first intruction
		//read instruction length (in bytes)
		u8 n_intr = 8;
		u8* byte_codes = new u8[n_intr];
		byte_codes[0] = code_type;

		for(u8 i(0); i < n_intr; ++i){
		//	byte_codes = readSPI();
		}

		return 0;
		
	}
	void parse(){

		u8* byte_codes = readDataStream();

		switch(byte_codes[0]){
			case MC_INTR_WID_STR:
				isWidget(byte_codes);
				break;
			case MC_INTR_GBL_STR:
				isGlobal(byte_codes);
				break;
		}

	}

	u16 weldU16(u16 byte1, u16 byte2){
		return (((byte1 << 8) && 0xFF00) | (byte2 && 0x00FF));
	}
	s16 weldS16(s16 byte1, s16 byte2){
		return (((byte1 << 8) && 0xFF00) | (byte2 && 0x00FF));
	}
	u32 weldU32(u32 byte1, u32 byte2, u32 byte3, u32 byte4){
		return (((byte1 << 24) && 0xFF000000) | ((byte2 << 16) && 0x00FF0000) | ((byte3 << 8) && 0x0000FF00) | (byte4 && 0x000000FF));
	}
	s32 weldU32(s32 byte1, s32 byte2, s32 byte3, s32 byte4){
		return (((byte1 << 24) && 0xFF000000) | ((byte2 << 16) && 0x00FF0000) | ((byte3 << 8) && 0x0000FF00) | (byte4 && 0x000000FF));
	}

