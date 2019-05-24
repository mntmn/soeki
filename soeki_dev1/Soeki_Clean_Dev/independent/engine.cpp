/*
	Networ GFX Engine �1999 Lukas Hartmann / Atomatrix Entertainment
*/

#include "engine.h"

Store* eNW;
gfx_32* eG32;

float getplaneheight(vector p1,vector p2,vector p3,float x, float y)
{
	vector vtx1,vtx2;
   // Plane (aus 3 Punkten des Vierecks)
   //  p1 *
   //                   * p2
   //       p3*  
   //Vektor von p1 zu p2:
    vtx1.x=p2.x-p1.x;
    vtx1.y=p2.y-p1.y;
    vtx1.z=p2.z-p1.z;
   //Vektor von p1 zu p3:
    vtx2.x=p3.x-p1.x;
    vtx2.y=p3.y-p1.y;
    vtx2.z=p3.z-p1.z;
//Kreuzprodukt berechnet die Normale, also A, B und C
    float A = vtx1.y * vtx2.z - vtx1.z * vtx2.y;
    float B = vtx1.z * vtx2.x - vtx1.x * vtx2.z;
    float C = vtx1.x * vtx2.y - vtx1.y * vtx2.x;
    //D ist Abstand der Fläche zum Koordinatenursprung. Wird berechnet aus A, B, C und irgendeinem der Punkte der Fläche
    float D = (p1.x * A + p1.y * B + p1.z * C);
    // A*x + B*y + C*z = D;
// Für Höhe z nur noch Umformung:
    float z = (D - A*x - B*y) / C;
    return z;
    // für x und y die Koordinaten einsetzen
    // Tip: A, B, C und D können vorberechnet werden
};

void Store_GFX::Connect(Store* n, gfx_32* g)
{
	eNW=n;
	NW_WIDTH=eNW->NW_WIDTH;
	NW_HEIGHT=eNW->NW_HEIGHT;
	Units=eNW->Units;
	Buildings=eNW->Buildings;
	Objects=eNW->Objects;
	Relanims=eNW->Relanims;
	
	eG32=g;
};

Store_GFX::Store_GFX()
{
	this->drawn=false;
};

void Store_GFX::DrawBuildings(int mode)
{
	int tx,ty,tw,th,i,chp;
	zbuffer=eNW->zbuffer;
	
	eG32->NW_WIDTH=640+256; // Very dirty hack
	eG32->NW_HEIGHT=480+128; // Dirty hack #2
	
	for (i=0; i<eNW->Buildings_Created; i++)
	{
		if (Buildings[i].id)
		{
			tx=Buildings[i].x;
			ty=Buildings[i].y;
			tw=Buildings[i].w;
			th=Buildings[i].h;
			int rtx=0; int rty=0;
			if (tx>=eNW->mapx-4 && ty>=eNW->mapy-4 && tx<=eNW->mapx+NW_WIDTH/64+2 && ty<=eNW->mapy+NW_HEIGHT/16+2)
			{
				int ttx=tx-eNW->mapx;
				int tty=ty-eNW->mapy;
				for (int ly=0; ly<30; ly++)
					for (int lx=0; lx<10; lx++)
						if (eNW->Cmap[lx][ly].x==ttx && eNW->Cmap[lx][ly].y==tty)
				{
					rtx=lx*64+(ly&1)*32;
					rty=ly*16;
				};
			
				for (int j=0; j<4; j++)
				{
					if (Buildings[i].statics[j])
					{
						chp=Buildings[i].statics[j]-1;
						
						if (rtx || rty)
						{
							int16 z=rty/16;
							/*if (Buildings[i].sshadow[j])
							{
								//eG32->Use(eNW->Chunky);
								//if (mode==2) eG32->ZSBlit(chp,rtx+32,rty+16,zbuffer,z+5);
							}
							else
							{*/
								eG32->Use(eNW->Chunky2);
								if (mode==1) eG32->ZBlit(chp,rtx+32,rty+16,zbuffer,z+5,0,0);
							//};
						};
					};
				};
			};
		};
	};
	eG32->Use(eNW->Chunky);
	eG32->NW_WIDTH=640; // Very dirty hack
	eG32->NW_HEIGHT=480; // Dirty hack #2
};

void Store_GFX::DrawPartial(int side,int frame)
{
	if (frame<0) return;

	int COLUMN_WIDTH=(640+256)/64;
	int COLUMN_HEIGHT=(480+128)/16;
	int SCROLL_FRAMES=64/16;
	int YSCROLL_FRAMES=32/16;

	int wd=(640+256)>>6;
	int ht=(480+128)>>4;
	
	int sr=-1;
	int er=ht+7;

	int sc=-2;
	int ec=wd;

	int ymode=0;

	if (side==0)
	{
		frame/=16;
		ec=sc+3;
		sr=-6+(COLUMN_HEIGHT/SCROLL_FRAMES)*frame;
		er=-5+(COLUMN_HEIGHT/SCROLL_FRAMES)*(frame+1);
		char buf[40];
		sprintf (buf,"LEFT: X %d %d Y %d %d",sc,ec,sr,er);
		eNW->OutCon(buf);
	};
	
	if (side==1)
	{
		frame/=16;
		sc=ec-2;
		sr=-6+(COLUMN_HEIGHT/SCROLL_FRAMES)*frame;
		er=-5+(COLUMN_HEIGHT/SCROLL_FRAMES)*(frame+1);
	};
	
	if (side==2)
	{
		frame/=16;
		ymode=1;
		er=sr+5;
		sc=-6+(COLUMN_WIDTH/YSCROLL_FRAMES)*frame;
		ec=-5+(COLUMN_WIDTH/YSCROLL_FRAMES)*(frame+1);
	};
	
	if (side==3)
	{
		frame/=16;
		sr=er-12;
		sc=-6+(COLUMN_WIDTH/YSCROLL_FRAMES)*frame;
		ec=-5+(COLUMN_WIDTH/YSCROLL_FRAMES)*(frame+1);
	};
	
	eNW->IsoScape(sc,ec,sr,er,ymode);
};

void Store_GFX::Map(int scrollx,int scrolly)
{
	zbuffer=eNW->zbuffer;
	//printf ("ZBuffer: %x\n",zbuffer);

	int i=0;
	int tx,ty,chp,tw,th,cnt;
	int mx=eNW->MouseX();
	int my=eNW->MouseY();
	int after,before;
	if (drawn==false)
	{
		int wd=NW_WIDTH>>6;
		int ht=NW_HEIGHT>>4;
	
		int sr=-4;
		int er=ht+7;

		int sc=-4;
		int ec=wd+4;

		int ymode=0;

		eG32->Use(eNW->Chunky2);

		/*if (scrollx == -1 && scrolly == -1)
		{
			eG32->ScrollDiag(eNW->Chunky2,eNW->Chunky2+64+NW_WIDTH*32,zbuffer,zbuffer+64+NW_WIDTH*32);
			ec=sc+3;
			eNW->IsoScape(sc,ec,sr,er,0);
			ec=wd+1;
			er=sr+6;
			ymode=1;
			goto Scroll_End;
		};
		
		if (scrollx == 1 && scrolly == -1)
		{
			eG32->ScrollDiag(eNW->Chunky2+64,eNW->Chunky2+NW_WIDTH*32,zbuffer+64,zbuffer+NW_WIDTH*32);
			sc=ec-3;
			eNW->IsoScape(sc,ec,sr,er,0);
			sc=-1;
			er=sr+6;
			ymode=1;
			goto Scroll_End;
		};
		
		if (scrollx == -1 && scrolly == 1)
		{
			eG32->ScrollDiag(eNW->Chunky2+NW_WIDTH*32,eNW->Chunky2+64,zbuffer+NW_WIDTH*32,zbuffer+64);
			ec=sc+3;
			eNW->IsoScape(sc,ec,sr,er,0);
			ec=wd+1;
			sr=ht-3;
			goto Scroll_End;
		};
		
		if (scrollx == 1 && scrolly == 1)
		{
			eG32->ScrollDiag(eNW->Chunky2+64+NW_WIDTH*32,eNW->Chunky2,zbuffer+64+NW_WIDTH*32,zbuffer);
			sc=ec-3;
			eNW->IsoScape(sc,ec,sr,er,0);
			sc=-1;
			sr=ht-3;
			goto Scroll_End;
		};*/

		#define BUFFER_WIDTH (640+256)

		if (scrolly == -1)
		{
			eG32->ScrollVert(eNW->Chunky2,eNW->Chunky2+BUFFER_WIDTH*32,zbuffer,zbuffer+BUFFER_WIDTH*32);
			//ymode=1;
		};
		if (scrolly == 1)
		{
			eG32->ScrollVert(eNW->Chunky2+BUFFER_WIDTH*32,eNW->Chunky2,zbuffer+BUFFER_WIDTH*32,zbuffer);
			//sr=er-7;
		};
		if (scrollx == -1)
		{
			eG32->ScrollHoriz(eNW->Chunky2,eNW->Chunky2+64,zbuffer,zbuffer+64);
		};
		if (scrollx == 1)
		{
			eG32->ScrollHoriz(eNW->Chunky2+64,eNW->Chunky2,zbuffer+64,zbuffer);
		};
		
Scroll_End:		before = real_time_clock_usecs();
		if (!scrollx && !scrolly) eNW->IsoScape(sc,ec,sr,er,ymode);
		after = real_time_clock_usecs();
		//printf ("IsoScape(): %d usecs.\n",after-before);

Scroll_End2:		cnt=0;

		DrawBuildings(1);
		drawn=true;
	};

	//eNW->Chunky=eNW->NWWindow->kick_me+NW_WIDTH*NW_HEIGHT;

	eG32->SmoothCopy(eNW->Chunky2,eNW->smoothx+128,eNW->smoothy+64,eNW->Chunky);
	eG32->Use(eNW->Chunky);
	
	Activated=false;
	
	for (i=0;i<eNW->Units_Created;i++)
	{
		if (Units[i].type)
		{
			tx=Units[i].x;
			ty=Units[i].y;
			tw=Units[i].w;
			th=Units[i].h;
			int rtx=0; int rty=0;
			
			// To Do: Replace the following line with a better method to check visibility of a unit...
			
			if (tx>=eNW->mapx-8 && ty>=eNW->mapy-8 && tx<=eNW->mapx+NW_WIDTH/64+8 && ty<=eNW->mapy+NW_HEIGHT/16+8)
			{
				if (Units[i].state==UNIT_STATE_ATTACKING)
				{
					if (Units[i].r==Units[i].dr)
					{
						chp=124+(Units[i].r/3)*4+Units[i].state_data;
					}
					else
					{
						chp=CHAPESBASE_UNITS+Units[i].type+Units[i].r;
					};
					//printf ("chp: %d\n",chp);
				}
				else
				{
					chp=CHAPESBASE_UNITS+Units[i].type+Units[i].r;
				};

				int ttx=tx-eNW->mapx;
				int tty=ty-eNW->mapy;
				for (int ly=0; ly<30; ly++)
					for (int lx=0; lx<10; lx++)
						if (eNW->Cmap[lx][ly].x==ttx && eNW->Cmap[lx][ly].y==tty)
				{
					rtx=lx*64+(ly&1)*32;
					rty=ly*16;
				};
				
				if (rtx || rty)
				{
					eG32->Blix(61,rtx-eNW->smoothx,rty-eNW->smoothy,64);
					
					float height1=eNW->Blox[Units[i].x][Units[i].y];
					float height2=eNW->Blox[Units[i].x+1][Units[i].y];
					float height3=eNW->Blox[Units[i].x][Units[i].y+1];
					float height4=eNW->Blox[Units[i].x+1][Units[i].y+1];
					
					int relx=32+Units[i].relx+Units[i].rely;
					int rely=Units[i].rely-Units[i].relx;
					
					rely/=2;
					//rely+=16;
					
					int relheight=0;
					
					vector v1,v2,v3;
					
					if (relx<32)
					{
						v1.x=0; v1.y=16; v1.z=height1;
						v2.x=32; v2.y=0; v2.z=height2;
						v3.x=32; v3.y=32; v3.z=height3;
					}
					else
					{
						v1.x=32; v1.y=0; v1.z=height1;
						v2.x=64; v2.y=16; v2.z=height4;
						v3.x=32; v3.y=32; v3.z=height3;
					};
					
					relheight=getplaneheight(v1,v2,v3,relx,rely);

					//relx-=16;
					//rely-=16;
					//rely/=2;
					
					int16 z=rty/16;
					rtx+=relx-eNW->smoothx;
					rty+=rely-relheight-eNW->smoothy;

					Units[i].dispx=rtx;
					Units[i].dispy=rty;

					//printf ("Unit %d rtx %d rty %d\n",i,rtx,rty);

					eG32->CZBlit(chp,rtx,rty,zbuffer,z+6,eNW->smoothx,eNW->smoothy);
					
					// Note: z+6 because upper border takes 4 rows,
					// and there must be room of about 2 rows.
					
					bool justnow=false;
					if (eNW->MouseButt() && modifiers())
					{
						if (mx>=rtx-(tw<<5) && mx<=rtx+(tw<<5) && my>=rty-(th<<4) && my<=rty+(th<<4) && !eNW->EditMode && !eNW->BuildMode && !eNW->Dragging)
						{
							for (int j=0; j<eNW->Units_Created; j++)
							{
								if (Units[j].active)
								{
									Units[j].state=UNIT_STATE_ATTACKING;
									Units[j].state_data=0;
									Units[j].state_data2=i;
								}
							};
							//Units[i].active=1;
							//Units[i].activated_frame=8;
							//Activated=i+1;
							//justnow=true;
						};
					};
					if (Units[i].active)
					{
						int af=Units[i].activated_frame;
						if (af>0) {Units[i].activated_frame--; af--;};
					
						int adder=(af & 1)*4;
					
						eG32->Blix(512,rtx-(tw<<4)-8,rty-(th<<4)-6,128);
						eG32->Box(rtx-(tw<<4)-6,rty-(th<<4)+3+(30-Units[i].health),rtx-(tw<<4)-3,rty-(th<<4)+33,0x80ff80,0xff8080);
					
						eG32->Blix(400+adder,rtx-(tw<<4)-2-af,rty-(th<<4)-2-af,64);
						eG32->Blix(401+adder,rtx+(tw<<4)-6+af,rty-(th<<4)-2-af,64);
						eG32->Blix(402+adder,rtx-(tw<<4)-2-af,rty+(th<<4)-6+af,64);
						eG32->Blix(403+adder,rtx+(tw<<4)-6+af,rty+(th<<4)-6+af,64);
						if (Activated && !justnow)
						{
							Units[i].active=0;
						};
					};
				};
			};
		};
	};
	if (Activated)
	{
		for (i=0; i < Activated-1; i++)
		{
			if (Units[i].active)
			{
				Units[i].active=0;
			};
		};
		Activated=true;
	};
	
	i=0;
	
	for (i=0;i<eNW->Objects_Created;i++)
	{
		if (Objects[i].type)
		{
			tx=Objects[i].x;
			ty=Objects[i].y;
			tw=Objects[i].w;
			th=Objects[i].h;
			int rtx=0; int rty=0;
			if (tx>=eNW->mapx-4 && ty>=eNW->mapy-4 && tx<=eNW->mapx+NW_WIDTH/64+2 && ty<=eNW->mapy+NW_HEIGHT/16+2)
			{
				chp=CHAPESBASE_OBJECTS+Objects[i].type;

				/*int height1=Blox[Units[i].x][Units[i].y];
				int height2=Blox[Units[i].x+1][Units[i].y];
				int height3=Blox[Units[i].x][Units[i].y];
				int height4=Blox[Units[i].x+1][Units[i].y];
				int relheight=(height1+height2+height3+height4)>>2;*/
				//rtx=32+((tx-eNW->mapx)*32+(ty-eNW->mapy)*32)+Units[i].relx+Units[i].rely*2;				
				//rty=16+(NW_HEIGHT/2+(Units[i].y-eNW->mapy)*16-(Units[i].x-eNW->mapx)*16-relheight)+Units[i].rely-Units[i].relx/2;

				/*rtx=32+((tx-eNW->mapx)*32+(ty-eNW->mapy)*32);
				rty=16+(NW_HEIGHT/2+(ty-eNW->mapy)*16-(tx-eNW->mapx)*16);*/
				
				int ttx=tx-eNW->mapx;
				int tty=ty-eNW->mapy;
				for (int ly=0; ly<30; ly++)
					for (int lx=0; lx<10; lx++)
						if (eNW->Cmap[lx][ly].x==ttx && eNW->Cmap[lx][ly].y==tty)
				{
					rtx=lx*64+(ly&1)*32;
					rty=ly*16;
				};
				if (rtx || rty)
				{
					int16 z=rty/16;
					eG32->Blix(61,rtx-eNW->smoothx,rty-eNW->smoothy,128);
					eG32->ZBlit(chp,rtx+32-eNW->smoothx,rty+30-eNW->smoothy,zbuffer,z+2,eNW->smoothx,eNW->smoothy);
				};
			};
		};
	};
	
	for (i=0;i<eNW->Relanims_Created;i++)
	{
		if (Relanims[i].startframe)
		{
			tx=Relanims[i].x;
			ty=Relanims[i].y;
			tw=Relanims[i].w;
			th=Relanims[i].h;
			int rtx=0; int rty=0;
			if (tx>=eNW->mapx-2 && ty>=eNW->mapy-2 && tx<=eNW->mapx+NW_WIDTH/64+2 && ty<=eNW->mapy+NW_HEIGHT/16+2)
			{
				int ttx=tx-eNW->mapx;
				int tty=ty-eNW->mapy;
				for (int ly=0; ly<30; ly++)
					for (int lx=0; lx<10; lx++)
						if (eNW->Cmap[lx][ly].x==ttx && eNW->Cmap[lx][ly].y==tty)
				{
					rtx=lx*64+(ly&1)*32;
					rty=ly*16;
				};
				
				if (rtx || rty)
				{
					/*float height1=eNW->Blox[tx][ty];
					float height2=eNW->Blox[tx+1][ty];
					float height3=eNW->Blox[tx][ty+1];
					float height4=eNW->Blox[tx+1][ty+1];*/
					
					int chp=Relanims[i].startframe+Relanims[i].frame;
					
					int relx=16; //+Relanims[i].relx;
					int rely=16; //+Relanims[i].rely*2;
					
					int relheight=0;
					
					relx-=16;
					rely-=16;
					rely/=2;
					
					int16 z=rty/16;
					rtx+=32+relx+rely*2-eNW->smoothx;
					rty+=16+rely-relx/2-relheight-eNW->smoothy;

					/*Units[i].dispx=rtx;
					Units[i].dispy=rty;*/
					
					if (Relanims[i].transparent)
					{
						eG32->Blix(chp,rtx,rty,50);
					}
					else
					{
						eG32->Blit(chp,rtx,rty);
					};
				};
			};
			Relanims[i].frame++;
			if (Relanims[i].frame>=Relanims[i].duration)
			{
				Relanims[i].startframe=0;
				Relanims[i].frame=0;
				if (i==eNW->Relanims_Created-1) eNW->Relanims_Created--;
			};
		};
	};
	
	DrawBuildings(2);
};

void Store_GFX::UpDate()
{
	drawn=false;
};