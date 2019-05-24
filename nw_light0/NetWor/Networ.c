
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
	unsigned char Light[101][101];
	struct normals {
		double nx,ny,nz,nl;
	};
	struct normals UpperNrm[101][101];
	struct normals LowerNrm[101][101];

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



		double lx=-170;
		double ly=-150;
		double lz=180;
		double llen=sqrt(lx*lx+ly*ly+lz*lz);
		lx/=llen; //normalisieren des Lichts
		ly/=llen;
		lz/=llen;

		double p1x=0,p1y=0,p2x=32,p2y=0,p3x=32,p3y=32,p4x=0,p4y=32;

//*************************************
// Hier werden erstmal die Normalen der Dreiecke berechnet
//*************************************

for(x=0;x<100;x++)
  for(y=0;y<100;y++)
    {
      double p1z=Blox[x][y]; //z1  1 2
      double p2z=Blox[x+1][y]; //z2  4 3
      double p3z=Blox[x+1][y+1]; //z3
      double p4z=Blox[x][y+1]; //z4
//calculate upper normal
      double kpx=(p1y-p2y)*(p1z-p4z)-(p1z-p2z)*(p1y-p4y);
      double kpy=(p1z-p2z)*(p1x-p4x)-(p1x-p2x)*(p1z-p4z);
      double kpz=(p1x-p2x)*(p1y-p4y)-(p1y-p2y)*(p1x-p4x);
      double len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
      if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0}
      UpperNrm[x][y].nx=kpx;
      UpperNrm[x][y].ny=kpy;
      UpperNrm[x][y].nz=kpz;

      //double lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;

//calculate lower normal
      kpx=(p4y-p2y)*(p4z-p3z)-(p4z-p2z)*(p4y-p3y);
      kpy=(p4z-p2z)*(p4x-p3x)-(p4x-p2x)*(p4z-p3z);
      kpz=(p4x-p2x)*(p4y-p3y)-(p4y-p2y)*(p4x-p3x);
      len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
      if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0}
      //lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;
      LowerNrm[x][y].nx=kpx;
      LowerNrm[x][y].ny=kpy;
      LowerNrm[x][y].nz=kpz;

    }

//*************************************
// Teil 2: Berechnen der Durchschnittsnormalen und des Lichts
//*************************************
for(x=1;x<99;x++)
  for(y=1;y<99;y++)
    {
      double kpx=(UpperNrm[x][y].nx+UpperNrm[x][y-1].nx+UpperNrm[x-1][y].nx+
                LowerNrm[x-1][y-1].nx+LowerNrm[x-1][y].nx+LowerNrm[x][y-1].nx)/6.0;
      double kpy=(UpperNrm[x][y].ny+UpperNrm[x][y-1].ny+UpperNrm[x-1][y].ny+
                LowerNrm[x-1][y-1].ny+LowerNrm[x-1][y].ny+LowerNrm[x][y-1].ny)/6.0;
      double kpz=(UpperNrm[x][y].nz+UpperNrm[x][y-1].nz+UpperNrm[x-1][y].nz+
                LowerNrm[x-1][y-1].nz+LowerNrm[x-1][y].nz+LowerNrm[x][y-1].nz)/6.0;
      double lf=(lx*kpx+ly*kpy+lz*kpz)/* /(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*/*20+40;
      Light[x][y]=(unsigned char)lf;
    }



		
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
