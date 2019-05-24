/*
	ASSDS Client Module for BeOS
	©1999 Lukas Hartmann / Atomatrix
*/

#ifndef SOEKI_ASSDS
#define SOEKI_ASSDS

#include <DeviceKit.h>
#include <stdio.h>

class assd
{
		BSerialPort serial;
		FILE* debugfile;
	public:
		assd();
		~assd();
		void Debug(char* text);
};

#endif