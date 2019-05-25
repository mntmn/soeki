/*
	ASSDS Client Module for BeOS
	©1999 Lukas Hartmann / Atomatrix
*/

#ifndef SOEKI_ASSDS
#define SOEKI_ASSDS

#include <stdio.h>

class assd
{
		FILE* debugfile;
	public:
		assd();
		~assd();
		void Debug(const char* text);
};

#endif
