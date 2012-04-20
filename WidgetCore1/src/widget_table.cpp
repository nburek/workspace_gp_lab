#include"widget_table.h"

inline bool WidgetTable::isFull(){
	return size == (NWIDGETS - 1) ? true : false;
}
//returns location and true if found,  if not returns proper parent location and false
//loc = 0 is a standard call
s16 WidgetTable::search(Widget* addr){
	for(int i(0); i < NWIDGETS; ++i){
		if(table[i].addr == addr){
			return i;
		}
	}	
	return -1;
}

s16 WidgetTable::insert(Widget* wid, s16 loc){
	
	bool collision(false);
	do{
		collision = false;
		if(loc == -1){//no preference or location taken, scan and return first empty
			loc = search(0);
		}
		//if location is legal
		if(loc >= 0 && loc < NWIDGETS){
			if(table[loc].addr != 0){//user specified location was bad
				collision = true;
				loc = -1;
			}else{
				table[loc].addr = wid;
				++size;
			}
			return loc;
		}
	}while(collision);
		
	return -1; //failed
}

void WidgetTable::remove(u8 loc){
	delete table[loc].addr;
	table[loc].addr = 0;
	size--;
}
inline void WidgetTable::remove(u32 addr){
	remove((u8)search((Widget*) addr));
}
inline void WidgetTable::remove(Widget* addr){
	remove((u8)search(addr));
}

Widget* WidgetTable::operator[](u8 loc){
	
	return table[loc].addr;
}