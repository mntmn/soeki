/*
*/

#ifndef SOEKI_ENGINE
#define SOEKI_ENGINE

#include "platform/beos/master.h"
#include "independent/gfx32.h"
#include "roster.h"
#include "independent/structures.h"

class Store_GFX
{
	public:
		int NW_WIDTH;
		int NW_HEIGHT;
		int16* zbuffer;
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