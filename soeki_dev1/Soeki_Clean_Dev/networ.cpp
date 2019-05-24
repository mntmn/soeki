 
/*	What will once be Networ... boy this editor is much better than crappy SuperTed
	©Lukas Hartmann / Atomatrix, 1998/1999/2000                                           */

//  BeOS Version

	#include <AppKit.h>
	#include <InterfaceKit.h>
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	
	#include "independent/structures.h"
	
	#include "independent/zones.h"
	Store_ZON ZON;
	#include "platform/beos/assd.h"
	assd ASS;
	#include "independent/gfx32.h"
	gfx_32 G32(640,480);
	#include "platform/beos/storage.h"
	Store_DAT DAT;
	#include "platform/beos/textures.h"
	Store_TEX TEX;
	#include "platform/beos/master.h"
	Store NW;
	#include "independent/engine.h"
	Store_GFX GFX;
	#include "independent/processing.h"
	Store_PRC PRC;
	
	#include "network.h"
	Store_NET NET(&NW);
	
	#include "zoomwater.cpp"
	
	AlphasWater ZWT;
	
	class SoekiApp : public BApplication
	{
		public:
			SoekiApp();
			virtual void ReadyToRun();
			virtual bool QuitRequested();
			void main_thread();
	};
	
	int32 launcher(void* p)
	{
		ASS.Debug ("launcher()\n");
		SoekiApp* sapp=(SoekiApp*)be_app;
		sapp->main_thread();
		return B_OK;
	};
	
	bool SoekiApp::QuitRequested()
	{
		ASS.Debug("SoekiApp::QuitRequested()\n");
		NW.NWWindow->PostMessage(B_QUIT_REQUESTED);
		return true;
	};
	
	SoekiApp::SoekiApp() : BApplication::BApplication(SOEKI_SIG)
	{
	};
	
	char SERVER_IP[100];

	bool configured;
	
	class SNetConfWin : public BWindow
	{
		public:
			SNetConfWin();
			virtual void MessageReceived(BMessage* msg);
		
			BBox* Outline;
				BBox* ServBox;
					BTextControl* ServIP;
				BBox* ClientBox;
					BTextControl* ClientIP;
					BTextControl* ClientID;
					BTextControl* ClientNick;
				BButton* Cancel;
				BButton* OK;
	};
	
	void SNetConfWin::MessageReceived(BMessage* msg)
	{
		if (msg->what=='done')
		{
			configured=true;
		};
		if (msg->what=='canc')
		{
			be_app->PostMessage(B_QUIT_REQUESTED);
		};
	};
	
	SNetConfWin::SNetConfWin() : BWindow::BWindow(BRect(355,306,355+378,306+182),"Soeki Networking",B_MODAL_WINDOW,B_NOT_RESIZABLE|B_NOT_ZOOMABLE)
	{
		Outline=new BBox(BRect(0,0,378,182),"box1",B_FOLLOW_NONE,B_WILL_DRAW|B_FRAME_EVENTS|B_NAVIGABLE_JUMP,B_PLAIN_BORDER);
		ServBox=new BBox(BRect(5,6,373,65),"box2",B_FOLLOW_NONE,B_WILL_DRAW|B_FRAME_EVENTS|B_NAVIGABLE_JUMP,B_FANCY_BORDER);
		ClientBox=new BBox(BRect(5,70,373,144),"box3",B_FOLLOW_NONE,B_WILL_DRAW|B_FRAME_EVENTS|B_NAVIGABLE_JUMP,B_FANCY_BORDER);
		ServBox->SetLabel("Server Settings");
		ClientBox->SetLabel("Client Settings");
		ServIP=new BTextControl(BRect(7,22,360,41),"txt1","Server IP","192.168.0.1",new BMessage('txt1'));
		ClientIP=new BTextControl(BRect(7,17,360,36),"txt2","Local IP","192.168.0.1",new BMessage('txt2'));
		ClientID=new BTextControl(BRect(10,45,54,64),"txt3","ID","0",new BMessage('txt3'));
		ClientID->SetDivider(be_plain_font->StringWidth("ID "));
		ClientIP->SetDivider(be_plain_font->StringWidth("Local IP "));
		ServIP->SetDivider(be_plain_font->StringWidth("Server IP "));
		ClientNick=new BTextControl(BRect(65,45,360,64),"txt4","Your Nick","gl.minuteman",new BMessage('txt4'));
		ClientNick->SetDivider(be_plain_font->StringWidth("Your Nick "));
		Cancel=new BButton(BRect(170,150,270,172),"but1","Cancel",new BMessage('canc'));
		OK=new BButton(BRect(273,150,372,172),"but2","OK",new BMessage('done'));
		
		ServBox->AddChild(ServIP);
		ClientBox->AddChild(ClientIP);
		ClientBox->AddChild(ClientID);
		ClientBox->AddChild(ClientNick);
		Outline->AddChild(ServBox);
		Outline->AddChild(ClientBox);
		Outline->AddChild(OK);
		
		OK->MakeDefault(true);
		
		AddChild(Outline);
	};
	
	void SoekiApp::ReadyToRun()
	{
		// Network Config
	
		configured=false;
		
		SNetConfWin* config=new SNetConfWin();
		config->Show();
		
		while (!configured)
		{
			snooze(100000);
		};
		
		strcpy(SERVER_IP,config->ServIP->Text());
		
		NW_Player player;
		
		player.id=strtol(config->ClientID->Text(),0,0);
		strcpy(player.hostname,config->ClientIP->Text());
		strcpy(player.nickname,config->ClientNick->Text());
		player.artifical=false;
	
		config->Lock();
		config->Quit();
		//delete config;
	
		NET.ConnectTo(SERVER_IP,player);
		printf ("NET.ConnectTo() returned.\n");
	
	
		// Submodule Connections -----------------------------
		
		NW.Textures=TEX.Connect(NW.SOEKI_PATH);
		DAT.Connect(NW.SOEKI_PATH);
		NW.Connect(&ASS,&G32,&DAT);
		PRC.Connect(&NW,&G32,&NET);
		GFX.Connect(&NW,&G32);
		G32.Connect(NW.Chapes);
		
		printf ("Submodules connected.\n");
		
		NW.LoadChapes(0,0,"gfx/distort.amxc");
		G32.distort=(uint8*)malloc(256*300);
		for (int x=0; x<256*256; x++) *(G32.distort+x)=(*(NW.Chapes[0].chunk+x)&0xff);

		
		// ---------------------------------------------------

		int NW_WIDTH=NW.NW_WIDTH;
		int NW_HEIGHT=NW.NW_HEIGHT;
		
		ZWT.init();
		NW.Chapes[668].chunk=ZWT.array;
		NW.Chapes[668].w=255;
		NW.Chapes[668].h=255;
		
		NW.NWWindow=new NetworDisplay();
		ASS.Debug ("Waiting for Kernel\n");

		NW.NWWindow->Show();
		
		char debuffer[20];
		
		while (!NW.NWWindow->didthejob)
		{
			snooze(50000);
			if (modifiers())
			{
				ASS.Debug ("\nKernel timeout! Terminating.\n");
				be_app->PostMessage(B_QUIT_REQUESTED);
				exit(666);
			};
		};
		
		NW.running=true;
		
		NW.Chunky=NW.NWWindow->kick_me+NW_WIDTH*NW_HEIGHT;

		ASS.Debug ("\n.******         ****** *  .* *\n");
		ASS.Debug ("*    '* .*****. *   '* * .*  *\n");
		ASS.Debug ("*.      *'   '* *      *.*   *\n");
		ASS.Debug ("'*****. *     * *****  **    *\n");
		ASS.Debug ("      * *     * *      *'*   *\n");
		ASS.Debug ("*.   .* *.   .* *   .* * '*  *\n");
		ASS.Debug ("******' '*****' ****** *  '* *\n\n");
		ASS.Debug ("  --= T H E  P L A G U E =--  \n\n");
		
		
		if (!NW.Chunky)
		{
			ASS.Debug ("Error: Bits() returned zero.\n");
			exit(666);
		};

		status_t puke;
		status_t puke2;
		thread_id gfx_thread=spawn_thread(launcher,"soeki_main",60,NULL);

		char buffer[100];
		sprintf (buffer,"soeki_gfx thread id: 0x%x\n",(unsigned int)gfx_thread);
		
		ASS.Debug (buffer);

		puke2=wait_for_thread(gfx_thread,&puke);

		if (puke2 != B_OK)
		{
			ASS.Debug ("Error: Couldn't spawn soeki_gfx thread!\n");
			printf ("Error       : Couldn't spawn soeki_gfx thread!\n");
			printf ("What's wrong: %s\n",strerror(puke2));
		};
		
		printf ("SoekiApp::main_thread() returned.\n");
	};
	
	int32 Flipper(void* p)
	{
		Store* universe=(Store*) p;
		
		while (universe->running)
		{
			// Rest a little...
			
			snooze(1000);

			if (universe->PreMain)
			{
				universe->NWWindow->HardwareBlit(0,480,0,0,639,479);
				//universe->NWWindow->HardwareSync();
				universe->PreMain=false;
			};

			int HEIGHT=universe->NW_HEIGHT;
			int WIDTH=universe->NW_WIDTH;

			int num=62;
			
			uint32* chunk=universe->Chapes[num].chunk;
			
			int x=universe->MouseX();
			int y=universe->MouseY();

			uint32* work=universe->NWWindow->kick_me;
			
			// Our very own Blit...
			
			x-=universe->Chapes[num].xhandle;
			y-=universe->Chapes[num].yhandle;
			int w=universe->Chapes[num].w;
			int h=universe->Chapes[num].h;
			
			int xsmod=0,xemod=0,loop=0;
			
			if ((y+h)>=HEIGHT)
			{
				h -= (h+y)-(HEIGHT-1);
			};
			if ((x+w)>=WIDTH)
			{
				xemod = (w+x)-(WIDTH-1);
				w -= xemod;
			};
			
			uint32* poke=work+(y*WIDTH)+x;
			int scrmod=(WIDTH-w)-1;
	
			while (h-->=0)
			{
				chunk+=xsmod;
				for (loop=w; loop>=0; loop--) 
				{
					if (*(chunk)!=0xff0000)
					{
						/*int r=(*(poke) & 0x00ff0000) >> (16+1);
						int g=(*(poke) & 0x0000ff00) >> (8+1);
						int b=(*(poke) & 0x000000ff) >> 1;
						
						int rw=(*(chunk) & 0x00ff0000) >> (16+1);
						int gw=(*(chunk) & 0x0000ff00) >> (8+1);
						int bw=(*(chunk) & 0x000000ff) >> 1;
						
						r=(r+rw);
						g=(g+gw);
						b=(b+bw);
						
						*(poke)=r<<16|g<<8|b;*/
						
						*(poke)=*(chunk);
					};
					poke++;
					chunk++;
				};
				chunk+=xemod;
				poke+=scrmod;
			};

			// That's it.

		};
		
		return 0;
	};

	void SoekiApp::main_thread()
	{
		int NW_WIDTH=NW.NW_WIDTH;
		int NW_HEIGHT=NW.NW_HEIGHT;

		int i=0;
		int x=0;
		int y=0;

		Dat* TheFile=0;
		int res=0;
		
		for (y=0;y<100;y++)
		{
			for (x=0;x<100;x++)
			{
				NW.Blox[x][y]=0;
				//NW.Tex[x][y]=(int)(((float)rand()/(float)RAND_MAX)*4);
				NW.Tex[x][y]=0;
			};
		};
		
		for (y=1;y<99;y++)
		{
			for (x=1;x<99;x++)
			{
				NW.MakeLight(x,y);
			};
		};

		NW.ToFront();
		
		int mx=0;
		int my=0;

		int cnt=0;
	
		// Gogogo!
		G32.Use(NW.Chunky);
		for (uint32 fill=0; fill<NW_WIDTH*NW_HEIGHT; fill++) *(NW.Chunky+fill)=0;
		resume_thread(spawn_thread(Flipper,"Flipper",20,&NW));

		NW.LoadChapes(0,3,"gfx/menu.amxc");		
		NW.LoadChapes(62,63,"gfx/pointers.amxc");

		int selection=0;

		while (!selection)
		{
			snooze(10000);
			for (uint32 fill=0; fill<NW_WIDTH*NW_HEIGHT; fill++) *(NW.Chunky+fill)=0;
			mx=NW.MouseX();
			my=NW.MouseY();
			
			G32.Blit(0,NW_WIDTH/2-NW.Chapes[0].w/2,NW_HEIGHT/2-20);
			G32.Blit(1,NW_WIDTH/2-NW.Chapes[1].w/2,NW_HEIGHT/2+20);
						
			if (mx>=NW_WIDTH/2-NW.Chapes[0].w/2 && mx<=NW_WIDTH/2+NW.Chapes[0].w/2)
			{
				if (my>=NW_HEIGHT/2-20 && my<=NW_HEIGHT/2+20+NW.Chapes[1].h)
				{
					if (my<NW_HEIGHT/2+20)
					{
						G32.Blit(2,NW_WIDTH/2-NW.Chapes[2].w/2,NW_HEIGHT/2-23);
						if (NW.MouseButt()) selection=1;
					}
					else
					{
						G32.Blit(3,NW_WIDTH/2-NW.Chapes[3].w/2,NW_HEIGHT/2+17);
						if (NW.MouseButt()) selection=2;
					};
				};
			};
			
			NW.Show();
		};

		char Out[50];

		NW.LoadChapes(0,48,"gfx/font.amxc");
		NW.LoadChapes(50,55,"gfx/consymbols.amxc");
		NW.LoadChapes(56,57,"gfx/console.amxc");
		
		NW.Console_Running=true;
		NW.OutCon("WELCOME TO SOEKI THE PLAGUE");
		NW.OutCon("RUNNING ON THE NETWOR ENGINE");
		NW.OutCon("FOR <I1>");
		NW.OutCon("COPYRIGHT 2000 ATOMATRIX");
		
		NW.LoadChapes(60,61,"gfx/markers.amxc");
		NW.LoadChapes(100,123,"gfx/tank.amcc");
		NW.LoadChapes(400,408,"gfx/selection.amxc");
		
		NW.LoadChapes(124,127,"gfx/tank_fire000deg.amcc");
		NW.LoadChapes(128,131,"gfx/tank_fire045deg.amcc");
		NW.LoadChapes(132,135,"gfx/tank_fire090deg.amcc");
		NW.LoadChapes(136,139,"gfx/tank_fire135deg.amcc");
		NW.LoadChapes(140,143,"gfx/tank_fire180deg.amcc");
		NW.LoadChapes(144,147,"gfx/tank_fire225deg.amcc");
		NW.LoadChapes(148,151,"gfx/tank_fire270deg.amcc");
		NW.LoadChapes(152,155,"gfx/tank_fire315deg.amcc");
		
		NW.LoadChapes(160,175,"gfx/explosion.amxc");
		
		/*NW.LoadChapes(180,180,"gfx/background.amxc");
		NW.LoadChapes(181,184,"gfx/options.amxc");*/
		
		NW.LoadChapes(180,180,"gfx/radar.amxc");
		NW.Chapes[180].xhandle=10;
		NW.Chapes[180].yhandle=-(NW.Chapes[180].h-10);
		
		for (i=160; i<175; i++)
		{
			NW.MidHandle(i);
		};
		
		for (i=124; i<156; i++)
		{
			NW.Chapes[i].xhandle=63;
			NW.Chapes[i].yhandle=63;
		};

		NW.LoadChapes(500,503,"gfx/slides.amxc");
		
		NW.LoadChapes(510,512,"gfx/aux.amxc");
		NW.LoadChapes(512,513,"gfx/energy.amxc");

		NW.LoadChapes(550,551,"gfx/objects1.amxc");
		NW.LoadChapes(560,561,"gfx/template.amxc");

		TEX.LoadTexture(0,"desert.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);

		//TEX.LoadTexture(20,"shield.jpg",0);

		/*TEX.LoadTexture(1,"gr_ur.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);
		TEX.LoadTexture(2,"gr_bl.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);
		TEX.LoadTexture(3,"gr_br.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);
		*/
		
		TEX.LoadRawTexture(1,"desert-grass2-br.dat",TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(2,"desert-grass2-b.dat",TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(3,"desert-grass2-bl.dat",TEX_BOTTOMLEFT);
		TEX.LoadRawTexture(4,"desert-grass2-l.dat",TEX_TOPLEFT|TEX_BOTTOMLEFT);
		TEX.LoadRawTexture(5,"desert-grass2-tl.dat",TEX_TOPLEFT);
		TEX.LoadRawTexture(6,"desert-grass2-t.dat",TEX_TOPLEFT|TEX_TOPRIGHT);
		TEX.LoadRawTexture(7,"desert-grass2-tr.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(8,"desert-grass2-r.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(9,"desert-grass2-bri.dat",TEX_TOPLEFT);
		TEX.LoadRawTexture(10,"desert-grass2-bli.dat",TEX_TOPLEFT|TEX_TOPRIGHT);
		TEX.LoadRawTexture(11,"desert-grass2-tri.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(12,"desert-grass2-tli.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(13,"desert-grass2-xt.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(14,"desert-grass2-xb.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadTexture(15,"grass2.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);

		TEX.LoadRawTexture(16,"grass2-stone-br.dat",TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(17,"grass2-stone-b.dat",TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(18,"grass2-stone-bl.dat",TEX_BOTTOMLEFT);
		TEX.LoadRawTexture(19,"grass2-stone-l.dat",TEX_TOPLEFT|TEX_BOTTOMLEFT);
		TEX.LoadRawTexture(20,"grass2-stone-tl.dat",TEX_TOPLEFT);
		TEX.LoadRawTexture(21,"grass2-stone-t.dat",TEX_TOPLEFT|TEX_TOPRIGHT);
		TEX.LoadRawTexture(22,"grass2-stone-tr.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(23,"grass2-stone-r.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(24,"grass2-stone-bri.dat",TEX_TOPLEFT);
		TEX.LoadRawTexture(25,"grass2-stone-bli.dat",TEX_TOPLEFT|TEX_TOPRIGHT);
		TEX.LoadRawTexture(26,"grass2-stone-tri.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(27,"grass2-stone-tli.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadRawTexture(28,"grass2-stone-xt.dat",TEX_TOPRIGHT);
		TEX.LoadRawTexture(29,"grass2-stone-xb.dat",TEX_TOPRIGHT|TEX_BOTTOMRIGHT);
		TEX.LoadTexture(30,"stone.jpg",TEX_TOPLEFT|TEX_TOPRIGHT|TEX_BOTTOMLEFT|TEX_BOTTOMRIGHT);

		/*for (int x=0; x<50; x++)
		for (int y=0; y<50; y++)
		{
			int r=(int)(((float)rand()/(float)RAND_MAX)*10);
			if (r>6) NW.Tex[x][y]=r+3;
		};*/

		/*for (i=10;i<16;i++) NW.Tex[i][10]=2;
		for (i=10;i<16;i++) NW.Tex[10][i]=8;
		for (i=10;i<16;i++) NW.Tex[i][15]=6;
		for (i=10;i<16;i++) NW.Tex[15][i]=4;
		NW.Tex[10][10]=1;
		NW.Tex[15][10]=3;
		NW.Tex[15][15]=5;
		NW.Tex[10][15]=7;
		
		for (x=11;x<15;x++) for (int y=11;y<15;y++) NW.Tex[x][y]=9;*/

		NW.Chapes[61].xhandle=0;
		NW.Chapes[61].yhandle=0;
		
		for (i=100;i<132;i++)
		{
			NW.MidHandle(i);
		};

		int blocksize=1;
		
		//int T=0;
		//int Texture_Base=0;
		
		int box=0,boy=0,boxd=0;
		bool ComLink_Minimized=FALSE;
		int Active_Page=0;
		int Active_Construct=-1;
		int Active_RightButton=-1;
		bool Panel_Minimized=FALSE;
		
		int Build=0;
		int Building=0;
		
		bool SmallGrid=FALSE;

		NW.PreMain=false;
		
		int Hill[4][4]={ 1, 2, 2,1,
					 2, 4, 4,2,
					 2,4,4,2,
					 1, 2, 2,1};
						 
		int Mount[4][4]={ 2, 2, 2,2,
					 2,2,2,2,
					 2, 2, 2,2,
					 2, 2, 2,2};
						 
		int Crater[4][4]={ -1, -2,-2, -1,
					 -2,-4,-4,-2,
					 -2, -4, -4,-2,
					 -1, -2, -2,-1};

		int Key=0;

		bool CoMessage=FALSE;
		int frm=0;
		
		int Manip=0;
		int TexMan=1;
		int snowy=0;

		int mov=0;
		
		NW_Unit newunit;
		
		if (selection==2)
		{
			for (mov=0; mov<10; mov++)
			{
				newunit.type=1;
				newunit.health=30;
				newunit.x=10+mov*2;
				newunit.y=10+mov*2;
				newunit.relx=0;
				newunit.rely=0;
				newunit.w=1;
				newunit.h=1;
				newunit.r=mov*2;
				
				NET.AddUnit(&newunit);
				memcpy(&NW.Units[mov],&newunit,sizeof (NW_Unit));
				memcpy(&NW.DRUnits[mov],&newunit,sizeof (NW_Unit));

				NW.Units_Created++;
				
				//NW.Bmap[10+mov*2][10+mov*2]=1;
			};
		};
		
		//NW.Units[0].state=UNIT_STATE_ATTACKING;
		
		/*NW.Objects[0].type=1;
		NW.Objects[0].x=15;
		NW.Objects[0].y=6;
		NW.Bmap[15][6]=666;
		NW.Chapes[550].xhandle=NW.Chapes[550].w/2;
		NW.Chapes[550].yhandle=NW.Chapes[550].h-1;
		
		NW.LoadBuilding(0,"/boot/home/test.amxb");
		NW.Buildings[0].id=1;
		NW.Buildings[0].x=7;
		NW.Buildings[0].y=7;
		NW.Buildings[0].w=3;
		NW.Buildings[0].h=4;
		
		NW.Objects_Created=1;
		NW.Buildings_Created=1;
		NW.Units_Created=10;*/
		NW.Relanims_Created=0;

		int Pullout_One=0;
		int Pulling_One=0;
		int Pullout_Two=0;
		int Pulling_Two=0;
		int Pullout_Three=0;
		int Pulling_Three=0;
		
		int inslone=0,insltwo=0,inslthree=0;
		
		float degree=3.141592654/180;
		int sf=0;
		int u=0,um=0;

		int SCROLLF=0; // Scroll feedback time

		int fx=0;

		int SelectedOption=0;

		int scount=0; // Scroll reaction counter
		
		//NW.LoadChapes(999,999,"gfx/test.amxc");


		// -------------------------------------------------

			// Slideout Zones

			ZON.Set(0,NW_WIDTH-40,NW_WIDTH-1,0,99);
			ZON.Set(1,NW_WIDTH-40,NW_WIDTH-1,102,201);
			ZON.Set(2,NW_WIDTH-40,NW_WIDTH-1,204,305);
			
			ZON.Set(3,NW_WIDTH-390,NW_WIDTH-350,0,99);
			ZON.Set(4,NW_WIDTH-390,NW_WIDTH-350,102,201);
			ZON.Set(5,NW_WIDTH-390,NW_WIDTH-350,204,305);

			ZON.Set(6,NW_WIDTH-349,NW_WIDTH-1,0,99);
			ZON.Set(7,NW_WIDTH-349,NW_WIDTH-1,102,201);
			ZON.Set(8,NW_WIDTH-349,NW_WIDTH-1,204,305);

		// -------------------------------------------------

		/*entry_ref msxref;
		BEntry msxentry("/boot/home/code/Soeki/mus/condemned_area.aiff");
		msxentry.GetRef(&msxref);
		BFileGameSound CondemnedArea(&msxref,true);
		CondemnedArea.StartPlaying();*/

		NW.SayMode=false;
		NW.SayChars=0;

		while (NW.running)
		{
//			AUD.HandleAudio();

			NW.Command=0;

			if (modifiers())
			{
				NW.Command=1;
			};

			Key=NW.NWWindow->kd;
			
			if (Key)
			{
				NW.NWWindow->kd=0;
				//printf ("Key: %c\n",Key);
				if (!NW.SayMode)
				{
					switch (Key)
					{
						case '\n':
							NW.SayMode=true;
							NW.SayChars=0;
							NW.SayString[0]=0;
							break;
						case 'q':
							NW.running=false;
							be_app->PostMessage(B_QUIT_REQUESTED);
							break;
						case 'm':
							Manip++;
							if (Manip==3) Manip=0;
							if (Manip==0) NW.OutCon("MANIPULATOR: HILL");
							if (Manip==1) NW.OutCon("MANIPULATOR: MOUNTAIN");
							if (Manip==2) NW.OutCon("MANIPULATOR: CRATER");
							break;
						case 't':
							TexMan++;
							if (TexMan==3) TexMan=0;
							if (TexMan==0) NW.OutCon("TEXTURE: DESERT");
							if (TexMan==1) NW.OutCon("TEXTURE: DARK GRASS");
							if (TexMan==2) NW.OutCon("TEXTURE: STONE");
							break;
						case 'g':
							NW.GRID=!NW.GRID;
							//GFX.UpDate();
							break;
						case 's':
							TheFile=DAT.Open("map/MapShot.dat",DAT_WRITE);
							res=DAT.Write(TheFile,NW.Blox,100*100);
							res=DAT.Write(TheFile,NW.Tex,100*100);
							DAT.Close(TheFile);
							NW.OutCon("MAP SAVED TO MAP/MAPSHOT.DAT");
							break;
						case 'l':
							TheFile=DAT.Open("map/MapShot.dat",DAT_READ);
							res=DAT.Read(TheFile,NW.Blox,100*100);
							res=DAT.Read(TheFile,NW.Tex,100*100);
							DAT.Close(TheFile);
							NW.OutCon("MAP LOADED FROM MAP/MAPSHOT.DAT");
							for (y=0; y<100; y++)
								for (x=0; x<100; x++)
							{
								NW.MakeLight(x,y);
							};
							GFX.UpDate();
							break;
						case 'c':
							NW.Console_Running=!NW.Console_Running;
							break;
					};
				}
				else
				{
					//printf ("Keypress: %d\n",Key);
					switch (Key)
					{
						case '\n':
							NET.Say(NW.SayString);
							NW.SayMode=false;
							break;
						case 8:
							NW.SayString[--NW.SayChars]=0;
							break;
						default:
							NW.SayString[NW.SayChars++]=Key;
							NW.SayString[NW.SayChars]=0;
							break;
					};
				};
			};
			
			mx=NW.MouseX();
			my=NW.MouseY();
			
			/*if (mx>NW_WIDTH) mx=NW_WIDTH;
			if (my>NW_HEIGHT) my=NW_HEIGHT;
			
			if (mx==NW_WIDTH || my==NW_HEIGHT) set_mouse_position(mx,my);*/
			
			int scrollx=0;
			int scrolly=0;
			
			bool sf=false;
			
			#define smsp 16
			#define smspy 16
			
			if (mx>=NW_WIDTH-1 && NW.mapx<80 && NW.mapy<80)
			{
				sf=1; 
				if (scount>=SCROLLF) 
				{
					NW.smoothx+=smsp;
					GFX.DrawPartial(1,NW.smoothx);
				}
				else scount++;
			};
			if (mx==0 && NW.mapx>0 && NW.mapy>0) {sf=1; if (scount>=SCROLLF) {NW.smoothx-=smsp; GFX.DrawPartial(0,-NW.smoothx);} else scount++;};
			if (my>=NW_HEIGHT-1 && NW.mapy<80 && NW.mapx>0) {sf=1; if (scount>=SCROLLF) {NW.smoothy+=smspy; GFX.DrawPartial(3,NW.smoothy);} else scount++;};
			if (my==0 && NW.mapy>0 && NW.mapx<80) {sf=1; if (scount>=SCROLLF) {NW.smoothy-=smspy; GFX.DrawPartial(2,-NW.smoothy);} else scount++;};
			
			if (!sf)
			{
				if (mx==0 && NW.mapx>0) {sf=1; NW.smoothx-=smsp; NW.smoothy+=smspy;};
				if (mx==0 && NW.mapy>0) {sf=1; NW.smoothx-=smsp; NW.smoothy-=smspy;};
			};
			
			if (NW.smoothx>=64) {NW.mapx++; NW.mapy++; NW.smoothx=0; scrollx=1;};
			if (NW.smoothx<=-64) {NW.mapx--; NW.mapy--; NW.smoothx=0; scrollx=-1;};
			if (NW.smoothy>=32) {NW.mapy++; NW.mapx--; NW.smoothy=0; scrolly=1;};
			if (NW.smoothy<=-32) {NW.mapy--; NW.mapx++; NW.smoothy=0; scrolly=-1;};
			
			if (!sf) scount=0;
			
			if (scrollx || scrolly) GFX.UpDate();

			int scrlocky=(my>>4);
			int scrlockx=(mx>>6);
			
			if (NW.MouseButt() && NW.EditMode && !inslone && !insltwo && !inslthree)
			{
				int ox=NW.Cmap[scrlockx][scrlocky].x+NW.mapx;
				int oy=NW.Cmap[scrlockx][scrlocky].y+NW.mapy;
				int m=0;

				//NW.IsoScape(4+scrlockx-3,4+scrlockx+3,4+scrlocky-5,4+scrlocky+6,2);

				for (x=0;x<=blocksize+2;x++)
				{
					for (y=0;y<=blocksize+2;y++)
					{
						if (Manip==0) m=Hill[x][y];
						if (Manip==1) m=Mount[x][y];
						if (Manip==2) m=Crater[x][y];
						if (ox+x>0 && oy+y>0 && ox+x<99 && oy+y<99)
						{
							//m=Hill[x][y];
							NW.Blox[ox+x-2][oy+y-2]+=m;
						};
					};
				};

				for (x=-1;x<=blocksize-1;x++)
				{
					for (y=-1;y<=blocksize-1;y++)
					{
						NW.Tex[ox+x][oy+y]=TexMan*15;
					};
				};
				
				for (y=-2;y<=blocksize;y++)
				{
					for (x=-2;x<=blocksize;x++)
					{
						NW.Dyntex(ox+x,oy+y);
					};
				};
				
				for (x=-1;x<=blocksize+3;x++)
				{
					for (y=-1;y<=blocksize+3;y++)
					{
						NW.MakeLight(ox+x-2,oy+y-2);
						//Tmap[ox+x][oy+y]=Tex[ox+x][oy+y]/15;
						//if (Tmap[ox+x][oy+y]<1 || Tmap[ox+x][oy+y]>2) Bmap[ox+x][oy+y]=1;
						//NW.Bmap[ox+x][oy+y]=2000;
					};
				};

				NW.IsoScape(2+scrlockx-3,2+scrlockx+3,2+scrlocky-5,2+scrlocky+8,0);
				GFX.DrawBuildings(1);
			};
			G32.Use(NW.Chunky2);
			GFX.Map(scrollx,scrolly);
			
			if (NW.GRID)
			{
				for (y=0; y<480; y++) for (x=0; x <640; x++)
				{
					*(NW.Chunky+x+y*640)=(*(NW.zbuffer+x+64+(y+32)*768)*4)<<8;
				};
			};
			
			//*************************************
			//* Drawing here!
			//*************************************
			
			G32.CBlit(100,100,100);
			
			if (um==0) u+=5;
			if (um==1) u-=5;
			if (u>=40) um=1;
			if (u<=0) um=0;
			
			if (Pulling_One)
			{
				Pullout_One+=50*Pulling_One;
				if (Pullout_One >= 350 || Pullout_One==0) Pulling_One=0;
			};
			if (Pulling_Two)
			{
				Pullout_Two+=50*Pulling_Two;
				if (Pullout_Two >= 350 || Pullout_Two==0) Pulling_Two=0;
			};
			if (Pulling_Three)
			{
				Pullout_Three+=50*Pulling_Three;
				if (Pullout_Three >= 350 || Pullout_Three==0) Pulling_Three=0;
			};
			
			//ZWT.run(mx,my);
			
			//G32.Blit (668,0,0);
			
			inslone=0; insltwo=0; inslthree=0;

			ZON.Mouse(mx,my);
			
			ZON.Set(10,0,0,0,0);
			
			if (!boxd)
			{
				if (ZON.Hit(0)) inslone=1;
				if (ZON.Hit(1)) insltwo=1;
				if (ZON.Hit(2)) inslthree=1;
				if (ZON.Hit(3) && Pullout_One>=300) inslone=2;
				if (ZON.Hit(4) && Pullout_Two>=300) insltwo=2;
				if (ZON.Hit(5) && Pullout_Three>=300) inslthree=2;
				if (ZON.Hit(6) && Pullout_One>=300) inslone=3;
				if (ZON.Hit(7) && Pullout_Two>=300) insltwo=3;
				if (ZON.Hit(8) && Pullout_Three>=300) inslthree=3;
				
				if (inslone==1 && NW.MouseButt() && !Pullout_One) Pulling_One=1; 
				if (insltwo==1 && NW.MouseButt() && !Pullout_Two) Pulling_Two=1;
				if (inslthree==1 && NW.MouseButt() && !Pullout_Three) Pulling_Three=1;
				if (inslone==2 && NW.MouseButt()) Pulling_One=-1;
				if (insltwo==2 && NW.MouseButt()) Pulling_Two=-1;
				if (inslthree==2 && NW.MouseButt()) Pulling_Three=-1;
				if (inslthree==3 && NW.MouseButt()) {while (NW.MouseButt()) snooze(30000); NW.EditMode=!NW.EditMode;};
			};
			
			
			if (!inslone && !insltwo && !inslthree && NW.EditMode)
				for (int sgy=scrlocky-3; sgy<scrlocky+3; sgy++) for (int sgx=scrlockx-2; sgx<scrlockx+2; sgx++)
			{
				int xmd=NW.Cmap[sgx][sgy].x;
				int ymd=NW.Cmap[sgx][sgy].y;
				int sgs=sgy & 1;
				/*if (sgx==scrlockx && sgy==scrlocky)
				{
					sprintf(buffer,"%d %d %d %d",xmd,ymd,NW.mapx+xmd,NW.mapy+ymd);
					NW.OutCon(buffer);
				};*/
			
				if (NW.mapx+xmd>=0 && NW.mapy+ymd>=0 && NW.mapx+xmd<99 && NW.mapy+ymd<99)
				{
					int hsub1=NW.Blox[NW.mapx+xmd][NW.mapy+ymd];
					int hsub2=NW.Blox[NW.mapx+xmd+1][NW.mapy+ymd];
					int hsub3=NW.Blox[NW.mapx+xmd][NW.mapy+ymd+1];
					int hsub4=NW.Blox[NW.mapx+xmd+1][NW.mapy+ymd+1];
					
					int px1=sgx*64+sgs*32;
					int py1=sgy*16+16-hsub1;
					int py2=sgy*16-hsub2;
					int py3=sgy*16+16-hsub4;
					int py4=sgy*16+31-hsub3;
					
					uint32 col=0xffffff;
					if (py4<=py3) col=0x000000;
					
					G32.Line(px1-NW.smoothx,py1-NW.smoothy,px1-NW.smoothx+31,py2-NW.smoothy,col);
					G32.Line(px1-NW.smoothx+31,py2-NW.smoothy,px1-NW.smoothx+63,py3-NW.smoothy,col);
					G32.Line(px1-NW.smoothx+63,py3-NW.smoothy,px1-NW.smoothx+31,py4-NW.smoothy,col);
					G32.Line(px1-NW.smoothx+31,py4-NW.smoothy,px1-NW.smoothx,py1-NW.smoothy,col);
				};
			};
			
			/*sprintf (buffer,"%d %d",xmd,ymd);
			NW.Dynt(scrlockx*64+6+32*scrswitch,scrlocky*16-16,buffer);*/
			
			/*if (++mov>=32) mov=0;
			G32.Blit(100+mov,200,200);*/
			
			if (boxd==1)
			{
				G32.Line(box+1,boy+1,box+1,my+1,0);
				G32.Line(mx+1,boy+1,mx+1,my+1,0);
				G32.Line(box+1,boy+1,mx+1,boy+1,0);
				G32.Line(box+1,my+1,mx+1,my+1,0);
				
				G32.Line(box,boy,box,my,0xffffff);
				G32.Line(mx,boy,mx,my,0xffffff);
				G32.Line(box,boy,mx,boy,0xffffff);
				G32.Line(box,my,mx,my,0xffffff);
			};
			
			if (Build)
			{
				Building=0;
				for (x=0;x<blocksize+2;x++)
				{
					for (y=0;y<blocksize+2;y++)
					{
						if (NW.Bmap[NW.mapx+NW.gridlockx+x][NW.mapy+NW.gridlocky+y]==0) i=2;
						else {i=3; Building=1;};
//						NW.LandQuad2(gridlockx+NW.mapx+x,gridlocky+NW.mapy+y,i);
					};
				};
				if (NW.MouseButt() && !Building)
				{
					cnt=NW.Units_Created;
					NW.Units[cnt].type=1;
					NW.Units[cnt].x=NW.gridlockx+NW.mapx+1;
					NW.Units[cnt].y=NW.gridlocky+NW.mapy+1;
					NW.Units[cnt].relx=0;
					NW.Units[cnt].rely=0;
					NW.Units[cnt].w=3;
					NW.Units[cnt].h=3;
					NW.Units[cnt].r=(rand()/32767)*23;
					NW.Units_Created++;
					Build=0;
					for (x=0;x<blocksize+2;x++)
					{
						for (y=0;y<blocksize+2;y++)
						{
							NW.Bmap[NW.mapx+NW.gridlockx+x][NW.mapy+NW.gridlocky+y]=1;
						};
					};
				};
			};
			
			// ComLink
			
			/*if (!CoMessage)
			{
				if (!ComLink_Minimized) G32.Blit(1015+frm,clx+7,cly+9);
				frm++;
				if (frm>4) frm=0;
			}
			else
			{
				if (NW.Stream)
				{
					if (!ComLink_Minimized) G32.Blit(1020,clx+7,cly+9);
					NW.DoStream(1020);
				}
				else
				{
					CoMessage=0;
				};
			};*/
			
			// Draw Slides
			
			G32.Blit (500,NW_WIDTH-40-Pullout_One,0);
			G32.Blit (501,NW_WIDTH-40-Pullout_Two,102);
			G32.Blit (502,NW_WIDTH-40-Pullout_Three,204);
			
			//G32.Blit (180,0,NW_HEIGHT-1);
			
			for (int y=0; y<100; y++)
			{
				for (int x=0; x<100; x++)
				{
					int display_x=2+x+y;
					int display_y=NW_HEIGHT-50+((y-x)>>1);
					
					uint32 col=NW.Blox[x][y];
					
					*(NW.Chunky+display_x+display_y*NW_WIDTH)=(col<<16)|(col<<8)|(col);
				};
			};
			
			int wd=(640)>>5;
			int ht=(480)>>5;
			
			int display_x1=2+NW.mapx+NW.mapy;
			int display_y1=NW_HEIGHT-(50+ht/2)+((NW.mapy-NW.mapx)>>1);
			
			G32.Line(display_x1,display_y1,display_x1+wd,display_y1,0xffffff);
			G32.Line(display_x1,display_y1,display_x1,display_y1+ht,0xffffff);
			G32.Line(display_x1,display_y1+ht,display_x1+wd,display_y1+ht,0xffffff);
			G32.Line(display_x1+wd,display_y1,display_x1+wd,display_y1+ht,0xffffff);
			
			G32.Blit (510+NW.EditMode,NW_WIDTH+17-Pullout_Three,218);
			
			//*************************************

			/*if (mx>=clx && mx<=clx+57 && my>=cly && my<=cly+59) incl=1;
			else incl=0;
			
			if (mx>=cpx && mx<=cpx+127 && my>=cpy && my<=cpy+64) incp=1;
			else incp=0;*/

			if (GFX.Activated)
			{
				NW.Units[GFX.Activated-1].active=true;
				//NW.NewStream(1020,"gfx/CombatLinkk.chp");
				//CoMessage=true;
			};

			// Command a unit to move:
			
			if (modifiers()) boxd=0;

			if (!GFX.Activated && !NW.EditMode && !NW.BuildMode && !NW.Dragging  && !inslone && !insltwo && !inslthree)
			{
				if (!NW.MouseButt() && boxd==-1)
				{
					for (i=0;i<=NW.Units_Created;i++)
					{
						if (NW.Units[i].active)
						{
							NW.Units[i].dx=NW.Cmap[scrlockx][scrlocky].x+NW.mapx;
							NW.Units[i].dy=NW.Cmap[scrlockx][scrlocky].y+NW.mapy;
							//PRC.StepTable(i);
							NW.Units[i].state=UNIT_STATE_MOVING;
							NET.UpdateUnit(i,&NW.Units[i],1);
							memcpy(&NW.DRUnits[i],&NW.Units[i],sizeof (NW_Unit));
							//memcpy(&NW.DRUnits[i],&NW.Units[i],sizeof(NW_Unit));
							//CoMessage=true;
							//NW.NewStream(1020,"gfx/CombatLinkk.chp");
							frm=0;
						};
					};
					boxd=0;
				};
			};
			
			// Manage Multiselect-Box:
			
			if (NW.MouseButt() && !NW.EditMode && !boxd  && !inslone && !insltwo && !inslthree)
			{
				boxd=-1;
				box=mx; 
				boy=my;
			};
			if (NW.MouseButt() && boxd==-1)
			{
				if ((mx-box<-4 || mx-box>4) && (my-boy<-4 || my-boy>4)) {boxd=1;}
			};
			
			if (!NW.MouseButt() && boxd==1)
			{
				cnt=0;
				for (i=0;i<=NW.Units_Created;i++)
				{
					int tx=NW.Units[i].x;
					int ty=NW.Units[i].y;
					if (tx>=NW.mapx-2 && ty>=NW.mapy-2 && tx<=NW.mapx+NW_WIDTH/64+2 && ty<=NW.mapy+NW_HEIGHT/16+2)
					{
						if (box<=NW.DRUnits[i].dispx && mx>=NW.DRUnits[i].dispx && boy<=NW.DRUnits[i].dispy && my>=NW.DRUnits[i].dispy)
						{
							NW.Units[i].active=1;
							//NW.Units[i].activated_frame=8;
							NW.DRUnits[i].active=1;
							NW.DRUnits[i].activated_frame=8;
							GFX.Activated=true;
						}
						else
						{
							NW.Units[i].active=0;
							NW.DRUnits[i].active=0;
						};
					}
					else
					{
						NW.Units[i].active=0;
						NW.DRUnits[i].active=0;
					};
				};
				boxd=0;
			};

			// Global dragging 'bit':

			if (boxd==1) {NW.Dragging=true;} else {NW.Dragging=false;};

			// And the rest:
			
			PRC.Proc();
			NW.Show();
		};
		
		free (G32.distort);
		
		printf ("\n");
		printf ("-[First Half]-----------------------------------\n");
		printf ("*Soeki The Plague* Kernel halted.\n");
	};
	
	int main(int argc,char** argv)
	{
		NW.termination=0;
		printf ("Module Setup success.\n");
		be_app=new SoekiApp();
		
		// Finally, making the thing path relative
	
		app_info info;
		BPath* apppath;
		
		if (be_app->GetAppInfo(&info)!=B_OK)
		{
			printf ("This may sound crazy, but this application doesn't exist.\n");
			exit (666);
		};
		
		entry_ref ref=info.ref;
		BEntry* appentry=new BEntry(&ref);
		apppath=new BPath(appentry);
		
		const char* pathbuf;
		pathbuf=apppath->Path();
		
		int length=strlen(pathbuf)-(2*strlen(apppath->Leaf())+1);
		
		printf ("%d\n",length);
		
		NW.SOEKI_PATH=malloc(length+1);
		
		strncpy (NW.SOEKI_PATH,pathbuf,length);
		NW.SOEKI_PATH[length]=0;
		
		printf ("Application Path: %s\n",NW.SOEKI_PATH);
		
		be_app->Run();
		printf ("main() exit\n");
		free (NW.SOEKI_PATH);
		while (NW.NWWindow->didthejob)
		{
			snooze(30000);
		};
		return 0;
	};