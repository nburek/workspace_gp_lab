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

void wt_init();
u8 wt_isFull();
s16 wt_free_loc();
s16 wt_insert(Widget new_wid);
void wt_remove(u8 loc);
Packet wt_runFunctionFor(u8 loc, u8 funcN, Packet* pack);

struct widget_table{

	u8 size;			//number of widgets allocated
	u8 bitmap[NWIDGETS / CLUSTER_S];

	void (*init) ();
	u8 (*isFull) ();
	s16 (*free_loc)();
	s16 (*insert)(Widget new_wid);
	void (*remove)(u8 loc);
	Packet (*runFunctionFor)(u8 loc, u8 funcN, Packet* pack);

	struct widget table[NWIDGETS];


}WidgetTable = {
	.size = 0,
	.init = wt_init,
	.isFull = wt_isFull,
	.free_loc = wt_free_loc,
	.insert = wt_insert,
	.remove = wt_remove,
	.runFunctionFor = wt_runFunctionFor
};

void wt_init(){
	int i;
	int clusters = NWIDGETS / CLUSTER_S;

	for(i = 0; i < clusters; ++i){
		WidgetTable.bitmap[i] = 0;
	}
}

u8 wt_isFull(){
	return WidgetTable.size == NWIDGETS ? 1 : 0;
}
//returns location and true if found,  if not returns proper parent location and false
//loc = 0 is a standard call
s16 wt_free_loc(){

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

void wt_remove(u8 loc){

	u8 cluster = loc / CLUSTER_S;
	u8 bit = loc - cluster * CLUSTER_S;

	free(WidgetTable.table[loc].derive);
	WidgetTable.bitmap[cluster] ^= (BIGBIT >> bit);

	WidgetTable.size--;
}

Packet wt_runFunctionFor(u8 loc, u8 funcN, Packet* pack){

	return WidgetTable.table[loc].runFunction(&(WidgetTable.table[loc]), funcN, pack);
}

#endif
