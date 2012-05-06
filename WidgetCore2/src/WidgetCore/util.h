/*
 * util.h
 *
 *  Created on: May 1, 2012
 *      Author: ACM
 */

#ifndef UTIL_H_
#define UTIL_H_

u16 weldU16(u16 byte1, u16 byte2);
u32 weldU32(u32 byte1, u32 byte2, u32 byte3, u32 byte4);
void createPacket(Packet* p, u8 byte_codes[], u8 offset, u8 length);

u16 weldU16(u16 byte1, u16 byte2){
	return (((byte1 << 8) & 0xFF00) | (byte2 & 0x00FF));
}
u32 weldU32(u32 byte1, u32 byte2, u32 byte3, u32 byte4){
	return (((byte1 << 24) & 0xFF000000) | ((byte2 << 16) & 0x00FF0000) | ((byte3 << 8) & 0x0000FF00) | (byte4 & 0x000000FF));
}

void createPacket(Packet* p, u8 byte_codes[], u8 offset, u8 length){

	int i;
	for(i = 0; i < length; ++i){
		p->bytes[i] = byte_codes[offset +i];//load the packet with the parameters
	}
	p->size = length;
}

#endif /* UTIL_H_ */
