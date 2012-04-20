#ifndef ___WIDGET___
#define ___WIDGET___

#include"packet.h"

class Widget{

protected:
	static const unsigned nFuncs = 8;
	u16 x, y;
public:

	virtual void render() = 0;

	//universal interface to run a function
	//TO DO: enforce the function table, make this non-virtual
//	virtual Packet runFunction(u8 function, const Packet& pack) = 0;
	void move(u16 x_s, u16 y_s){
		x = x_s;
		y = y_s;
	}
};


#endif
