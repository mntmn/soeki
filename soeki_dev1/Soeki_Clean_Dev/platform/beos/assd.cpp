
#include "assd.h"

assd::~assd()
{
	printf ("*** ASSDC ");
	Debug("@");
	//serial.Close();
	printf ("shutdown. ***\n");
};

assd::assd()
{
	serial.SetFlowControl(0);
	serial.SetTimeout(2000000);

	printf ("*** ASSDC launching. ***\n");

	/*if (serial.Open("serial2"))
	{
		printf ("*** serial2 opened succesfully ***\n");
	}
	else
	{
		printf ("*** Couldn't open serial2! ***\n");
	};
	if (serial.SetDataRate(B_38400_BPS)==B_OK)
	{
		printf ("*** Data rate set to 38400 BPS ***\n");
	}
	else
	{
		printf ("*** Couldn't set data rate! ***\n");
		exit(666);
	}
	Debug("SESSION");
	printf ("*** Server session started. ***\n");*/

	Debug ("\n-------------------------------------------------\n");
};

void assd::Debug(char* text)
{
	//serial.Write(text,strlen(text));
	debugfile=fopen ("/boot/home/Soeki.dbg","a+");
	fwrite(text,strlen(text),1,debugfile);
	fclose (debugfile);
};