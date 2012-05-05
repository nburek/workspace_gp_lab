
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
#include "Widgets/graph.h"
#include "GraphicsEngine/Graphics.h"
#include "interpreter.h"

u32 counter = 0;
int main()
{
		WidgetTable.init();

		clearScreen();

		Packet p;

		while (1)
		{
			interpret();

			drawNumber(4, 207,counter, CYAN);
			++counter;
		}


    return 0;
}
