/*
	Networ Structures 1999 Lukas Hartmann / Atomatrix Entertainment
	Updated: 24.2.1999
*/

#ifndef SOEKI_STRUCT
#define SOEKI_STRUCT

#include <stdint.h>

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
	uint32_t w;
	uint32_t h;
	int32_t xhandle;
	int32_t yhandle;
	uint32_t* chunk;
};

struct event
{
	uint8_t type;
	uint8_t chape;
	uint16_t frame;
	uint8_t delay;
	char name[21];
};

struct NW_Building
{
	short id;
	uint16_t statics[4];
	bool sshadow[4];
	event events[8];
	char name[21];
	char descr[21];
	uint8_t bmap[5*5];
	unsigned char owner;
	uint32_t x;
	uint32_t y;
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
	uint32_t x;
	uint32_t y;
	short r;
	int relx;
	int rely;
	short w;
	short h;
	uint32_t dx;
	uint32_t dy;
	int16_t* blocks;
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
	int16_t startframe;
	short frame;
	short duration;
	uint32_t x;
	uint32_t y;
	short w;
	short h;
	bool transparent;
};

struct NW_Object
{
	short type;
	uint32_t x;
	uint32_t y;
	short w;
	short h;
	uint32_t flags;
};

struct NW_Texture
{
	uint32_t* data;
	uint8_t	flags;
	//BBitmap* transmap;
};

struct NW_Player
{
	long id;
	char hostname[128];
	char nickname[128];
	bool artifical;
};

#endif
