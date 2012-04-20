#ifndef ___OUTPACK___
#define ___OUTPACK___

#include"common.h"

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"
/////////////////////////////////////
//
//Description: handler for the byte array to clean up memory management
//
//
/////////////////////////////////////
class Packet{

private:
	u8* bytes;
	u8 size;
	u16 *use;

	void decr_use(){
		if(--*use == 0) {	delete[] bytes; delete use;}
	}

public:
	Packet(u8 size_i, u8 bytes_stream[]): size(size_i), use(new u16){
		bytes = new u8[size];
		for(u8 i(0); i < size; ++i){
			bytes[i] = bytes_stream[i];
		}
	}
	Packet(const Packet& pack): bytes(pack.bytes), use(pack.use) { ++*use;}
	~Packet(){	decr_use();	}

	Packet& operator=(const Packet& pack){
		++*pack.use;
		decr_use();
		bytes = pack.bytes;
		use = pack.use;
		return *this;
	}

	u8& operator[](u8 i) const {
		if(bytes) return bytes[i];
	}
	u8 getPacketLength(){
		return size;
	}

};

#endif