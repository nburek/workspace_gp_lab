/*
 * Empty C++ Application
 */
#include <stdio.h>
#include "Graphics.h"
#include "RoundMeter.h"
#include "xbasic_types.h"


	int main()
	{
		int x = 0;
		int y = 215;
		u8 color = 1;
		volatile int delayCounter = 0;
		RoundMeter speedDemon(x,y,1);

		for (x = 0; x<MAX_WIDTH; ++x)
			for (y = 0; y<MAX_HEIGHT; ++y)
				Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (7));
		print("---Entering main---\n\r");
		x = 100;
		y = 100;
		speedDemon.draw();
	return 0;
}
