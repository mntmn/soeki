/*
	The Phind Core
	©1999 L. Hartmann / Atomatrix
*/

class phaux
{
	public:
	int blocks[20][20];
	int startx;
	int starty;
	int destx;
	int desty;
	void DrawGrid();
	void DrawBox(int x,int y,int val);
	void Flood(PView* disp);
};

void phaux::DrawGrid()
{
	for (int y=0; y<20; y++)
	{
		G32.Line(10,10+y*10,200,10+y*10,0x000000);
		G32.Line(10+y*10,10,10+y*10,200,0x000000);
	};
};

void phaux::DrawBox(int x,int y,int val)
{
	if (val==0) {G32.Rect(11+x*10,11+y*10,19+x*10,19+y*10,255); return;};
	G32.Rect(11+x*10,11+y*10,19+x*10,19+y*10,(254-val*6)<<16);
};

void phaux::Flood(PView* disp)
{
	for (int x=1; x<19; x++) for (int y=1; y<19; y++)
	{
		if (blocks[x][y]==-1)
		{
			int tx=x; int ty=y; int tt=999;
			for (int xx=-1; xx<2; xx++) for (int yy=-1; yy<2; yy++)
			{
				if (blocks[x+xx][y+yy]>=0)
				  if (blocks[x+xx][y+yy]<tt) {tt=blocks[x+xx][y+yy]; tx=x+xx; ty=y+yy;};
			};
			if (tt!=999) blocks[x][y]=blocks[tx][ty]+1;
		};
		snooze (5000);
		DrawBox(x,y,blocks[x][y]);
		disp->Draw(BRect(0,0,0,0));
	};
	for (int x=19; x>0; x--) for (int y=19; y>0; y--)
	{
		if (blocks[x][y]==-1)
		{
			int tx=x; int ty=y; int tt=999;
			for (int xx=-1; xx<2; xx++) for (int yy=-1; yy<2; yy++)
			{
				if (blocks[x+xx][y+yy]>=0)
				  if (blocks[x+xx][y+yy]<tt) {tt=blocks[x+xx][y+yy]; tx=x+xx; ty=y+yy;};
			};
			if (tt!=999) blocks[x][y]=blocks[tx][ty]+1;
		};
		snooze (5000);
		DrawBox(x,y,blocks[x][y]);
		disp->Draw(BRect(0,0,0,0));
	};
};