/*
 * wsystem.c
 *
 *  Created on: Apr 19, 2012
 *      Author: ACM
 */
#include "wsystem.h"

void clearScreen(){
	//white out the entire screen to start
	int x = 0;
	int y = 0;

	for (x = 0; x<MAX_WIDTH; ++x){
		for (y = 0; y<MAX_HEIGHT; ++y){
			Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (7));
		}
	}
}
