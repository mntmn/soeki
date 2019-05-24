/*
	Networ Structures ©1999 Lukas Hartmann / Atomatrix Entertainment
	Updated: 24.2.1999
*/

	#include <AppKit.h>

struct chape
{
	uint32 w;
	uint32 h;
	int32 xhandle;
	int32 yhandle;
	uint32* chunk;
};

struct NW_Building
{
	short type;
	unsigned char owner;
	uint32 x;
	uint32 y;
	unsigned char w;
	unsigned char h;
	short health;
	unsigned char state;
	short state_data;
	unsigned char cargo;
	unsigned char cargo2;
	bool active;
};

struct NW_Unit
{
	short type;
	unsigned char owner;
	uint32 x;
	uint32 y;
	short r;
	int relx;
	int rely;
	short w;
	short h;
	uint32 dx;
	uint32 dy;
	short dr;
	short health;
	unsigned char state;
	short state_data;
	short activated_frame;
	unsigned char cargo;
	bool active;
};

struct NW_Object
{
	short type;
	uint32 x;
	uint32 y;
	short w;
	short h;
	uint32 flags;
};