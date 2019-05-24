/*
	Phind - A Path Finder
	© 1999 L. Hartmann / Atomatrix
*/

#define NW_WIDTH 320
#define NW_HEIGHT 256

char SOEKI_PATH[]="/BeStuff/code/Soeki/";

#include <AppKit.h>
#include <KernelKit.h>
#include <InterfaceKit.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "independent/structures.h"
chape Chapes[1000];

#include "independent/gfx32.h"
gfx_32 G32;

#define PHIND_SIG "application/x-vnd.atomatrix-Phind"

class PView : public BView
{
	public:
		PView();
		virtual void Draw(BRect puke);
		BBitmap* work;
		uint32* poke;
};

PView::PView() : BView::BView(BRect(0,0,319,255),"The View",B_FOLLOW_NONE,B_WILL_DRAW)
{
	work = new BBitmap(BRect(0,0,319,255),B_RGB32);
	poke = (uint32*)work->Bits();
};

void PView::Draw(BRect puke)
{
	Window()->Lock();
	DrawBitmap(work);
	Window()->Unlock();
};

#include "phind.h"
phaux AUX;

class PWin : public BWindow
{
	public:
		PWin();
		//virtual void MessageReceived(BMessage* msg);
		virtual bool QuitRequested();
		PView* disp;
};

PWin::PWin() : BWindow::BWindow(BRect(600,50,920,50+256),"PHIND",B_TITLED_WINDOW,B_NOT_ZOOMABLE)
{
	disp = new PView();
	AddChild(disp);
};

bool PWin::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
};

class PApp : public BApplication
{
	public:
		PApp();
		virtual void ReadyToRun();
		PWin* pwin;
};

PApp::PApp() : BApplication::BApplication(PHIND_SIG)
{
	pwin = new PWin();
};

void PApp::ReadyToRun()
{
	pwin->Show();
	G32.Use(pwin->disp->poke);
	AUX.DrawGrid();
	for (int y=0; y<20; y++) for (int x=0; x<20; x++)
	{
		AUX.blocks[x][y]=-1;
		if (x==0 || y==0 || x==19 || y==19) {AUX.blocks[x][y] = -2;};
	};
	AUX.blocks[10][10]=0;
	for (int x=0; x<8; x++)
	{
		AUX.blocks[3+x][6]=-2;
		AUX.blocks[3][3+x]=-2;
		AUX.blocks[17][3+x]=-2;
	};
	AUX.Flood(pwin->disp);
	/*for (int y=0; y<20; y++) for (int x=0; x<20; x++)
	{
		AUX.DrawBox(x,y,AUX.blocks[x][y]);
	};
	pwin->disp->Draw(BRect(0,0,0,0));*/
	AUX.startx=5;
	AUX.starty=5;
	int sx=AUX.startx;
	int sy=AUX.starty;
	int dx=10,dy=10;
	int tt=AUX.blocks[sx][sy];
	for (int i=0; i<100; i++)
	{
		int tx=sx; int ty=sy;
		/*if (dy>sy)
		{
			for (int y=1; y>-1; y--) for (int x=-1; x<2; x++)
			{
				if (AUX.blocks[sx+x][sy+y]>0)
				{
					if (AUX.blocks[sx+x][sy+y]<tt) {tt=AUX.blocks[sx+x][sy+y]; tx=sx+x; ty=sy+y;};
				};
			};
		}
		else
		{*/
			for (int y=-1; y<2; y++) for (int x=-1; x<2; x++)
			{
				if (AUX.blocks[sx+x][sy+y]>0)
				{
					if (AUX.blocks[sx+x][sy+y]<tt) {tt=AUX.blocks[sx+x][sy+y]; tx=sx+x; ty=sy+y;};
				};
			};
		//};
		sx=tx;
		sy=ty;
		AUX.DrawBox(sx,sy,0);
		pwin->disp->Draw(BRect(0,0,0,0));
		snooze (60000);
		if (sx==dx && sy==dy) break;
	};
};

int main()
{
	be_app = new PApp();
	be_app->Run();
};