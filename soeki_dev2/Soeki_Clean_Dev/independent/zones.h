
#ifndef SOEKI_ZONES
#define SOEKI_ZONES

struct zone
{
	int x1;
	int y1;
	int x2;
	int y2;
};

class Store_ZON
{
	zone Zones[64];
	int x;
	int y;
	public:
		void Set(int n,int x1,int x2,int y1,int y2);
		bool Hit(int n);
		void Mouse(int mx,int my);
};

#endif