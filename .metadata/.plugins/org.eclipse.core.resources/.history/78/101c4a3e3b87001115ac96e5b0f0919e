#include"widget.h"

class PBar: public Widget{

private:
	u16 length;
	u16 done;

	Packet (PBar::*funcTable[nFuncs])(const Packet&);	//creates array of pointers to member function named funcPtr

	//sample function to work through the function table
	Packet f1(const Packet& pack){

		Packet p(pack);

		return p;
	}
public:

	PBar(u16 length_i) : done(0){
		length = length_i;
		funcTable[0] = &PBar::f1; //assign function f1 to the function table
	}

	//responsible for operating rendering functions
	void render(){
	//	cout << "|" << done << "/" << length << "|" << endl;
	}

	Packet runFunction(u8 function, const Packet& pack){
		return (this->*funcTable[function])(pack);
	}
};
