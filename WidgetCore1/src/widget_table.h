
#include"common.h"
#include"widget.h"

class WidgetTable{

private:

	u8 size;			//number of widgets allocated
	struct Wnode{
		Widget* addr;	//compare to value

		Wnode():addr(0) {}
	};
	
	Wnode table[NWIDGETS]; 
	
public:

	WidgetTable(): size(0){}

	inline bool isFull();

	s16 search(Widget* addr);

	s16 insert(Widget* wid, s16 loc = -1);

	void remove(u8 loc);
	inline void remove(u32 addr);
	inline void remove(Widget* addr);

	Widget* operator[](u8 loc);
};