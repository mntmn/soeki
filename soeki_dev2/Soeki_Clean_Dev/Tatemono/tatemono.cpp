/*
	Tatemono
	Soeki The Plague Buildings Editor
	©1999 Lukas Hartmann / Atomatrix
*/

#include <AppKit.h>
#include <InterfaceKit.h>
#include <TranslationKit.h>
#include <StorageKit.h>
#include "tatemono.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

BTranslationUtils* trans;

uint32* work;
uint32* backgr;
int cmax=0;
int selected_chape=0;

#define NW_WIDTH 298
#define NW_HEIGHT 199

#include "../independent/structures.h"
#include "../independent/zones.h"

Store_ZON ZON;

struct range
{
	uint16 start;
	uint16 end;
};

chape Chapes[500];
range Ranges[100];
NW_Building Tatemono;

void Blit(int num,int x,int y)
{
	uint32* chunk=Chapes[num].chunk;
	if (!chunk) return;
	x-=Chapes[num].xhandle;
	y-=Chapes[num].yhandle;
	//printf ("x: %d y: %d c: %d\n",(int)x,(int)y,(int)num);
	int w=Chapes[num].w;
	int h=Chapes[num].h;
	
	int xsmod=0,xemod=0,loop=0;
	
	if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
	
	if (y<0)
	{
		y=-y;
		chunk += (w+1)*y;
		h -= y;
		y=0;
	};
	if (x<0) {w += x; xsmod = -x; x=0;};
	
	if ((y+h)>=NW_HEIGHT)
	{
		h -= (h+y)-(NW_HEIGHT-1);
	};
	if ((x+w)>=NW_WIDTH)
	{
		xemod = (w+x)-(NW_WIDTH-1);
		w -= xemod;
	};

	if (w<0 || h<0) return;
	
	uint32* poke=work+(y*NW_WIDTH)+x;

	int scrmod=(NW_WIDTH-w)-1;

	while (h-->=0)
	{
		chunk+=xsmod;
		for (loop=w; loop>=0; loop--) 
		{
			if (*(chunk)!=0xff0000)
			{
				if (*(chunk)==0x00ff00)
				{
					*(poke)=(*(poke)&0xfefefe)>>1;
				}
				else
				{
					*(poke) = *(chunk);
				};
			};
			poke++;
			chunk++;
		};
		chunk+=xemod;
		poke+=scrmod;
	};
};

void ShadowBlit(int num,int x,int y)
{
	uint32* chunk=Chapes[num].chunk;
	if (!chunk) return;
	x-=Chapes[num].xhandle;
	y-=Chapes[num].yhandle;
	printf ("x: %d y: %d c: %d\n",(int)x,(int)y,(int)num);
	int w=Chapes[num].w;
	int h=Chapes[num].h;
	
	int xsmod=0,xemod=0,loop=0;
	
	if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
	
	if (y<0)
	{
		y=-y;
		chunk += (w+1)*y;
		h -= y;
		y=0;
	};
	if (x<0) {w += x; xsmod = -x; x=0;};
	
	if ((y+h)>=NW_HEIGHT)
	{
		h -= (h+y)-(NW_HEIGHT-1);
	};
	if ((x+w)>=NW_WIDTH)
	{
		xemod = (w+x)-(NW_WIDTH-1);
		w -= xemod;
	};

	if (w<0 || h<0) return;
	
	uint32* poke=work+(y*NW_WIDTH)+x;

	int scrmod=(NW_WIDTH-w)-1;

	while (h-->=0)
	{
		chunk+=xsmod;
		for (loop=w; loop>=0; loop--) 
		{
			if (*(chunk)!=0xff0000)
			{
				uint32 pix=(*(poke)&0xfefefe)>>1;
				uint32 pix2=(*(chunk)&0xfefefe)>>1;
				
				*(poke)=pix+pix2;

				//*(poke)=(pix&0xfefefe)>>1;
			};
			poke++;
			chunk++;
		};
		chunk+=xemod;
		poke+=scrmod;
	};
};

void LightBlit(int num,int x,int y)
{
	uint32* chunk=Chapes[num].chunk;
	if (!chunk) return;
	x-=Chapes[num].xhandle;
	y-=Chapes[num].yhandle;
	printf ("x: %d y: %d c: %d\n",(int)x,(int)y,(int)num);
	int w=Chapes[num].w;
	int h=Chapes[num].h;
	
	int xsmod=0,xemod=0,loop=0;
	
	if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
	
	if (y<0)
	{
		y=-y;
		chunk += (w+1)*y;
		h -= y;
		y=0;
	};
	if (x<0) {w += x; xsmod = -x; x=0;};
	
	if ((y+h)>=NW_HEIGHT)
	{
		h -= (h+y)-(NW_HEIGHT-1);
	};
	if ((x+w)>=NW_WIDTH)
	{
		xemod = (w+x)-(NW_WIDTH-1);
		w -= xemod;
	};

	if (w<0 || h<0) return;
	
	uint32* poke=work+(y*NW_WIDTH)+x;

	int scrmod=(NW_WIDTH-w)-1;

	while (h-->=0)
	{
		chunk+=xsmod;
		for (loop=w; loop>=0; loop--) 
		{
			if (*(chunk)!=0xff0000)
			{
				uint32 pix=*(poke);
				int16 r=(((pix & 0xff0000)>>16)+20)&0xff;
				int16 g=(((pix & 0xff00)>>8)+20)&0xff;
				int16 b=((pix & 0xff)+20)&0xff;
				
				//if (r>255) r=255;
				//if (g>255) g=255;
				//if (b>255) b=255;
				*(poke)=r<<16|g<<8|b;
				
				//*(poke)=(pix&0xefefef)<<1;
				
			};
			poke++;
			chunk++;
		};
		chunk+=xemod;
		poke+=scrmod;
	};
};

	int LoadChapes(int chapenum,int max,char fname[])
	{
		char* name=fname;
		int res=0;
		char buf[5]="\0\0\0\0";
		int cnt=1;

		FILE* TheFile=fopen(name,"r");

		res=fread(buf,1,4,TheFile);
		int w,h;
		if (strncmp("AMXC",buf,4))
		{
			printf("Sorry, file \"%s\" is no Atomatrix Chape.\n",fname);
			fclose(TheFile);
			goto outback;
		};

	ReadLoop:

		if (Chapes[chapenum].chunk) free(Chapes[chapenum].chunk);

		res=fread(&Chapes[chapenum],1,16,TheFile);

		w=Chapes[chapenum].w+1;
		h=Chapes[chapenum].h+1;
		Chapes[chapenum].chunk=(uint32*)malloc(w*h*4);
		
		res=fread(Chapes[chapenum].chunk,1,w*h*4,TheFile);

		buf="    ";
		res=fread(buf,1,4,TheFile);
		if (!strncmp("AMXC",buf,4) && max>chapenum)
		{
			chapenum++;
			cnt++;
			goto ReadLoop;
		};
		
outback: printf ("%d chapes loaded from %s\n",cnt,fname);
	return cnt;
};

void FreeChapes()
{
	for (int i=0; i<500; i++)
	{
		if (Chapes[i].chunk) free(Chapes[i].chunk);
	};
};

void MidHandle(int i)
{
	Chapes[i].xhandle=Chapes[i].w/2;
	Chapes[i].yhandle=Chapes[i].h/2;
};

//-------------------------------------------------------------------------

ChapeItem::ChapeItem(BBitmap* cicon,char* text) : BListItem()
{
	strcpy(data,text);
	icon=cicon;
};

void ChapeItem::DrawItem(BView *owner, BRect frame, bool complete = false)
{
	rgb_color highlight;
	highlight.red=200;
	highlight.green=200;
	highlight.blue=255;
	
	rgb_color black;
	black.red=0;
	black.green=0;
	black.blue=0;

	if (IsSelected() || complete)
	{
		rgb_color color;
		if (IsSelected())
		{
			color = highlight;
		}
		else
		{
			color = owner->ViewColor();
		};
		owner->SetHighColor(color);
		owner->SetLowColor(color);
		owner->FillRect(frame);
	};

		owner->MovePenTo(frame.left+20, frame.bottom-2);
		owner->SetHighColor(black);
		owner->DrawString(data);
		//owner->DrawBitmap(icon,BPoint(frame.left+1,frame.top));
};

TListView::TListView() : BListView(BRect(5,5,145-B_V_SCROLL_BAR_WIDTH,165),"Chapes")
{
};

void TListView::SelectionChanged()
{
	be_app->PostMessage(new BMessage('ctog'));
};

TEListView::TEListView() : BListView(BRect(5,5,145-B_V_SCROLL_BAR_WIDTH,165),"Events")
{
};

void TEListView::SelectionChanged()
{
	be_app->PostMessage(new BMessage('etog'));
};

TGridView::TGridView() : BView::BView(BRect(554,5,554+40,5+40),"Grid",B_FOLLOW_NONE,B_WILL_DRAW)
{
	/*image=new BBitmap(BRect(0,0,63,63),B_RGB32);
	this->work=(uint32*)background->Bits();
	for (int x=0; x<64; x++)
	{
		for (int y=0; y<64; y++)
		{
			*(this->work+x+y*64)=0;
		};
	};*/
};

void TGridView::Draw(BRect dummy)
{
	Window()->Lock();
	DrawGrid(5,5);
	Window()->Unlock();
};

#define m NW_HEIGHT/2

int matrix[5*5*2]={0,m-16,   32,m-32,  64,m-48,  96,m-64,  128,m-80,
				 32,m,     64,m-16,  96,m-32,  128,m-48, 160,m-64,
				 64,m+16,  96,m,     128,m-16, 160,m-32, 192,m-48,
				 96,m+32,  128,m+16, 160,m,    192,m-16, 224,m-32,
				 128,m+48, 160,m+32, 192,m+16, 224,m,    256,m-16};

uint8 bmap[5][5];

void TGridView::DrawGrid(int w,int h)
{
	rgb_color black = {0,0,0,255};
	rgb_color grey = {100,100,100,255};
	rgb_color green = {0,255,100};
	
	SetLowColor(grey);
	SetHighColor(black);

	FillRect(BRect(0,0,40,40),B_SOLID_HIGH);

	for (int y=0; y<w; y++)
	{
		for (int x=0; x<h; x++)
		{
			SetLowColor(grey);
			if (bmap[x][y]) SetLowColor(green);
			FillRect(BRect(1+x*(40/w),1+y*(40/h),(x+1)*(40/w)-1,(y+1)*(40/h)-1),B_SOLID_LOW);
		};
	};
	
	be_app->PostMessage('upd1');
};

void TGridView::MouseDown(BPoint where)
{
	int x=(int)where.x;
	int y=(int)where.y;
	
	x=(x/8);
	y=(y/8);
	
	bmap[x][y]=1-bmap[x][y];
	Draw();
};

TMainView::TMainView() : BView::BView(BRect(150,50,599-151,249),"Display",B_FOLLOW_NONE,B_WILL_DRAW)
{
	image=trans->GetBitmapFile("/boot/background.png"); //new BBitmap(BRect(0,0,299,199),B_RGB32);
	backgr=(uint32*)image->Bits();
	image2=new BBitmap(BRect(0,0,297,198),B_RGB32);
	work=(uint32*)image2->Bits();
	memcpy(work,backgr,298*199*4);
};

void TMainView::DrawStatics()
{
	memcpy(work,backgr,298*199*4);
	for (int y=0; y<5; y++)
		for (int x=0; x<5; x++)
	{
		if (bmap[x][y]) LightBlit(400,matrix[(x+y*5)*2]-(64*5-NW_WIDTH)/2,matrix[(x+y*5)*2+1]);
	};
	for (int i=0; i<4; i++) if (Tatemono.statics[i])
	{
		if (Tatemono.sshadow[i])
		{
			ShadowBlit(Tatemono.statics[i]-1,298/2,199/2);
		}
		else
		{
			Blit(Tatemono.statics[i]-1,298/2,199/2);
		};
	};
	for (int i=0; i<8; i++) if (Tatemono.events[i].type)
	{
		int chp=Tatemono.events[i].frame;
		Blit(chp,298/2,199/2);
	};
	Blit(401,298-40,199-50);
	Blit(402,298-50,199-40);
	Blit(403,298-40,199-40);
	Blit(404,298-23,199-40);
	Blit(405,298-40,199-23);
	Draw();
};

TMainWin* winlink;
int xmode;
int ymode;

int32 Shifter(void* p)
{
	uint32 but=1;
	BPoint pos;
	char buf[20];

	while (but)
	{
		int stc=Ranges[winlink->t_clist->CurrentSelection(0)].start;
		while (stc<=Ranges[winlink->t_clist->CurrentSelection(0)].end)
		{
			/*Chapes[stc].xhandle-=xmode;
			Chapes[stc].yhandle-=ymode;*/
			
			winlink->Lock();
			winlink->t_mainview->GetMouse(&pos,&but);
			sprintf (buf,"%d",Chapes[stc].xhandle);
			winlink->t_chxoff->SetText(buf);
			sprintf (buf,"%d",Chapes[stc].yhandle);
			winlink->t_chyoff->SetText(buf);
			winlink->Unlock();
			
			int offx=Chapes[stc].w/2+298/2;
			int offy=Chapes[stc].h/2+199/2;
			
			Chapes[stc].xhandle=-(pos.x-offx);
			Chapes[stc].yhandle=-(pos.y-offy);
			
			stc++;
		};
		winlink->t_mainview->DrawStatics();
	};
	return 0;
	winlink->t_mainview->working=false;
};

thread_id shift;

void TMainView::MouseDown(BPoint where)
{
	if (!working)
	{
		/*int mx=(int)where.x;
		int my=(int)where.y;
		ZON.Mouse(mx,my);
		
		xmode=0;
		ymode=0;
		
		if (ZON.Hit(0)) ymode=-1;
		if (ZON.Hit(1)) xmode=-1;
		if (ZON.Hit(2)) xmode=1;
		if (ZON.Hit(3)) ymode=1;
		
		winlink=(TMainWin*)Window();

		if (xmode || ymode)
		{*/
		winlink=(TMainWin*)Window();
		
			working=true; 
			md=true;
			shift=spawn_thread(Shifter,"TTM_Shifter",60,NULL);
			resume_thread(shift);
		//};
	};
};

void TMainView::MouseUp(BPoint where)
{
	md=false;
	working=false;
};

void TMainView::Draw(BRect dummy)
{
	Window()->Lock();
	DrawBitmap(image2);
	Window()->Unlock();
};

TMainWin::TMainWin() : BWindow::BWindow(BRect(100,100,699,500),"Atomatrix - Tatemono",B_TITLED_WINDOW,B_NOT_ZOOMABLE|B_NOT_RESIZABLE)
{
	chapeicon=new BBitmap(BRect(0,0,10,10),B_RGB32); //trans->GetBitmapFile("/boot/test.png");

	t_toolbar=new BBox(BRect(0,0,599,49),"Toolbar",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);
	t_mainview=new TMainView();
	t_chapelist=new BBox(BRect(0,50,149,275),"Chapes",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);
	t_eventlist=new BBox(BRect(600-152,50,599,275),"Events",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);
	t_paramview=new BBox(BRect(0,276,599,400),"Params",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);
	t_eventparams=new BBox(BRect(0,276,599,400),"Params",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);

	t_loadbutton=new BButton(BRect(5,5,44,25),"load","Load",new BMessage('load'));
	t_savebutton=new BButton(BRect(45,5,94,25),"save","Save",new BMessage('save'));
	t_id=new BTextControl(BRect(98,5,140,25),"id","Id","0",new BMessage('idid'));
	t_name=new BTextControl(BRect(144,5,550,25),"name","Name","Untitled",new BMessage('name'));
	t_descr=new BTextControl(BRect(98,28,550,42),"descr","Description","Nothing.",new BMessage('desc'));
	t_grid=new TGridView();

	t_id->SetDivider(10);
	t_name->SetDivider(39);
	t_descr->SetDivider(85);

	t_playbutton=new BButton(BRect(150,250,189,249),"play","Play",new BMessage('play'));
	t_gridbutton=new BButton(BRect(190,250,229,249),"grid","Grid",new BMessage('grid'));
	
	t_gridbutton->SetEnabled(false);
	
	t_addchape=new BButton(BRect(3,176,72,165),"Add","Add",new BMessage('addc'));
	t_addevent=new BButton(BRect(3,176,72,165),"Add","Add",new BMessage('adde'));
	t_remchape=new BButton(BRect(73,176,145,165),"Remove","Remove",new BMessage('remc'));
	t_remevent=new BButton(BRect(73,176,145,165),"Remove","Remove",new BMessage('reme'));

	t_remchape->SetEnabled(false);
	t_remevent->SetEnabled(false);

	t_evchpmenu=new BMenu("Select");
	t_eventname=new BTextControl(BRect(3,10,150,34),"name","Name","Untitled Event",new BMessage('enam'));
	t_eventchape=new BMenuField(BRect(3,35,150,59),"chevent","Chapes",t_evchpmenu);
	t_eventfps=new BTextControl(BRect(3,60,150,84),"fps","Delay","0",new BMessage('efps'));
	t_eventname->SetDivider(be_plain_font->StringWidth("Chapes "));
	t_eventchape->SetDivider(be_plain_font->StringWidth("Chapes "));
	t_eventfps->SetDivider(be_plain_font->StringWidth("Chapes "));

	OpenPanel=new BFilePanel(B_OPEN_PANEL,new BMessenger(be_app));

	/*t_chapelist->SetLabel("Chapes");
	t_eventlist->SetLabel("Events");
	t_paramview->SetLabel("Parameters for Selection");*/
	
	//t_clistbox=new BBox(BRect(3,15,145,175),"Chapes",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);
	//t_elistbox=new BBox(BRect(3,15,145,175),"Events",B_FOLLOW_NONE,B_WILL_DRAW,B_PLAIN_BORDER);

	t_clist=new TListView();
	t_elist=new TEListView();

	t_clistbox=new BScrollView("clistbox",t_clist,B_FOLLOW_NONE,0,false,true);
	t_elistbox=new BScrollView("elistbox",t_elist,B_FOLLOW_NONE,0,false,true);

	t_checkstatic=new BCheckBox(BRect(3,15,103,30),"static","Static",new BMessage ('stts'));
	t_checkshadow=new BCheckBox(BRect(108,15,208,30),"shadow","Shadow",new BMessage ('shad'));
	t_chxoff=new BTextControl(BRect(3,35,103,50),"xoff","X Offset","0",new BMessage ('xoff'));
	t_chyoff=new BTextControl(BRect(3,55,103,70),"yoff","Y Offset","0",new BMessage ('yoff'));

	t_paramview->AddChild(t_checkstatic);
	t_paramview->AddChild(t_checkshadow);
	t_paramview->AddChild(t_chxoff);
	t_paramview->AddChild(t_chyoff);

	//t_clistbox->AddChild(t_clist);
	t_chapelist->AddChild(t_clistbox);
	t_chapelist->AddChild(t_addchape);
	t_chapelist->AddChild(t_remchape);

	//t_elistbox->AddChild(t_elist);
	t_eventlist->AddChild(t_elistbox);
	t_eventlist->AddChild(t_addevent);
	t_eventlist->AddChild(t_remevent);

	t_eventparams->AddChild(t_eventchape);
	t_eventparams->AddChild(t_eventfps);
	t_eventparams->AddChild(t_eventname);

	t_toolbar->AddChild(t_loadbutton);
	t_toolbar->AddChild(t_savebutton);
	t_toolbar->AddChild(t_id);
	t_toolbar->AddChild(t_name);
	t_toolbar->AddChild(t_descr);
	t_toolbar->AddChild(t_grid);

	AddChild(t_toolbar);
	AddChild(t_mainview);
	AddChild(t_chapelist);
	AddChild(t_eventlist);
	AddChild(t_paramview);
	AddChild(t_playbutton);
	AddChild(t_gridbutton);
};

bool TMainWin::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
};

void TMainWin::MessageReceived(BMessage* what)
{
	bool got=false;
	int i;
	int stc;
	FILE* test;

	switch (what->what)
	{
		case 'addc':
			OpenPanel->Show();
			break;
		case 'adde':
			for (i=0; i<8; i++)
			{
				if (!Tatemono.events[i].type) got=true;
				if (got) break;
			};
			if (got)
			{
				t_elist->AddItem(new ChapeItem(chapeicon,"Untitled Event"));
				Tatemono.events[i].type=EVENT_LOOP;
			};
			break;
		case 'stts':
			for (i=0; i<4; i++)
			{
				if (t_checkstatic->Value())
				{
					if (!Tatemono.statics[i])
					{
						got=true;
						Tatemono.statics[i]=Ranges[t_clist->CurrentSelection(0)].start+1;
						t_checkshadow->SetEnabled(true);
					};
				}
				else
				{
					if (Tatemono.statics[i]==Ranges[t_clist->CurrentSelection(0)].start+1)
					{
						got=true;
						Tatemono.statics[i]=0;
						t_checkshadow->SetEnabled(false);
					};
				};
				if (got) break;
			};
			t_mainview->DrawStatics();
			break;
		case 'shad':
			for (i=0; i<4; i++)
			{
				if (Tatemono.statics[i]==Ranges[t_clist->CurrentSelection(0)].start+1)
				{
					got=true;
					Tatemono.sshadow[i]=t_checkshadow->Value();
				};
				if (got) break;
			};
			t_mainview->DrawStatics();
			break;
		case 'xoff':
			stc=Ranges[t_clist->CurrentSelection(0)].start;
			while (stc<=Ranges[t_clist->CurrentSelection(0)].end)
			{
				Chapes[stc].xhandle=strtol(t_chxoff->Text(),0,0);
				stc++;
			};
			t_mainview->DrawStatics();
			break;
		case 'yoff':
			stc=Ranges[t_clist->CurrentSelection(0)].start;
			while (stc<=Ranges[t_clist->CurrentSelection(0)].end)
			{
				Chapes[stc].yhandle=strtol(t_chyoff->Text(),0,0);
				stc++;
			};
			t_mainview->DrawStatics();
			break;
		case 'play':
			i=t_elist->CurrentSelection(0);
			if (i>=0)
			{
				stc=Ranges[Tatemono.events[i].chape].start;
				int end=Ranges[Tatemono.events[i].chape].end;
				while (stc<=end)
				{
					Tatemono.events[i].frame=stc;
					t_mainview->DrawStatics();
					snooze(Tatemono.events[i].delay*1000);
					stc++;
				};
			};
			break;
		case 'efps':
			Tatemono.events[t_elist->CurrentSelection(0)].delay=strtol(t_eventfps->Text(),0,0);
			break;
		case 'echp':
			int16 quest;
			what->FindInt16("chape",&quest);
			Tatemono.events[t_elist->CurrentSelection(0)].chape=quest;
			break;
		case 'enam':
			strncpy(Tatemono.events[t_elist->CurrentSelection(0)].name,t_eventname->Text(),20);
			strncpy(((ChapeItem*)t_elist->ItemAt(t_elist->CurrentSelection(0)))->data,t_eventname->Text(),20);
			t_elist->Invalidate();
			break;
		case 'name':
			strncpy(Tatemono.name,t_name->Text(),20);
			t_name->SetText(Tatemono.name);
			break;
		case 'desc':
			strncpy(Tatemono.descr,t_descr->Text(),20);
			t_name->SetText(Tatemono.descr);
			break;
		case 'save':
			test=fopen("/boot/home/test.amxb","w");
			fwrite ("AMXB",1,4,test);
			got=false;
			for (int i=0; i<4; i++)
			{
				if (Tatemono.statics[i])
				{
					fwrite ("STAT",1,4,test);
					int chp=Tatemono.statics[i]-1;
					fwrite (&Chapes[chp].w,1,4,test);
					fwrite (&Chapes[chp].h,1,4,test);
					fwrite (&Chapes[chp].xhandle,1,4,test);
					fwrite (&Chapes[chp].yhandle,1,4,test);
					fwrite (Chapes[chp].chunk,1,4*(Chapes[chp].w+1)*(Chapes[chp].h+1),test);
					fwrite (&Tatemono.sshadow[i],1,1,test);
				}
				else
				{
					fwrite ("\0\0\0\0",1,4,test);
					got=true;
				};
				if (got) break;
			};
			fwrite ("MTRX",1,4,test);
			fwrite (bmap,1,5*5,test);
			fclose(test);
			break;
		case 'load':
			test=fopen("/boot/home/test.amxb","r");
			char header[5];
			header[4]=0;
			fread (header,1,4,test);
			printf ("Header1: %s\n",header);
			got=false;
			
			for (int i=0; i<4; i++)
			{
				if (!got) {fread (header,1,4,test); printf ("Header2: %s\n",header);};
				if (!strcmp(header,"STAT"))
				{
					Tatemono.statics[i]=i+1;
					fread (&Chapes[i].w,1,4,test);
					fread (&Chapes[i].h,1,4,test);
					fread (&Chapes[i].xhandle,1,4,test);
					fread (&Chapes[i].yhandle,1,4,test);
					
					printf ("w: %d h: %d xhandle: %d yhandle: %d\n",Chapes[i].w,Chapes[i].h,Chapes[i].xhandle,Chapes[i].yhandle);
					
					Chapes[i].chunk=malloc((Chapes[i].w+1)*(Chapes[i].h+1)*4);
					
					fread (Chapes[i].chunk,1,(Chapes[i].w+1)*(Chapes[i].h+1)*4,test);
					fread (&Tatemono.sshadow[i],1,1,test);
					char namebuf[30];
					sprintf (namebuf,"Imported #%d [%d-%d]",i,i,i);
					t_clist->AddItem(new ChapeItem(chapeicon,namebuf));
					Ranges[i].start=i;
					Ranges[i].end=i;
				}
				else
				{
					got=true;
				};
			};
			
			fread (header,1,4,test);
			printf ("Header3: %s\n",header);
			
			if (!strcmp(header,"MTRX"))
			{
				fread (bmap,1,5*5,test);
				printf ("Matrix read.\n");
			};
			fclose(test);
			printf ("Done.");
			t_mainview->DrawStatics();
			t_grid->DrawGrid(5,5);
	};
};

/*
	struct chape
{
	uint32 w;
	uint32 h;
	int32 xhandle;
	int32 yhandle;
	uint32* chunk;
};
*/

TApp::TApp() : BApplication::BApplication(TATEMONO_SIG)
{
};

void TApp::ReadyToRun()
{
	LoadChapes(400,400,"/boot/home/code/Soeki/gfx/markers.amxc");
	LoadChapes(401,405,"/boot/home/code/Soeki/gfx/tat_cross.amxc");
	
	/*	LightBlit(401,298-40,199-50);
	LightBlit(402,298-50,199-40);
	LightBlit(403,298-40,199-40);
	LightBlit(404,298-23,199-40);
	LightBlit(405,298-40,199-23);*/
	
	ZON.Set(0,298-40,298-24,199-50,199-41);
	ZON.Set(1,298-50,298-41,199-40,199-24);
	ZON.Set(2,298-23,298-13,199-40,199-24);
	ZON.Set(3,298-40,298-24,199-23,199-13);
	
	t_mainwin=new TMainWin();
	t_mainwin->Show();
	t_mainwin->t_grid->Draw();
};

void TApp::MessageReceived(BMessage* msg)
{
	bool got=false;
	int chp=Ranges[t_mainwin->t_clist->CurrentSelection(0)].start;
	
	switch (msg->what)
	{
		case 'upd1':
			t_mainwin->t_mainview->DrawStatics();
			break;
		case 'upd2':
			t_mainwin->t_mainview->Draw();
			break;
		case 'ctog':
			if (t_mainwin->t_clist->CurrentSelection(0)>=0)
			{
				if (t_mainwin->t_paramview->Window()==NULL)
				{
					t_mainwin->Lock();
					t_mainwin->RemoveChild(t_mainwin->t_eventparams);
					t_mainwin->AddChild(t_mainwin->t_paramview);
					t_mainwin->t_elist->DeselectAll();
					t_mainwin->Unlock();
				};
			};
			t_mainwin->Lock();
			t_mainwin->t_checkstatic->SetValue(B_CONTROL_OFF);
			t_mainwin->t_checkshadow->SetValue(B_CONTROL_OFF);
			t_mainwin->t_checkshadow->SetEnabled(false);
			
			char buffer[10];
			sprintf (buffer,"%d",Chapes[chp].xhandle);
			t_mainwin->t_chxoff->SetText(buffer);
			sprintf (buffer,"%d",Chapes[chp].yhandle);
			t_mainwin->t_chyoff->SetText(buffer);
			
			for (int i=0; i<4; i++)
			{
				if (Tatemono.statics[i]==chp+1)
				{
					got=true;
					t_mainwin->t_checkstatic->SetValue(B_CONTROL_ON);
					t_mainwin->t_checkshadow->SetValue(Tatemono.sshadow[i]);
					t_mainwin->t_checkshadow->SetEnabled(true);
				};
				if (got) break;
			};
			t_mainwin->Unlock();
			break;
		case 'etog':
			if (t_mainwin->t_elist->CurrentSelection(0)>=0)
			{
				if (t_mainwin->t_paramview->Window()!=NULL)
				{
					t_mainwin->Lock();
					t_mainwin->RemoveChild(t_mainwin->t_paramview);
					t_mainwin->AddChild(t_mainwin->t_eventparams);
					t_mainwin->t_clist->DeselectAll();
					t_mainwin->Unlock();
				};
			};
			break;
	};
};

void TApp::RefsReceived(BMessage* msg)
{
	char buffer[100];
	entry_ref ref;
	msg->FindRef("refs",&ref);
	BEntry entry(&ref,true);
	BPath path;
	entry.GetPath(&path);
	entry.GetName(buffer);
	printf ("Import: %s\n",(char*)path.Path());
	
	int count=LoadChapes (cmax,cmax+100,(char*)path.Path());
	char buffer2[100];
	sprintf(buffer2,"%s [%d-%d]",buffer,cmax,cmax+count-1);

	ChapeItem* newitem=new ChapeItem(t_mainwin->chapeicon,buffer2);
	
	t_mainwin->Lock();
	t_mainwin->t_clist->AddItem(newitem);
	t_mainwin->Unlock();
	
	Ranges[t_mainwin->t_clist->IndexOf(newitem)].start=cmax;
	Ranges[t_mainwin->t_clist->IndexOf(newitem)].end=cmax+count-1;	
	
	cmax+=count;
	
	BMessage* chpmsg=new BMessage('echp');
	chpmsg->AddInt16("chape",t_mainwin->t_clist->IndexOf(newitem));
	t_mainwin->t_evchpmenu->AddItem(new BMenuItem((char*)path.Path(),chpmsg));
	/*if (!firstchapes)
	{
		firstchapes=true;
		MidHandle(0);
		Blit (0,298/2,198/2);
		t_mainwin->t_mainview->Draw();
	};*/
};

int main()
{
	be_app=new TApp();
	be_app->Run();
	FreeChapes(); // Clean up!
};