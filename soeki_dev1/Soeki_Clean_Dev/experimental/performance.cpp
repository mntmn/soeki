/*
	Atomatrix Triangle() Performance Test
	©1999 Lukas Hartmann / Atomatrix
*/

#include <AppKit.h>
#include <InterfaceKit.h>
#include <KernelKit.h>
#include <StorageKit.h>
#include <TranslationKit.h>

#include <math.h>

#include <stdio.h>


#include "/boot/home/Desktop/trimapper.cpp"

#define PAPP_SIG "application/x-vnd.TrianglePerformance"

Magic2 GTT(640);

unsigned int ltab[7][7];
unsigned int Light[20][10];

float global_fps=0;

class Perform : public BView
{
	public:
		virtual void Draw(BRect huh);
		Perform();
		virtual void Pulse();
		void TriRaster();
		int mx;
		int my;
		int oldx;
		int oldy;
		BBitmap* PBitmap;
};

void Perform::Draw(BRect huh)
{
	DrawBitmap(PBitmap);
};

Perform::Perform() : BView::BView(BRect(0,0,639,479),"View",B_FOLLOW_NONE,B_WILL_DRAW|B_PULSE_NEEDED)
{
	PBitmap=new BBitmap(BRect(0,0,639,479),B_RGB32);
	printf ("LightTable init:\n");
	for (int y=0;y<4;y++)
	{
		for (int x=0;x<4;x++)
		{
			ltab[x][y]=127+(x+y)*10;
			ltab[6-x][y]=127+(x+y)*10;
			ltab[x][6-y]=127+(x+y)*10;
			ltab[6-x][6-y]=127+(x+y)*10;
			printf ("[%d]",127+(x+y)*10);
		};
		printf ("\n");
	};
	printf ("Done.\n");
};

void Perform::Pulse()
{
	// Clear old light

	BPoint where;
	uint32 really;

	Window()->Lock();
	GetMouse(&where,&really,false);
	Window()->Unlock();
	
	if ((((int)where.x/32)!=oldx) || (((int)where.y/32)!=oldy))
	{
		oldx=(int)where.x/32;
		oldy=(int)where.y/32;
		
		int rows,cols;
		
		for (rows=my-3;rows<my+3;rows++)
		{
			for (cols=mx-3;cols<mx+3;cols++)
			{
				if (cols>=0 && rows>=0 && cols<=19 && rows<=9)
				{
					Light[cols][rows]=127;
				};
			};
		};
	
		mx=(int)where.x/32;
		my=(int)where.y/32;
	
		// Copy new light
		int x=0,y=0;
	
		for (rows=my-3;rows<my+3;rows++)
		{
			x=0;
			for (cols=mx-3;cols<mx+3;cols++)
			{
				if (cols>=0 && rows>=0 && cols<=19 && rows<=9)
				{
					Light[cols][rows]=ltab[x][y];
				};
				x++;
			};
			y++;
		};
		TriRaster();
		BWindow* win=Window();
		
		char buf[20];
		sprintf (buf,"%f FPS",global_fps);
		
		win->SetTitle(buf);
	};
};

void Perform::TriRaster()
{
	int lsub,lsub2,lsub3,lsub4;

	float coords1[6],coords2[6],coords3[6];

	//int heaps=0;
	float timeheap=0;
	int before,after;
	int rows,cols;
		
	for (rows=0;rows<9;rows++)
	{
		for (cols=0;cols<19;cols++)
		{
			lsub=Light[cols][rows]/2;
			lsub2=Light[cols+1][rows]/2;
			lsub3=Light[cols][rows+1]/2;
			lsub4=Light[cols+1][rows+1]/2;
			
			coords1[0]=10+cols*32;
			coords1[1]=10+rows*32;
			coords1[2]=1;
			coords1[3]=0;
			coords1[4]=0;
			coords1[5]=lsub;
			
			coords2[0]=10+cols*32+32;
			coords2[1]=10+rows*32;
			coords2[2]=1;
			coords2[3]=255;
			coords2[4]=0;
			coords2[5]=lsub2;
			
			coords3[0]=10+cols*32;
			coords3[1]=10+rows*32+32;
			coords3[2]=1;
			coords3[3]=0;
			coords3[4]=255;
			coords3[5]=lsub3;

			before = real_time_clock_usecs();
			GTT.Triangle(coords1,coords2,coords3);
			after = real_time_clock_usecs();

			timeheap+=after-before;
							
			coords1[0]=10+cols*32+32;
			coords1[1]=10+rows*32;
			coords1[2]=1;
			coords1[3]=255;
			coords1[4]=0;
			coords1[5]=lsub2;
			
			coords2[0]=10+cols*32+32;
			coords2[1]=10+rows*32+32;
			coords2[2]=1;
			coords2[3]=255;
			coords2[4]=255;
			coords2[5]=lsub4;
			
			coords3[0]=10+cols*32;
			coords3[1]=10+rows*32+32;
			coords3[2]=1;
			coords3[3]=0;
			coords3[4]=255;
			coords3[5]=lsub3;

			before=real_time_clock_usecs();
			GTT.Triangle(coords1,coords2,coords3);
			after=real_time_clock_usecs();

			timeheap+=after-before;
		};
	};
	
	global_fps=1/(timeheap/1000000);
	
	Draw(BRect(0,0,0,0));
};

class PWindow : public BWindow
{
	public:
					PWindow();
		virtual bool	QuitRequested();
		Perform		PDisplay;
};

PWindow::PWindow() : BWindow(BRect(50,50,690,520),"0 FPS",B_TITLED_WINDOW,B_WILL_DRAW)
{
	AddChild(&PDisplay);
};

bool PWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return BWindow::QuitRequested();
};

class PApp: public BApplication
{
	public:
					PApp();
		virtual void	ReadyToRun();
	private:
		PWindow*		PWin;
};

PApp::PApp() : BApplication(PAPP_SIG)
{
};

void PApp::ReadyToRun()
{
	PWin=new PWindow;
	GTT.array=(uint32*)PWin->PDisplay.PBitmap->Bits();
	printf ("Target bitmap: %x\n",GTT.array);
	if (!GTT.array)
	{
		printf ("Error: Bitmap not properly initialized!\n");
		exit(666);
	};

	GTT.TextureBitmap=GTT.TextureTrans->GetBitmap("/boot/home/code/Soeki/tex/desert.jpg");
	GTT.array_tex1=(uint32*)GTT.TextureBitmap->Bits();

	PWin->Show();
};

int main()
{
	for (int y=0;y<10;y++)
	{
		for (int x=0;x<20;x++)
		{
			Light[x][y]=127;
		};
	};
	be_app=new PApp;
	be_app->Run();
	return 0;
};