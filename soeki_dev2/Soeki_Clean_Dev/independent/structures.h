/*
	Networ Structures 1999 Lukas Hartmann / Atomatrix Entertainment
	Updated: 24.2.1999
*/

#ifndef SOEKI_STRUCT
#define SOEKI_STRUCT

#include <AppKit.h>
#include <NetworkKit.h>

#define UNIT_STATE_WAITING 1
#define UNIT_STATE_MOVING 2
#define UNIT_STATE_ATTACKING 3
#define UNIT_STATE_DYING 4

#define EVENT_LOOP 1

struct normals
{
	double nx,ny,nz,nl;
};

struct xy
{
	signed int x;
	signed int y;
};

struct Vector
{
	float x;
	float y;
	float z;
};

struct chape
{
	uint32 w;
	uint32 h;
	int32 xhandle;
	int32 yhandle;
	uint32* chunk;
};

struct event
{
	uint8 type;
	uint8 chape;
	uint16 frame;
	uint8 delay;
	char name[21];
};

struct NW_Building
{
	short id;
	uint16 statics[4];
	bool sshadow[4];
	event events[8];
	char name[21];
	char descr[21];
	uint8 bmap[5*5];
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
	int16* blocks;
	int dispx;
	int dispy;
	short dr;
	short health;
	unsigned char state;
	short state_data;
	int state_data2;
	short state_counter;
	short activated_frame;
	unsigned char cargo;
	bool active;
};

struct NW_Relanim
{
	int16 startframe;
	short frame;
	short duration;
	uint32 x;
	uint32 y;
	short w;
	short h;
	bool transparent;
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

struct NW_Texture
{
	uint32* data;
	uint8	flags;
	BBitmap* transmap;
};

struct NW_Player
{
	long id;
	char hostname[128];
	char nickname[128];
	bool artifical;
	BNetEndpoint* connection;
};

#endif
