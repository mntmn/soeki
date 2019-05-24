
#include "storage.h"

void Store_DAT::Connect(char* n)
{
	SOEKI_PATH=n;
};

Dat* Store_DAT::Open(char name[],const unsigned char mode)
{
	Dat* afile = new Dat();
	sprintf (fname,"%s",name);
	if (mode==DAT_READ)
	{
		afile->SetTo(fname,B_READ_ONLY);
	};
	
	if (mode==DAT_WRITE)
	{
		afile->SetTo(fname,B_WRITE_ONLY|B_CREATE_FILE|B_ERASE_FILE);
	};
	return (afile);
};

void Store_DAT::Close(Dat* file)
{
	// delete file;
};

int Store_DAT::Read(Dat* file, void* buf, int len)
{
	return file->Read(buf,len);
};

int Store_DAT::Write(Dat* file, void* buf, int len)
{
	return file->Write(buf,len);
};
