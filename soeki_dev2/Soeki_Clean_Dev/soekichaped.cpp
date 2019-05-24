/*
	The Atomatrix ChapEd
	Version 1.0 BeOS
	©1999 Lukas Hartmann / Atomatrix Entertainment
*/

#define NW_WIDTH 410
#define NW_HEIGHT 512

#include <AppKit.h>
#include <InterfaceKit.h>
#include <TranslationKit.h>
#include <StorageKit.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "chedsupport.h"

#define VIEWER_BLIT 'blit'

int cutcount=0;

bool compress=false;

CESupport CE;

int cutolerance=0;
int acts=-1,lgs=0;
int import_mode=0;

void ChapeScan(uint32* work,uint32* layer)
{
	acts=-1;

	int x=0, y=0;
	int found=0, scanmode=0, found2=0;
	int grabbed=0;
	int scanstart=0, scanstop=0;
	int y2=0;
	int grabstart=-1, grabstop=0;

ScanLines:
	found=0;
	CE.poke=work;
	for (x=0;x<NW_WIDTH;x++)
	{
		switch (scanmode)
		{
			case 2:
				found2=0;
				for (y2=scanstart;y2<=scanstop;y2++)
				{
					if (!CE.Tolerated(CE.CPoint(x,y2),cutcolor,cutolerance))
					{
						found2=1;
					};
				};
				if (found2==1 && grabstart==-1) 
				{
					CE.poke=layer;
					CE.Line(x,scanstart,x,scanstop,0xff0000);
					CE.poke=work;
					grabstart=x;
				};
				if (found2==0 && grabstart!=-1)
				{
					CE.poke=layer;
					CE.Line(x,scanstart,x,scanstop,0x0000ff);
					CE.poke=work;
					acts++;
					CE.GrabChape(acts,grabstart,scanstart,x-1,scanstop-1);
				//	CE.ScaleChape(acts,200+acts);
					grabbed=1;
					lgs=acts;
					grabstart=-1;
				};
				if (x==NW_WIDTH-1) {scanmode=0; y=scanstop;}
			break;
			default:
				if (!CE.Tolerated(CE.CPoint(x,y),cutcolor,cutolerance)) found=1;
		};
	};
				
	// Mode 0
			
	if (!found && scanmode==0)
	{
		if (y<NW_HEIGHT-1) {y++; goto ScanLines;}
		else goto ScanEnd;
	};
	if (found && scanmode==0) 
	{
		if (y<NW_HEIGHT-1)
		{
			CE.poke=layer;
			CE.Line(0,y,NW_WIDTH-1,y,0x00ff00);
			CE.poke=work;
			scanmode=1; scanstart=y; y++; goto ScanLines;
		}
		else goto ScanEnd;
	};
			
	// Mode 1
		
	if (!found && scanmode==1)
	{
		CE.poke=layer;
		CE.Line(0,y,NW_WIDTH-1,y,0x00ff00);
		CE.poke=work;
		scanmode=2; scanstop=y;
	};
	
	if (found && scanmode==1)
	{
		if (y<NW_HEIGHT-1) {y++; goto ScanLines;}
		else goto ScanEnd;
	};
				
	// Mode 2
				
	if (scanmode==2)
	{
		if (y<NW_HEIGHT-1) {goto ScanLines;}
		else goto ScanEnd;
	};
ScanEnd: return;
};

class CEView : public BView
{
	public:
		CEView();
		virtual void MouseDown(BPoint where);
		virtual void MouseUp(BPoint where);
		virtual void MouseMoved(BPoint where, uint32 crap, const BMessage* huh);
		virtual void Draw(BRect nowhere);
		
		BBitmap* Work;
		BBitmap* Layer;
		uint32* poke;
		uint32* layerpoke;

		bool Cutting;
		int Cox;
		int Coy;
		int Cnx;
		int Cny;
		
		bool pickmode;
};

CEView::CEView() : BView(BRect(0,0,NW_WIDTH-1,NW_HEIGHT-1),"Heckler und Koch",B_FOLLOW_NONE,B_WILL_DRAW)
{
	Cutting=false;
	pickmode=false;
	
	Work=new BBitmap(BRect(0,0,NW_WIDTH-1,NW_HEIGHT-1),B_RGB32);
	poke=(uint32*)Work->Bits();
	CE.poke=poke;

	CE.ImportImage("/boot/home/code/Soeki/gfx/soekipattern.jpg");

	Layer=new BBitmap(BRect(0,0,NW_WIDTH-1,NW_HEIGHT-1),B_RGB32);
	layerpoke=(uint32*)Layer->Bits();
	CE.poke=layerpoke;

	CE.Copy(Work,Layer);
};

void CEView::Draw(BRect nowhere)
{
	Window()->Lock();
	DrawBitmap(Layer);
	Window()->Unlock();
};	

void CEView::MouseDown(BPoint where)
{
	char buf[20];
	sprintf (buf,"Down: %d,%d",(int)where.x,(int)where.y);
	Window()->SetTitle(buf);

	if (!pickmode)
	{
		Cutting=true;
		Cox=(int)where.x;
		Coy=(int)where.y;
	
		cutcount++;
	}
};

void CEView::MouseMoved(BPoint where, uint32 crap, const BMessage* huh)
{
	if (Cutting && !CE.working)
	{
		Cnx=(int)where.x;
		Cny=(int)where.y;
		CE.Copy(Work,Layer);
		CE.poke=layerpoke;
		
		CE.Line(Cox+1,Coy+1,Cnx+1,Coy+1,0x0);
		CE.Line(Cox+1,Cny+1,Cnx+1,Cny+1,0x0);
		CE.Line(Cox+1,Coy+1,Cox+1,Cny+1,0x0);
		CE.Line(Cnx+1,Coy+1,Cnx+1,Cny+1,0x0);
		
		CE.Line(Cox,Coy,Cnx,Coy,0xffffff);
		CE.Line(Cox,Cny,Cnx,Cny,0xffffff);
		CE.Line(Cox,Coy,Cox,Cny,0xffffff);
		CE.Line(Cnx,Coy,Cnx,Cny,0xffffff);
		Draw(BRect(0,0,0,0));
	};
};

void CEView::MouseUp(BPoint where)
{
	char buf[20];
	sprintf (buf,"Up: %d,%d",(int)where.x,(int)where.y);
	Window()->SetTitle(buf);

	if (pickmode)
	{
		BMessage* msg=new BMessage('pikd');
		msg->AddInt32("x",(int32)where.x);
		msg->AddInt32("y",(int32)where.y);
		Window()->PostMessage(msg);
	};
	
	if (Cutting)
	{	
		CE.poke=poke;
		acts=0;
		CE.GrabChape(acts,Cox,Coy,Cnx,Cny);
		//CE.Box(Cox,Coy,Cnx,Cny,0x0);
		
		be_app->PostMessage(new BMessage(VIEWER_BLIT));

		while (CE.working) {};
		CE.poke=layerpoke;
		CE.Copy(Work,Layer);
	
		Draw(BRect(0,0,0,0));
		Cutting=false;
	};
};

class CEWindow : public BWindow
{
	public:
		CEWindow();
		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage* msg);

		CEView* Display;
		
		// User Interface Elements
		
		BBox* OptionsBox;
		BBox* ScanBox;
		BBox* ImpExpBox;
		BBox* BrowseBox;
		BBox* PickBox;

		BView* PickView;
		
		BCheckBox* CheckDelGrab;
		BButton* PickButton;
		BButton* ScanButton;
		BButton* ImportButton;
		BButton* ExportButton;
		BButton* LeftButton;
		BButton* RightButton;
		BButton* SequenceButton;
		BTextControl* XDelta;
		BTextControl* YDelta;
		BCheckBox* CheckAlpha;
		BSlider* TolSlider;
		BSlider* ChpSlider;

		BFilePanel* OpenFile;
		BFilePanel* SaveFile;
};

void CEWindow::MessageReceived(BMessage* msg)
{
	if (msg->what == 'impr')
	{
		import_mode=0;
		OpenFile->Show();
	};
	
	if (msg->what == 'sequ')
	{
		import_mode=1;
		OpenFile->Show();
	};
	
	if (msg->what == 'expr')
	{
		char buf[40];
		sprintf(buf,"Export %d Chapes?",lgs+1);
		BAlert* expalert=new BAlert("title",buf,"Cancel","Compressed","Raw",B_WIDTH_AS_USUAL, B_OFFSET_SPACING, B_WARNING_ALERT);
		int pressed=expalert->Go();
		printf ("panel: %d\n",pressed);
		if (pressed)
		{
			compress=false;
			if (pressed==1) compress=true;
			SaveFile->Show();
		};
	};

	if (msg->what == 'scan')
	{
		CE.poke=Display->poke;
		ChapeScan(Display->poke,Display->layerpoke);
		Display->Draw(BRect(0,0,0,0));
		
		be_app->PostMessage(VIEWER_BLIT);
	};
	
	if (msg->what == 'brow')
	{
		float valu=ChpSlider->Value();
		int nacts=(int)(((float)(lgs+1)/100)*valu);
		if(nacts!=acts)
		{
			acts=nacts;
			be_app->PostMessage(VIEWER_BLIT);
		};
	};
	
	if (msg->what == 'pick')
	{
		CheckDelGrab->SetEnabled(false);
		PickButton->SetEnabled(false);
		ScanButton->SetEnabled(false);
		ImportButton->SetEnabled(false);
		ExportButton->SetEnabled(false);
		//LeftButton->SetEnabled(false);
		//RightButton->SetEnabled(false);
		TolSlider->SetEnabled(false);
		
		Display->pickmode=true;
	};

	if (msg->what == 'pikd')
	{
		CheckDelGrab->SetEnabled(true);
		PickButton->SetEnabled(true);
		ScanButton->SetEnabled(true);
		ImportButton->SetEnabled(true);
		ExportButton->SetEnabled(true);
		//LeftButton->SetEnabled(true);
		//RightButton->SetEnabled(true);
		TolSlider->SetEnabled(true);
		
		Display->pickmode=false;
		
		int32 x=0;
		int32 y=0;
		
		msg->FindInt32("x",&x);
		msg->FindInt32("y",&y);
		
		uint32 col=CE.CPoint(x,y);
		
		cutcolor=col;
		
		PickView->SetHighColor((col&0xff0000)>>16,(col&0xff00)>>8,col&0xff);
		PickView->FillRect(BRect(0,0,60,41));
	};
	
	if (msg->what == 'tolr')
	{
		cutolerance=TolSlider->Value();
		
		char buf[30];
		sprintf(buf,"Tolerance: %d",cutolerance);
		
		TolSlider->SetLabel(buf);
	};
	
	if (msg->what == 'less' && acts>0)
	{
		acts--;
		ChpSlider->SetValue((int)((float)100/lgs)*(float)acts);
		be_app->PostMessage(VIEWER_BLIT);
	};
	
	if (msg->what == 'more' && acts<lgs)
	{
		acts++;
		ChpSlider->SetValue((int)((float)100/lgs)*(float)acts);
		be_app->PostMessage(VIEWER_BLIT);
	};
};

CEWindow::CEWindow() : BWindow(BRect(50,50,50+NW_WIDTH,204+NW_HEIGHT),"Atomatrix ChapEd v0.1",B_TITLED_WINDOW, B_NOT_RESIZABLE|B_NOT_ZOOMABLE)
{
	Display=new  CEView();
	AddChild (Display);

	// User Interface Elements

	OptionsBox=new BBox(BRect(0,NW_HEIGHT,159,NW_HEIGHT+44),"Options",B_FOLLOW_NONE,B_WILL_DRAW,B_FANCY_BORDER);
	ScanBox=new BBox(BRect(0,NW_HEIGHT+45,159,NW_HEIGHT+154),"Auto Scan",B_FOLLOW_NONE,B_WILL_DRAW,B_FANCY_BORDER);
	ImpExpBox=new BBox(BRect(160,NW_HEIGHT+45,NW_WIDTH-1,NW_HEIGHT+154),"Import/Export",B_FOLLOW_NONE,B_WILL_DRAW,B_FANCY_BORDER);
	PickBox=new BBox(BRect(5,15,75,69),"Cut Color",B_FOLLOW_NONE,B_WILL_DRAW,B_FANCY_BORDER);
	BrowseBox=new BBox(BRect(160,NW_HEIGHT,NW_WIDTH-1,NW_HEIGHT+44),"Browse",B_FOLLOW_NONE,B_WILL_DRAW,B_FANCY_BORDER);
	
	CheckDelGrab=new BCheckBox(BRect(5,15,62,30),"DelGrab","DelGrab",NULL,B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	LeftButton=new BButton(BRect(4,15,14,40),"<","<",new BMessage('less'),B_FOLLOW_LEFT|B_FOLLOW_BOTTOM,B_WILL_DRAW|B_NAVIGABLE);
	RightButton=new BButton(BRect(115,15,125,40),">",">",new BMessage('more'),B_FOLLOW_LEFT|B_FOLLOW_BOTTOM,B_WILL_DRAW|B_NAVIGABLE);
	ImportButton=new BButton(BRect(5,15,62,41),"Import","Import",new BMessage('impr'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	SequenceButton=new BButton(BRect(5,70,62,96),"Sequence","Sequence",new BMessage('sequ'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	ExportButton=new BButton(BRect(5,42,62,69),"Export","Export",new BMessage('expr'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	PickButton=new BButton(BRect(76,15,150,41),"Pick","Pick",new BMessage('pick'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	ScanButton=new BButton(BRect(76,42,150,69),"Scan","Scan",new BMessage('scan'),B_FOLLOW_NONE,B_WILL_DRAW|B_NAVIGABLE);
	
	XDelta=new BTextControl(BRect(64,70,100,96),"xdel","X","64",new BMessage('xdel'));
	YDelta=new BTextControl(BRect(102,70,140,96),"ydel","Y","64",new BMessage('ydel'));
	
	PickView=new BView(BRect(5,5,65,46),"Cut Color",B_FOLLOW_NONE,B_WILL_DRAW);

	TolSlider=new BSlider(BRect(5,70,150,95),"tol","Tolerance",new BMessage('tolr'),0,100,B_TRIANGLE_THUMB,B_FOLLOW_NONE);
	TolSlider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	TolSlider->SetHashMarkCount(6);
	ChpSlider=new BSlider(BRect(15,15,114,40),"chp",NULL,new BMessage('brow'),0,99,B_BLOCK_THUMB);
	
	ChpSlider->SetModificationMessage(new BMessage('brow'));
	
	OptionsBox->SetLabel("Options");
	BrowseBox->SetLabel("Browse");
	ScanBox->SetLabel("Auto Scan");
	ImpExpBox->SetLabel("Import/Export");

	PickBox->AddChild(PickView);
	ScanBox->AddChild(TolSlider);
	ScanBox->AddChild(ScanButton);
	ScanBox->AddChild(PickBox);
	ScanBox->AddChild(PickButton);
	OptionsBox->AddChild(CheckDelGrab);
	BrowseBox->AddChild(ChpSlider);
	BrowseBox->AddChild(LeftButton);
	BrowseBox->AddChild(RightButton);
	ImpExpBox->AddChild(ImportButton);
	ImpExpBox->AddChild(ExportButton);
	ImpExpBox->AddChild(SequenceButton);
	ImpExpBox->AddChild(XDelta);
	ImpExpBox->AddChild(YDelta);

	AddChild(OptionsBox);
	AddChild(BrowseBox);
	AddChild(ScanBox);
	AddChild(ImpExpBox);

	OpenFile=new BFilePanel(B_OPEN_PANEL,new BMessenger(be_app));
	SaveFile=new BFilePanel(B_SAVE_PANEL,new BMessenger(be_app));
};

bool CEWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
};

class CBView : public BView
{
	public:
		CBView();
		virtual void Draw(BRect jumbel);
		void DoBlit();
		
		BBitmap* blitmap;
		uint32* poke;
};

CBView::CBView() : BView(BRect(0,0,NW_WIDTH-1,NW_HEIGHT-1),"View",B_FOLLOW_NONE,B_WILL_DRAW)
{
	blitmap=new BBitmap(BRect(0,0,NW_WIDTH-1,NW_HEIGHT-1),B_RGB32);
	poke=(uint32*)blitmap->Bits();
};

void CBView::Draw(BRect jumbel)
{
	DrawBitmap(blitmap);
};

void CBView::DoBlit()
{
	CE.poke=poke;
	CE.working=true;
	CE.Clear(0xff0000);
	CE.Blit(acts,0,0);
	CE.working=false;
	Draw(BRect(0,0,0,0));
};

class CBWindow : public BWindow
{
	public:
		CBWindow();
		
		CBView* ChapeView;
};

CBWindow::CBWindow() : BWindow(BRect(400,100,500,200),"Browser",B_FLOATING_WINDOW,B_NOT_RESIZABLE|B_NOT_ZOOMABLE|B_NOT_CLOSABLE)
{
	ChapeView=new CBView();

	AddChild(ChapeView);
};

class CEApp : public BApplication
{
	public:
		CEApp();
		virtual void ReadyToRun();
		virtual void MessageReceived(BMessage* msg);
		virtual void RefsReceived(BMessage* msg);

		CEWindow* MainWin;
		CBWindow* BrowserWin;
};

void CEApp::MessageReceived(BMessage* msg)
{
	if (msg->what == VIEWER_BLIT)
	{
		BrowserWin->Lock();
		BrowserWin->ResizeTo(Chapes[acts].w,Chapes[acts].h);
		BrowserWin->ChapeView->DoBlit();
		BrowserWin->Unlock();
	};
	
	if (msg->what == B_SAVE_REQUESTED)
	{
		entry_ref ref;
		const char* name;
		msg->FindRef("directory", &ref);
		msg->FindString("name", &name);
		BEntry entry;
		entry.SetTo(&ref);
		BPath path;
		entry.GetPath(&path);
		path.Append(name);
		
		FILE* f=fopen(path.Path(),"w");
		for (int i=0;i<=lgs;i++)
		{
			if (compress)
			{
				fwrite("AMCC",1,4,f);
			}
			else
			{
				fwrite("AMXC",1,4,f);
			};
			fwrite(&Chapes[i],1,16,f);
			int w=Chapes[i].w+1;
			
			if (compress)
			{
				// Funky compression:
				
				uint32* newchunk=malloc((Chapes[i].w+1)*(Chapes[i].h+1)*4);
				
				uint32 samecnt=0;
				uint32 actualcol=*(Chapes[i].chunk) & 0xffffff;
				uint32 ncnt=0;
				for (int pixels=1; pixels<=(Chapes[i].h+1)*w; pixels++)
				{
					samecnt++;
					
					if ((*(Chapes[i].chunk+pixels) & 0xffffff)!=actualcol || samecnt==0xff)
					{
						//printf ("0x%x * 0x%x\n",samecnt,actualcol);
						*(newchunk+ncnt)=(samecnt<<24)|actualcol;
						samecnt=0;
						actualcol=*(Chapes[i].chunk+pixels) & 0xffffff;
						ncnt++;
					};
				};
				
				fwrite (&ncnt,4,1,f);
				fwrite (newchunk,4,ncnt+1,f);
				
				free(newchunk);
				
				printf ("Old size  : %d bytes\n",w*Chapes[i].h*4);
				printf ("Compressed: %d bytes\n\n",ncnt*4);
			}
			else
			{			
				// Old, raw save:		
				fwrite(Chapes[i].chunk,4,(Chapes[i].w+1)*(Chapes[i].h+1),f);
			};
		};
		fclose(f);
	};
};

void CEApp::RefsReceived(BMessage* msg)
{
	if (import_mode==0)
	{
		entry_ref ref;
		msg->FindRef("refs",&ref);
		BEntry entry(&ref,true);
		BPath path;
		entry.GetPath(&path);
		printf ("Import: %s\n",(char*)path.Path());
		CE.poke=MainWin->Display->poke;
		CE.ImportImage((char*)path.Path());
		CE.Copy(MainWin->Display->Work,MainWin->Display->Layer);
		MainWin->Display->Draw(BRect(0,0,0,0));
	}
	else
	{
		int xdel=strtol(MainWin->XDelta->Text(),0,0);
		int ydel=strtol(MainWin->YDelta->Text(),0,0);
		entry_ref ref;
		msg->FindRef("refs",&ref);
		BEntry* entry=new BEntry(&ref,true);
		BPath path;
		entry->GetPath(&path);
		char* pathname=path.Path();
		int pos=strlen(pathname)-7;
		int px=0,py=0;
		BPoint size;
		CE.poke=MainWin->Display->layerpoke;
		CE.Clear(cutcolor);
		while (entry->Exists() && (py+size.y)<NW_HEIGHT)
		{
			printf ("SeQuence: %s\n",pathname);
			CE.poke=MainWin->Display->poke;
			size=CE.ImportImage(pathname);
			size.x-=xdel;
			size.y-=ydel;
			CE.GrabChape(0,xdel/2,ydel/2,size.x+xdel/2,size.y+ydel/2);
			
			// Load Alpha image - heavy magic
			
			char alphapath[300];
			strncpy(alphapath,pathname,pos);
			alphapath[pos]=0;
			strcat(alphapath,"Alpha");
			strcat(alphapath,&pathname[pos]);
			printf ("Alpha: %s\n",alphapath);
			size=CE.ImportImage(alphapath);
			size.x-=xdel;
			size.y-=ydel;
			CE.GrabChape(1,xdel/2,ydel/2,size.x+xdel/2,size.y+ydel/2);

			int w=(int)size.x;
			
			// Very simple Alpha cutout
			// Threshhold: 50%
			
			for (int y=0; y<size.y; y++)
				for (int x=0; x<size.x; x++)
				{
					uint32 alphapixel=*(Chapes[1].chunk+x+y*w);
					if ((alphapixel>>16)<0x30)
					{
						*(Chapes[0].chunk+x+y*w)=cutcolor;
					};
			};
			
			// Phew... blit our results
			
			CE.poke=MainWin->Display->layerpoke;
			CE.Blit(0,px,py);
			
			int Cox=px;
			int Coy=py;
			int Cnx=px+size.x-1;
			int Cny=py+size.y-1;
			
			// Draw Boundary Box
			
			CE.Line(Cox,Coy,Cnx,Coy,0xff0000);
			CE.Line(Cox,Cny,Cnx,Cny,0xff0000);
			CE.Line(Cox,Coy,Cox,Cny,0xff0000);
			CE.Line(Cnx,Coy,Cnx,Cny,0xff0000);
			
			MainWin->Display->Draw(BRect(0,0,0,0));
			px+=size.x+2;
			if (px+size.x+1>NW_WIDTH-1)
			{
				px=0; py+=size.y+2;
			};
			if (pathname[pos+2]<'9')
			{
				pathname[pos+2]++;
			}
			else
			{
				pathname[pos+1]++;
				pathname[pos+2]='0';
			};
			entry->SetTo(pathname);
		};
		CE.Copy(MainWin->Display->Layer,MainWin->Display->Work);
	};
};

CEApp::CEApp() : BApplication("application/x-vnd.AMXChapEd")
{
};

void CEApp::ReadyToRun()
{
	MainWin=new CEWindow();
	MainWin->Show();
	MainWin->Display->Draw(BRect(0,0,0,0));

	BrowserWin=new CBWindow();
	BrowserWin->Show();
};

int main()
{
	be_app=new CEApp();
	be_app->Run();	
	return 0;
};