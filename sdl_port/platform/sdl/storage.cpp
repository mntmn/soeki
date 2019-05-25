
#include "storage.h"
#include <stdio.h>

void Store_DAT::Connect(char* n)
{
	//SOEKI_PATH=n;
};

FILE* Store_DAT::Open(const char name[],const unsigned char mode)
{
	FILE* afile;
	if (mode==DAT_READ)
	{
		afile = fopen(name,"r");
	};
	
	if (mode==DAT_WRITE)
	{
		afile = fopen(name,"w+");
	};
	return afile;
};

void Store_DAT::Close(FILE* file)
{
	fclose(file);
};

int Store_DAT::Read(FILE* file, void* buf, int len)
{
	return fread(buf, len, 1, file);
};

int Store_DAT::Write(FILE* file, void* buf, int len)
{
	return fwrite(buf, len, 1, file);
};
