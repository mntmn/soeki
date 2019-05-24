/*
	Chape Editor for Networ - ©1999 Lukas Hartmann/Atomatrix Entertainment
*/

	#include <clib/exec_protos.h>
	#include <clib/intuition_protos.h>
	#include <clib/dos_protos.h>
	#include <clib/graphics_protos.h>
	#include <clib/iffparse_protos.h>
	#include <clib/lowlevel_protos.h>
	#include <clib/asl_protos.h>
	#include <math.h>
	#include <exec/memory.h>
	#include <workbench/startup.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	
	#include "ChunkyLib.h"
	chape Chapes[3001];
	unsigned char CTable[256*3];
	unsigned char* CLUT;
	#include "CE_Master.h"
	
	struct Store CE;
	
	Library* LowLevelBase;
	Library* AslBase;
	
	void main()
	{
		IFFParseBase=OpenLibrary("iffparse.library",0L);
		LowLevelBase=OpenLibrary("lowlevel.library",0L);
		AslBase=OpenLibrary("asl.library",0L);
		
		CE.SetUp();
		CE.UseBitmap(0);
		CE.LoadPalette("Text:HiSOFT_C/projects/NetWor/Main.pal");

		CLUT=(unsigned char*)AllocMem(2560,MEMF_FAST|MEMF_CLEAR);

		CE.LoadChape (1,"Text:HiSOFT_C/projects/NetWor/CH_Gfx/ChTools.dat",59,25);
	
		BPTR cluthere=Lock("Text:HiSOFT_C/projects/NetWor/CH_Gfx/Invert.fxt",MODE_OLDFILE);
		
		BPTR TheFile=0;
		int res=0;

		/*TheFile=Open("Text:HiSOFT_C/projects/NetWor/CH_Gfx/CTable.dat",MODE_NEWFILE);
		res=Write(TheFile,CTable,256*3);
		Close(TheFile);*/
		
		if (!cluthere)
		{
			unsigned char TableRed[256];
			unsigned char TableGreen[256];
			unsigned char TableFinal[256];
			long RedNew,GreenNew,BlueNew,RedThis,GreenThis,BlueThis;
			signed int i,c,csub,rcount,gcount,bcount;
			for (i=0;i<10;i++)
			{
				for (c=0;c<256;c++)
				{
					/*RedNew=CTable[c*3]+30*(i+1);
					GreenNew=CTable[c*3+1]-10*(i+1);
					BlueNew=CTable[c*3+2]-10*(i+1);*/
					
					RedNew=255-CTable[c*3];
					GreenNew=255-CTable[c*3+1];
					BlueNew=255-CTable[c*3+2];
					
					if (RedNew>255) RedNew=255;
					if (GreenNew>255) GreenNew=255;
					if (BlueNew>255) BlueNew=255;
					
					if (RedNew<0) RedNew=0;
					if (GreenNew<0) GreenNew=0;
					if (BlueNew<0) BlueNew=0;
					
					int Tolerance=1;
					
					clutloop:
					
					// Durchgang 1: Alle Werte, die für Rot in Frage kommen -> TableRed[]
					rcount=0;
					for (csub=0;csub<256;csub++)
					{
						RedThis=(RedNew-CTable[csub*3]);
						RedThis*=RedThis;
						if (RedThis<Tolerance*Tolerance)
						{
							TableRed[rcount]=csub;
							rcount++;
						};
					};
					gcount=0;
					for (csub=0;csub<rcount;csub++)
					{
						GreenThis=(GreenNew-CTable[TableRed[csub]*3+1]);
						GreenThis*=GreenThis;
						if (GreenThis<Tolerance*Tolerance)
						{
							TableGreen[gcount]=TableRed[csub];
							gcount++;
						};
					};
					bcount=0;
					for (csub=0;csub<gcount;csub++)
					{
						BlueThis=(BlueNew-CTable[TableGreen[csub]*3+2]);
						BlueThis*=BlueThis;
						if (BlueThis<Tolerance*Tolerance)
						{
							TableFinal[bcount]=TableGreen[csub];
							bcount++;
						};
					};
					if (bcount==0)
					{
						Tolerance+=2;
						goto clutloop;
					};
					CLUT[i*256+c]=TableFinal[0];
				};
				printf("\nCALC: %d of 10",i);
			};
			
			TheFile=Open("Text:HiSOFT_C/projects/NetWor/CH_Gfx/Invert.fxt",MODE_NEWFILE);
			res=Write(TheFile,CLUT,2560);
			Close(TheFile);
		};
		else
		{
			UnLock(cluthere);
			CE.LoadCLUT ("Text:HiSOFT_C/projects/NetWor/CH_Gfx/Invert.fxt",CLUT);
		};

		c2p030init (320,256);
		ChunkInit(Chapes,CLUT);
		UseChunk(CE.Chunky);
		
		CE.NWToFront();
		
		CE.LoadBitmap("Text:HiSOFT_C/projects/NetWor/CH_Gfx/AMX.iff",0);
		CE.Bitmap2Chunky(0,CE.Chunky2);
		
		int x=0;
		int y=0;
		int ub=0;
		int m=0;
		int mx=0;
		int my=0;
		
		unsigned char* CHPoke=0;
		
		/*for (y=0;y<10;y++)
		{
			for (x=0;x<256;x++)
			{
				CHPoke=(unsigned char*)CE.Chunky2+6400+y*320+x;
				*CHPoke=CLUT[y*256+x];
			};
		};*/
		
		BOOL quit=FALSE;
		ULONG inkey=0;
		int px=10,py=10,npx=0,npy=0;
		int kp=0,kp2=0;
		int grabbed=0;
		int acts=1,lgs=0;
		
		APTR freq=0;
		char fname[512];
		
		char wbscreen[]="Workbench";
		char chpattern[]="#?.chp";
		char chsavetitle[]="Save Chape as...";
		char chsavepbut[]="Save";
		char chloadtitle[]="Load ILBM...";
		char chloadpbut[]="Load";
		
		int fs=0,i=0;
		
		while (!quit)
		{
			inkey=GetKey();
			if ((inkey & 0x0000ffff)==0x45) quit=TRUE;
			ChunKopy(CE.Chunky2,CE.Chunky);
			mx=CE.MouseX();
			my=CE.MouseY();
			
			// The Toolbar
			
			ChunkyBlit(1,px,py);
			if (grabbed)
			{
				ChunkyBlit(acts,px+1,py+26);
				CE.ChunkyLine(px,py+25,px+Chapes[acts].w+2,py+25,10,FALSE);
				CE.ChunkyLine(px,py+26,px,py+26+Chapes[acts].h,10,FALSE);
				CE.ChunkyLine(px+Chapes[acts].w+2,py+26,px+Chapes[acts].w+2,py+26+Chapes[acts].h+1,10,FALSE);
				CE.ChunkyLine(px,py+26+Chapes[acts].h+1,px+Chapes[acts].w+2,py+26+Chapes[acts].h+1,10,FALSE);
			};
			
			while (!CE.NWActive()) {};
			
			// Read and interpretate mouse input
			
			if (!(mx>=px && mx<=px+59 && my>=py && my<=py+25))
			{
				if (!kp)
				{
					if (MouseButt() && !kp2) {kp2=1; npx=mx; npy=my;};
					if (!MouseButt() && kp2)
					{
						kp2=0;
						acts++;
						CE.GrabChape(acts,CE.Chunky2,npx,npy,mx,my);
						for (x=npx;x<mx+1;x++)
						{
							for (y=npy;y<my+1;y++)
							{
								*((UBYTE*)CE.Chunky2+y*320+x)=0;
							};
						};
						grabbed=1;
						lgs=acts;
					};
					if (!kp2)
					{
						CE.ChunkyLine(0,my,320,my,1,TRUE);
						CE.ChunkyLine(mx,0,mx,256,1,TRUE);
					};
					else
					{
						CE.ChunkyLine(npx,npy,mx,npy,1,TRUE);
						CE.ChunkyLine(npx,npy,npx,my,1,TRUE);
						CE.ChunkyLine(mx,npy,mx,my,1,TRUE);
						CE.ChunkyLine(npx,my,mx,my,1,TRUE);
					};
				};
			};
			else 
			{
				if (MouseButt() && !kp && my<py+6) {kp=1; npx=mx-px; npy=my-py;};
				if (MouseButt() && !kp && my>py+6)
				{
					printf ("Mouse: %d, %d",mx,my);
					if (mx>=px+2 && mx<=px+17)
					{
						freq=AllocAslRequestTags(ASL_FileRequest,
							ASLFR_PubScreenName,wbscreen,
							ASLFR_TitleText,chloadtitle,
							ASLFR_DoPatterns,TRUE,
							ASLFR_InitialPattern,chpattern,
							ASLFR_PositiveText,chloadpbut,
							ASLFR_InitialLeftEdge,10,
							ASLFR_InitialTopEdge,10,
							ASLFR_InitialWidth,200,
							ASLFR_InitialHeight,400);
						if (AslRequest(freq,NULL))
						{
							strncpy(fname,((FileRequester*)freq)->fr_Drawer,300);
							strcat(fname,"/");
							strncat(fname,((FileRequester*)freq)->fr_File,200);
							CE.LoadBitmap(fname,0);
							CE.Bitmap2Chunky(0,CE.Chunky2);
							FreeAslRequest(freq);
						};
						CE.NWToFront();
					};
					if (mx>=px+18 && mx<=px+33)
					{
						freq=AllocAslRequestTags(ASL_FileRequest,
							ASLFR_PubScreenName,wbscreen,
							ASLFR_TitleText,chsavetitle,
							ASLFR_DoSaveMode,TRUE,
							ASLFR_DoPatterns,TRUE,
							ASLFR_InitialPattern,chpattern,
							ASLFR_PositiveText,chsavepbut,
							ASLFR_InitialLeftEdge,10,
							ASLFR_InitialTopEdge,10,
							ASLFR_InitialWidth,200,
							ASLFR_InitialHeight,400);
						if (AslRequest(freq,NULL))
						{
							strncpy(fname,((FileRequester*)freq)->fr_Drawer,300);
							strcat(fname,"/");
							strncat(fname,((FileRequester*)freq)->fr_File,200);
							CE.SaveChape(acts,fname);
							FreeAslRequest(freq);
						};
						CE.NWToFront();
					};
					if (mx>=px+34 && mx<=px+49)
					{
						if (grabbed)
						{
							fs=0;
							CE.FreeChape(acts);
							for (i=0;Chapes[acts+i+1].chunk;i++)
							{
								fs=1;
								Chapes[acts+i]=Chapes[acts+i+1];
								Chapes[acts+i+1].chunk=0;
								Chapes[acts+i+1].w=0;
								Chapes[acts+i+1].h=0;
								Chapes[acts+i+1].xhandle=0;
								Chapes[acts+i+1].yhandle=0;
							};
							lgs--;
							if (acts<lgs && lgs>=2) acts=lgs;
							if (acts==2 && !fs) grabbed=0;
						};
					};
					if (mx>=px+50 && mx<=px+56 && my<=py+14 && acts<lgs)
					{
						acts++;
					};
					if (mx>=px+50 && mx<=px+56 && my>=py+15 && my<=py+21 && acts>2)
					{
						acts--;
					};
				};
			};
			if (kp)
			{
				px=mx-npx;
				py=my-npy;
			};
			if (!MouseButt()) kp=0;
			
			// Double Buffering
			
			c2p030(CE.Chunky,CE.BMap[1-ub]);
			ub=1-ub;
			CE.UseBitmap(ub);
		};

		FreeMem(CLUT,2560);
		CE.CleanUp();
	}
