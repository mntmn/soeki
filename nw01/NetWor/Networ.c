
/*	What will once be Networ... boy this editor is much better than crappy SuperTed
	©Lukas Hartmann / Atomatrix, 1998/99                                                  */

	#include <clib/exec_protos.h>
	#include <clib/intuition_protos.h>
	#include <clib/dos_protos.h>
	#include <clib/graphics_protos.h>
	#include <math.h>
	#include <exec/memory.h>
	#include <workbench/startup.h>
	#include <stdlib.h>
	#include <stdio.h>
	
	#include "ChunkyLib.h"
	chape Chapes[3001];
	unsigned char Blox[101][101];
	#include "bbgoutextri.h"
	struct Tridat tri0;

	#include "NW_Master.h"
	
	struct Store NW;
	
	void main()
	{
		NW.SetUp();
		NW.UseBitmap(0);
		NW.LoadPalette("Text:HiSOFT_C/projects/NetWor/Main.pal");
		
		int i=0;
		int x=0;
		int y=0;
				
		NW.LoadChape (1,"Text:HiSOFT_C/projects/NetWor/Test.chape",0x5d,0x6b);

		c2p030init (320,256);
		ChunkInit(Chapes,0);
		UseChunk(NW.Chunky);
		
		NW.NWToFront();
		
		x=10;
		y=50;
		int ub=0;
		int m=0;
		int mx=0;
		int my=0;

		BPTR mFile=Open("TEXT:Hisoft_C/projects/NetWor/snow.chk",MODE_OLDFILE);

		APTR tex=AllocMem(65536,MEMF_FAST | MEMF_CLEAR);
		int result_=Read(mFile,tex,65536);
		Close (mFile);

		mFile=Open("TEXT:Hisoft_C/projects/NetWor/clutb.dat",MODE_OLDFILE);

		APTR clut=AllocMem(16384,MEMF_FAST | MEMF_CLEAR);
		result_=Read(mFile,clut,16384);
		Close (mFile);

		
		while (!MouseButt())
		{
			ChunKlear ();
			tri0.TMPtr=tex;
			tri0.CBPtr=NW.Chunky;
			tri0.CCTab=clut;

			mx=NW.MouseX();
			my=NW.MouseY();
			
			if (mx>315 && NW.mapx<80) NW.mapx++;
			if (mx<5 && NW.mapx>0) NW.mapx--;
			if (my>250 && NW.mapy<80) NW.mapy++;
			if (my<5 && NW.mapy>0) NW.mapy--;
			
			NW.LandScape ();
			ChunkyBlit (1,NW.MouseX(),NW.MouseY());
			c2p030(NW.Chunky,NW.BMap[1-ub]);
			ub=1-ub;
			NW.UseBitmap(ub);
		};
		
		NW.CleanUp();
       FreeMem(tex,65536);
       FreeMem(clut,16384);
	}
