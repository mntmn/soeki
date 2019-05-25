
#include "assd.h"
#include <string.h>

assd::~assd()
{
};

assd::assd()
{
	printf ("*** ASSDC launching. ***\n");

	Debug ("\n-------------------------------------------------\n");
};

void assd::Debug(const char* text)
{
	debugfile=fopen("Soeki.dbg","a+");
	fwrite(text,strlen(text),1,debugfile);
	fclose (debugfile);
  printf("[DBG] %s",text);
};
