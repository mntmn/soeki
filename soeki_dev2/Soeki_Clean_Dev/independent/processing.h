
#ifndef SOEKI_PROC
#define SOEKI_PROC

#include "platform/beos/master.h"
#include "independent/gfx32.h"
#include "roster.h"
#include "independent/structures.h"
#include "network.h"

struct Store_PRC
{
	private:
		int16 blocks[100][100];
	public:
		NW_Unit* Units;
		NW_Relanim* Relanims;
		NW_Building* Buildings;
		void Connect(Store* n,gfx_32* g,Store_NET* nt);
		void StepTable(int unum);
		void Proc();
};

#endif