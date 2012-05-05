/*
 * widget_table.h
 *
 *  Created on: Apr 16, 2012
 *      Author: ACM
 */

#ifndef ___WIDGETTABLE___
#define ___WIDGETTABLE___

#include"widget.h"
#include"packet.h"

#include<stdlib.h>
#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

#define NWIDGETS 64
#define CLUSTER_S 8	//CLUSTERS MUST BE A DIVISOR OR NWIDGETS, number of bits in cluster
#define FILLED_CLUSTER 0xFF
#define BIGBIT 0x80		//left-most bit in cluster
#define LILBIT 0x01		//right-most bit in cluster

void wt_init(void);
void wt_clear(void);
u8 wt_isFull(void);
s16 wt_free_loc(void);
s16 wt_insert(Widget new_wid);
u8 wt_remove(u8 loc);
void wt_redrawAll(void);
u8 wt_moveWidget(u8 loc, u16 x_s, u16 y_s);
Packet wt_runFunctionFor(u8 loc, u8 funcN, Packet* pack);
//private members
u8 wt_isValid(u8 loc);

struct widget_table{

	u8 size;			//number of widgets allocated
	u8 bitmap[NWIDGETS / CLUSTER_S];

	void (*init) (void);
	void (*clear)(void);
	u8 (*isFull) (void);
	s16 (*free_loc)(void);
	s16 (*insert)(Widget new_wid);
	u8 (*remove)(u8 loc);
	void (*redrawAll)(void);
	u8 (*moveWidget)(u8 loc, u16 x_s, u16 y_s);
	Packet (*runFunctionFor)(u8 loc, u8 funcN, Packet* pack);

	struct widget table[NWIDGETS];


}WidgetTable = {
	.size = 0,
	.init = wt_init,
	.clear = wt_clear,
	.isFull = wt_isFull,
	.free_loc = wt_free_loc,
	.insert = wt_insert,
	.remove = wt_remove,
	.redrawAll = wt_redrawAll,
	.moveWidget = wt_moveWidget,
	.runFunctionFor = wt_runFunctionFor
};

void wt_init(void){
	int i;
	int clusters = NWIDGETS / CLUSTER_S;

	for(i = 0; i < clusters; ++i){
		WidgetTable.bitmap[i] = 0;
	}
}

void wt_clear(void){

	int i;
	for(i = 0; i < NWIDGETS; ++i){
		WidgetTable.remove(i);
	}

	WidgetTable.size = 0;
}

u8 wt_isFull(void){
	return WidgetTable.size == NWIDGETS ? 1 : 0;
}
//returns location and true if found,  if not returns proper parent location and false
//loc = 0 is a standard call
s16 wt_free_loc(void){

	u32 i;
	u16 clusters = (NWIDGETS > CLUSTER_S)? NWIDGETS / CLUSTER_S: 1;
	s16 free = -1;

	for(i = 0; i < clusters; ++i){
		if(WidgetTable.bitmap[i] == 0){
			return (i * CLUSTER_S);
		}else if(WidgetTable.bitmap[i] != FILLED_CLUSTER){
			free = i;
		}
	}

	if(free != -1){

		for(i = 0; i < CLUSTER_S; ++i){

			if(((WidgetTable.bitmap[free] >> (CLUSTER_S - 1 - i)) & LILBIT) == 0){
				return (free*CLUSTER_S + i);
			}
		}
	}

	return -1;
}

s16 wt_insert(Widget new_wid){

	s16 free_loc = 	wt_free_loc();

	if(free_loc != -1){
		u8 cluster = free_loc / CLUSTER_S;
		u8 bit = free_loc - cluster * CLUSTER_S;

		WidgetTable.bitmap[cluster] |= (BIGBIT >> bit);
		WidgetTable.table[free_loc] = new_wid;
		WidgetTable.size++;

		return free_loc;
	}

	return -1; //failed
}

u8 wt_remove(u8 loc){

	if(wt_isValid(loc)){
		u8 cluster = loc / CLUSTER_S;
		u8 bit = loc - cluster * CLUSTER_S;

		WidgetTable.table[loc].destroy();//remove all dynamic memory stored in derive

		free((void*)(WidgetTable.table[loc].derive));//remove the const and free the derived portion
		WidgetTable.bitmap[cluster] ^= (BIGBIT >> bit);

		WidgetTable.size--;

		return 1;
	}else{
		return 0;
	}
}
void wt_redrawAll(void){

	Packet p;
	int i;
	for(i = 0; i < NWIDGETS; ++i){
		if(wt_isValid(i)){
			WidgetTable.runFunctionFor(i, 1, &p);
		}
	}
}
u8 wt_moveWidget(u8 loc, u16 x_s, u16 y_s){

	if(wt_isValid(loc)){
		WidgetTable.table[loc].x = x_s;
		WidgetTable.table[loc].y = y_s;
		return 1;
	}
	return 0;
}
Packet wt_runFunctionFor(u8 loc, u8 funcN, Packet* pack){

	if(wt_isValid(loc)){
		return WidgetTable.table[loc].runFunction(&(WidgetTable.table[loc]), funcN, pack);
	}else{
		Packet p;
		p.bytes[0] = 0;
		return p;
	}
}

u8 wt_isValid(u8 loc){
	u8 cluster = loc / CLUSTER_S;
	u8 bit = loc - cluster * CLUSTER_S;

	if((WidgetTable.bitmap[cluster] & (BIGBIT >> bit)) == (BIGBIT >> bit)){
		return 1;
	}else{
		return 0;
	}
}

#endif
