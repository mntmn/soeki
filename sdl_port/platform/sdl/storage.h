/*
	Data file handler
	Written for Soeki - The Plague
	©1999 L.Hartmann / Atomatrix Entertainment

	BeOS Version
*/

#ifndef SOEKI_STORAGE
#define SOEKI_STORAGE

#include <stdio.h>

const unsigned char DAT_READ=1;
const unsigned char DAT_WRITE=2;

class Store_DAT
{
		char fname[500];
		
		char* SOEKI_PATH;
	public:
		void Connect(char* n);
		FILE* Open(const char name[],const unsigned char mode);
		void Close(FILE* file);
		int Read(FILE* file, void* buf, int len);
		int Write(FILE* file, void* buf, int len);
};

#endif
