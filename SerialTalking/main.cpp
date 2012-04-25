#include <iostream>
#include "SerialClass.h"
#include <Windows.h>
using namespace std;

void main()
{
	Serial *serialPort1 = new Serial(L"COM4");
	Serial *serialPort2 = new Serial(L"COM3");
	char buf[100];
	serialPort1->WriteData("a",1);
while (1)
	{
		int i = 0;
		if ((i=serialPort2->ReadData(buf,100))>0)
		{
			serialPort1->WriteData(buf,i);
		}

		i = 0;
		if ((i=serialPort1->ReadData(buf,100))>0)
		{
			serialPort2->WriteData(buf,i);
		}
		//if ((i = serialPort1->ReadData(buf,100))>0)
			//for (int ii = 0; ii<i; ++ii)
				//cout << buf[ii];
	}

/*
	while (1)
	{
		serialPort1->WriteData("H",1);
		Sleep(2000);
		serialPort1->WriteData("L",1);
		Sleep(2000);
	}*/
	
}