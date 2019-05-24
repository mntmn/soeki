/*
	Atomatrix Zones Management Module
	©1999 Lukas Hartmann / Atomatrix
*/

#include "zones.h"

void Store_ZON::Set(int n,int x1,int x2,int y1,int y2)
{
	Zones[n].x1=x1;
	Zones[n].y1=y1;
	Zones[n].x2=x2;
	Zones[n].y2=y2;
};

bool Store_ZON::Hit(int n)
{
	if (x>=Zones[n].x1 && x<=Zones[n].x2 && y>=Zones[n].y1 && y<=Zones[n].y2) return true;
	return false;
};

void Store_ZON::Mouse(int mx,int my)
{
	x=mx;
	y=my;
};