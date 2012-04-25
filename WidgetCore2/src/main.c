
#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"
#include "WidgetCore/wsystem.h"
#include "WidgetCore/widget.h"
#include "WidgetCore/widget_table.h"
#include "WidgetCore/packet.h"
#include "Widgets/Dial.h"
#include "Widgets/pbar.h"
#include "Widgets/light.h"
#include "Widgets/light_row.h"
#include "Widgets/stringWID.h"
#include "GraphicsEngine/Graphics.h"

int main()
{
		WidgetTable.init();
		Packet p;

		u32 counter = 0;

		volatile int delayCounter = 0;

		clearScreen();

		WidgetTable.insert(new_DialWidget(85, 65));
		s16 loc  = WidgetTable.insert(new_PBarWidget(160, 85));
		s16 loc2 = WidgetTable.insert(new_LRowWidget(190, 35));
		s16 loc3 = WidgetTable.insert(new_STRWidget(100, 200, "THOMAS1", 7, BLACK));

		WidgetTable.runFunctionFor(0, 1, &p);
		WidgetTable.runFunctionFor(loc, 1, &p);
		WidgetTable.runFunctionFor(loc2, 1, &p);

		//draw test digits 0-9
		int i;
		for (i = 0; i<10; ++i)
			drawDigit(264+i*12,207,i,BLACK);

		//char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		//char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

		int y = 0;
		int x = 0;
		while (1)
		{
			//this is getting sent as a temporary handshake of sorts to request a byte
			XUartLite_SendByte(XPAR_UARTLITE_1_BASEADDR, 128);

			p.bytes[0] = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);;
			WidgetTable.runFunctionFor(0, 2, &p);

			p.bytes[0] = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);;
			WidgetTable.runFunctionFor(loc, 2, &p);

			int lights = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
			p.bytes[0] = lights & 0x01;
			p.bytes[1] = lights & 0x02;
			p.bytes[2] = lights & 0x04;
			p.bytes[3] = lights & 0x08;
			p.bytes[4] = lights & 0x10;
			p.bytes[5] = lights & 0x20;
			p.bytes[6] = lights & 0x40;
			p.bytes[7] = lights & 0x80;

			drawRectangle(200, 200, 224, 208, WHITE, 1);
			drawNumber(200, 200, lights & 0xFF, RED);

			WidgetTable.runFunctionFor(loc2, 2, &p);

			WidgetTable.runFunctionFor(loc3, 1, &p);

			Packet q = WidgetTable.runFunctionFor(loc2, 3, &p);
			if((!WidgetTable.isFull() || x >= MAX_WIDTH) && (q.bytes[0] == 1)){
				s16 loc4 = WidgetTable.insert(new_STRWidget(x, y, "THOMAS GRIEBEL", 14, CYAN));
				WidgetTable.runFunctionFor(loc4, 1, &p);
				y += 8;
				if(y >= (MAX_HEIGHT)){
					y = 0;
					x += 112;
				}
				WidgetTable.remove(loc4);
			}

			drawNumber(4, 207,counter, CYAN);
			++counter;

			delayCounter = 0;
			while (delayCounter<999999)
				delayCounter++;
		}


    return 0;
}
