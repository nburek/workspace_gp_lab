
#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"
#include "WidgetCore/wsystem.h"
#include "WidgetCore/util.h"
#include "WidgetCore/widget.h"
#include "WidgetCore/widget_table.h"
#include "WidgetCore/packet.h"
#include "GraphicsEngine/Graphics.h"

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#define START_SEND_COMMAND			0x7C	//Start command for a widget byte code
#define ESCAPE_CHARACTER			0x7D	//Value to escape the next character for a byte code
#define ADD_WIDGET_COMMAND			0x01	//Byte code to add a widget to the physical shield
#define REMOVE_WIDGET_COMMAND		0x02	//Byte code to remove a widget from the physical shield
#define MOVE_WIDGET_COMMAND			0x03	//Byte code to move a widget on the screen
#define SEND_WIDGET_COMMAND			0x04	//Byte code to access a widget command
#define SYSTEM_RESET				0x05	//Byte code to do a system reset

#define W_TYPE_BYTE			1		//byte 1 in byte codes
#define W_REMOVE_LOC_BYTE	1		//byte which stores the id of the Widget to remove
#define W_MOVE_LOC_BYTE		1		//byte which stores the id of the Widget to move
#define W_ACCESS_LOC_BYTE	1		//byte which stores the id of the Widget to move


#define DIAL_WIDGET_TYPE			0x01	//Byte code to define current code as a dial code
#define PROGRESS_BAR_WIDGET_TYPE	0x02	//Byte code to define current code as a progress bar code
#define LIGHT_WIDGET_TYPE			0x03	//Byte code to define current code as a light code
#define LIGHT_WIDGET_ARRAY_TYPE		0x04	//Byte code to define current code as a light array code
#define GRAPH_TYPE					0x05	//Byte code to define current code as a graph code

#define	MAX_BYTECODE_SIZE			64		//size of the longest byte code that can be received

/*
 * interpreter.c
 *
 *  Created on: Apr 30, 2012
 *      Author: ACM
 */

void interpret();
u8 receiveCodes(u8 byte_codes[], u8* length);
void returnID(u8 data);
Widget resolveWType(int type_code);

extern u32 counter;

void interpret(){

	u8 byte_codes[MAX_BYTECODE_SIZE];
	u8 length = 0;

	if(!receiveCodes(byte_codes, &length))	return;

	u8 command = byte_codes[0];

	int i;
	/*drawRectangle(60, MAX_HEIGHT - 10, MAX_WIDTH, MAX_HEIGHT, WHITE, 1);
	drawNumber(60,MAX_HEIGHT - 9,length,BLUE);
	for (i = 0; i<=length; ++i)
		drawNumber(80 + i*32,MAX_HEIGHT - 9,byte_codes[i],PURPLE);*/

	switch(command){
		case SYSTEM_RESET:
		{
			counter = 0;
			WidgetTable.clear();
			clearScreen();
			break;
		}
		case ADD_WIDGET_COMMAND:
		{
			u8 widgetID = 0xFF;
			if(!WidgetTable.isFull()){
				u8 type_byte = byte_codes[W_TYPE_BYTE];	//reads what type to create
				widgetID = WidgetTable.insert( resolveWType( type_byte ));	//resolveWType instantiates the appropriate Widget
				drawNumber(10, 10, widgetID, BLUE);							//insert, inserts the Widget and returns the position it resides in
			}
			returnID(widgetID);//return the Widget ID to the MC
			break;
		}
		case REMOVE_WIDGET_COMMAND:
		{
			clearScreen();

			WidgetTable.remove(byte_codes[W_REMOVE_LOC_BYTE]);
			WidgetTable.redrawAll();

			break;
		}

		case MOVE_WIDGET_COMMAND:
		{
			clearScreen();

			u8 loc = byte_codes[W_MOVE_LOC_BYTE];
			u16 x = weldU16(byte_codes[W_MOVE_LOC_BYTE +1], byte_codes[W_MOVE_LOC_BYTE +2]);
			u16 y = weldU16(byte_codes[W_MOVE_LOC_BYTE +3], byte_codes[W_MOVE_LOC_BYTE +4]);

			WidgetTable.moveWidget(loc, x, y);
			WidgetTable.redrawAll();

			break;
		}

		case SEND_WIDGET_COMMAND:
		{
			u8 loc = byte_codes[W_ACCESS_LOC_BYTE];

			Packet p;
			createPacket(&p, byte_codes, W_ACCESS_LOC_BYTE+2, length);

			WidgetTable.runFunctionFor(loc, byte_codes[W_ACCESS_LOC_BYTE +1], &p);
			break;
		}

	}

	drawRectangle(0, 198, 264, 206, WHITE, 1);
	for (i = 0; i<8; ++i)
		drawNumber(i*32,198,WidgetTable.bitmap[i],BLACK);

}

u8 receiveCodes(u8 byte_codes[], u8* length){

	u8 pos = 0;
	u8 state = 0;
	u8 data = 0;
	*length = 1;


/*
	clearScreen();
	int i, j;
	j = 0;
	for (i = 0;  1; ++i){
		u8 data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);


		if(i > 12 || data == 124){
			j++;
			i = 0;
		}

		if(j >= 20){
			j = 0;
			clearScreen();
		}
		drawNumber(i*32,j*10, data,PURPLE);
		returnID(1);
	}*/

/*	while (XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR) != START_SEND_COMMAND);
 *
 * do
	{
		if (pos == 0)
		{
			data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR); //read the command type
			if (data == ESCAPE_CHARACTER)
				data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
			else if (data == START_SEND_COMMAND)
				continue;

			*length = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR); //read the data length
			if(*length == ESCAPE_CHARACTER)
				*length =  XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
			else if (*length == START_SEND_COMMAND)
				continue;

			byte_codes[pos++] = data; // add the command type to the data buffer
		}

		data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR); // grab the next byte
		if(data == ESCAPE_CHARACTER) // check for escaped character
		{
			data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
			byte_codes[pos++] = data;
		}
		else if (data == START_SEND_COMMAND)
			pos = 0;
		else // if escaped ignore the escape and add the next byte to the data buffer
			byte_codes[pos++] = data; // if not escaped then add it to data buffer

	} while (pos<=*length);*/

	u8 checksum = 0;
	do
	{
		data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);

		switch(data){
			case START_SEND_COMMAND:{//always reset if it is the start command
				pos = 0;
				state = 0;
				*length = 1;
				checksum = START_SEND_COMMAND;
				break;
			}
			case ESCAPE_CHARACTER://if escape ignore byte, read next byte and process
				data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
				checksum ^= data;
			default:{
				if(state == 0){//state 0: write command type
					byte_codes[pos++] = data;
					checksum ^= data;
					++state;
				}else if(state == 1){//state 1: write length
					*length = data;
					checksum ^= data;
					++state;
				}else{//state 2: write data until done
					byte_codes[pos++] = data;
					checksum ^= data;
				}
				break;
			}

		}
	} while (pos<=*length);

	//data = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);//checksum;

	//return (checksum ^ data) == 0;
	return 1;
}

void returnID(u8 data){

	XUartLite_SendByte(XPAR_UARTLITE_1_BASEADDR, data);
}

Widget resolveWType(int type_code){

	switch(type_code){

		case DIAL_WIDGET_TYPE:				return new_DialWidget(0, 0);
		case PROGRESS_BAR_WIDGET_TYPE:		return new_PBarWidget(0, 0);
		case LIGHT_WIDGET_TYPE:				return new_LEDWidget(0, 0, 8, RED);
		case LIGHT_WIDGET_ARRAY_TYPE:		return new_LEDWidget(0, 0, 8, RED);
		case GRAPH_TYPE:					return new_GraphWidget(0, 0, 150, 50);

	}
	Widget w;
	return w;
}

#endif /* INTERPRETER_H_ */
