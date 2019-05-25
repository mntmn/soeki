/*
*/

#ifndef SOEKI_ENGINE
#define SOEKI_ENGINE

#define CHAPESBASE_BUILDINGS 299
#define CHAPESBASE_UNITS 99
#define CHAPESBASE_OBJECTS 549
#define CREATELIGHT true

#define TEX_TOPLEFT 	1
#define TEX_TOPRIGHT 	2
#define TEX_BOTTOMLEFT 	4
#define TEX_BOTTOMRIGHT 8

#define hshift 8
#define tshift 8

#include "gfx32.h"
#include "structures.h"

// FIXME silly interdependence
#include "../platform/sdl/master.h"

class Store_GFX
{
	public:
		int NW_WIDTH;
		int NW_HEIGHT;
		int16_t* zbuffer;
		bool drawn;
		bool Activated;
		NW_Unit* Units;
		NW_Object* Objects;
		NW_Building* Buildings;
		NW_Relanim* Relanims;
		
		Store_GFX();
		void Connect(Store* n,gfx_32* g);
		void DrawBuildings(int mode);
		void DrawPartial(int side,int frame);
		void Map(int scrollx,int scrolly);
		void UpDate();
};

#endif
