/*
	Texas - Texture Previewer
	© 1999 L. Hartmann / Atomatrix
*/

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256

char SOEKI_PATH[]="/BeStuff/code/Soeki/";

#include <AppKit.h>
#include <InterfaceKit.h>
#include <stdio.h>
#include <string.h>

#include "../platform/beos/assd.h"
#include "../platform/beos/textures.h"

assd ASS;
Store_TEX TEX;

#include "texas.h"

TexBerg TB;

#define TEXAS_SIG "application/x-vnd.atomatrix-Texas"

class TexView : public BView
{
	public:
		TexView();
		virtual void Draw(BRect puke);
		void ShowItToMe();
		BBitmap* work;
		uint32* poke;
};

TexView::TexView() : BView::BView(BRect(0,0,319,255),"The View",B_FOLLOW_NONE,B_WILL_DRAW)
{
	work = new BBitmap(BRect(0,0,319,255),B_RGB32);
	poke = (uint32*)work->Bits();
};

void TexView::Draw(BRect puke)
{
	Window()->Lock();
	DrawBitmap(work);
	Window()->Unlock();
};

void TexView::ShowItToMe()
{
	TB.IsoScape(-1,10,-1,20);
	Draw(BRect(0,0,0,0));
};

class TexWin : public BWindow
{
	public:
		TexWin();
		virtual void MessageReceived(BMessage* msg);
		virtual bool QuitRequested();
		TexView* disp;
		BButton* refresh;
		BTextControl* texfile;
		BTextControl* tex2file;
};

TexWin::TexWin() : BWindow::BWindow(BRect(600,50,920,372),"Texas",B_TITLED_WINDOW,B_NOT_ZOOMABLE)
{
	disp = new TexView();
	refresh = new BButton(BRect(0,256,320,279),"Reload Texture","Reload Texture",new BMessage('refr'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	texfile = new BTextControl(BRect(0,280,320,300),"Texture File","Texture File:","grass.jpg",NULL);
	tex2file = new BTextControl(BRect(0,301,320,321),"Texture File 2","Texture File 2:","desert.jpg",NULL);

	AddChild(disp);
	AddChild(refresh);
	AddChild(texfile);
	AddChild(tex2file);
};

void TexWin::MessageReceived(BMessage* msg)
{
	char* tex=texfile->Text();
	char* tex2=tex2file->Text();
	if (msg->what == 'refr')
	{
		TEX.LoadTexture(0,tex,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT|TEX_TOPRIGHT|TEX_TOPLEFT);
		/*TEX.LoadTexture(1,TEX.MakeName(tex,tex2,TEX_BOTTOMRIGHT),TEX_BOTTOMRIGHT);
		TEX.LoadTexture(2,TEX.MakeName(tex,tex2,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT),TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT);
		TEX.LoadTexture(3,TEX.MakeName(tex,tex2,TEX_BOTTOMLEFT),TEX_BOTTOMLEFT);
		TEX.LoadTexture(4,TEX.MakeName(tex,tex2,TEX_TOPLEFT|TEX_BOTTOMLEFT),TEX_TOPLEFT|TEX_BOTTOMLEFT);
		TEX.LoadTexture(5,TEX.MakeName(tex,tex2,TEX_TOPLEFT),TEX_TOPLEFT);
		TEX.LoadTexture(6,TEX.MakeName(tex,tex2,TEX_TOPLEFT|TEX_TOPRIGHT),TEX_TOPLEFT|TEX_TOPRIGHT);
		TEX.LoadTexture(7,TEX.MakeName(tex,tex2,TEX_TOPRIGHT),TEX_TOPRIGHT);
		TEX.LoadTexture(8,TEX.MakeName(tex,tex2,TEX_TOPRIGHT|TEX_BOTTOMRIGHT),TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadTexture(9,tex2,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT|TEX_TOPRIGHT|TEX_TOPLEFT);*/
		disp->ShowItToMe();
		ASS.Debug ("!! TEXAAAAAS !!\n");
	};
};

bool TexWin::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
};

class TexApp : public BApplication
{
	public:
		TexApp();
		virtual void ReadyToRun();
		TexWin* texwin;
};

TexApp::TexApp() : BApplication::BApplication(TEXAS_SIG)
{
	texwin = new TexWin();
	printf ("Texas Window created!\n");
};

void TexApp::ReadyToRun()
{
	texwin->Show();
	printf ("Texas Window shown!\n");
	
	char* tex="grass.jpg";
	char* tex2="desert.jpg";
	
	TEX.LoadTexture(0,tex,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT|TEX_TOPRIGHT|TEX_TOPLEFT);
	/*TEX.LoadTexture(1,TEX.MakeName(tex,tex2,TEX_BOTTOMRIGHT),TEX_BOTTOMRIGHT);
	TEX.LoadTexture(2,TEX.MakeName(tex,tex2,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT),TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT);
	TEX.LoadTexture(3,TEX.MakeName(tex,tex2,TEX_BOTTOMLEFT),TEX_BOTTOMLEFT);
	TEX.LoadTexture(4,TEX.MakeName(tex,tex2,TEX_TOPLEFT|TEX_BOTTOMLEFT),TEX_TOPLEFT|TEX_BOTTOMLEFT);
	TEX.LoadTexture(5,TEX.MakeName(tex,tex2,TEX_TOPLEFT),TEX_TOPLEFT);
	TEX.LoadTexture(6,TEX.MakeName(tex,tex2,TEX_TOPLEFT|TEX_TOPRIGHT),TEX_TOPLEFT|TEX_TOPRIGHT);
	TEX.LoadTexture(7,TEX.MakeName(tex,tex2,TEX_TOPRIGHT),TEX_TOPRIGHT);
	TEX.LoadTexture(8,TEX.MakeName(tex,tex2,TEX_TOPRIGHT|TEX_BOTTOMRIGHT),TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
	TEX.LoadTexture(9,tex2,TEX_BOTTOMRIGHT|TEX_BOTTOMLEFT|TEX_TOPRIGHT|TEX_TOPLEFT);*/
	
	GTT.array=texwin->disp->poke;
	GTT.Clear();
	
	ASS.Debug("***** ***** *.  .*    .*.   .*****  *\n");
	ASS.Debug("  *   *     `*..*`   .* *.  *<.     *\n");
	ASS.Debug("  *   ****   `**`   .*****. `****.  *\n");
	ASS.Debug("  *   *     .*``*. .*     *.   .>*   \n");
	ASS.Debug("  *   *******    ***       ******`  #\n");
	
	texwin->disp->ShowItToMe();
};

int main()
{
	be_app = new TexApp();
	be_app->Run();
};