/*
	Soeki - The Plague
	Unit Action Processing
	©1999,2000 L. Hartmann / Atomatrix
*/

#include "processing.h"

Store* pNW;
gfx_32* pG32;
Store_NET* pNET;

void Store_PRC::Connect(Store* n,gfx_32* g,Store_NET* nt)
{
	pNW=n;
	pG32=g;
	pNET=nt;
	
	Units=pNW->Units;
	Relanims=pNW->Relanims;
};

void Store_PRC::StepTable(int unum)
{
	if (Units[unum].blocks) free(Units[unum].blocks);
	Units[unum].blocks=(int16*)malloc(100*100*2);
	
	int bw=100;
	
	for (int y=0; y<99; y++) for (int x=0; x<99; x++)
	{
		if (pNW->Bmap[x][y]==0)
		{
			Units[unum].blocks[x+y*bw]=-1;
		}
		else
		{
			Units[unum].blocks[x+y*bw]=-2;
		};
	};
	
	blocks[Units[unum].dx][Units[unum].dy]=0;
	
	for (int x=1; x<99; x++) for (int y=1; y<99; y++)
	{
		if (Units[unum].blocks[x+y*bw]==-1)
		{
			int tx=x; int ty=y; int tt=999;
			for (int xx=-1; xx<2; xx++) for (int yy=-1; yy<2; yy++)
			{
				if (Units[unum].blocks[x+xx+(y+yy)*bw]>=0)
				  if (Units[unum].blocks[x+xx+(y+yy)*bw]<tt) {tt=Units[unum].blocks[x+xx+(y+yy)*bw]; tx=x+xx; ty=y+yy;};
			};
			if (tt!=999) Units[unum].blocks[x+y*bw]=Units[unum].blocks[tx+ty*bw]+1;
		};
	};
	for (int x=99; x>0; x--) for (int y=99; y>0; y--)
	{
		if (Units[unum].blocks[x+y*bw]==-1)
		{
			int tx=x; int ty=y; int tt=999;
			for (int xx=-1; xx<2; xx++) for (int yy=-1; yy<2; yy++)
			{
				if (Units[unum].blocks[x+xx+(y+yy)*bw]>=0)
				  if (Units[unum].blocks[x+xx+(y+yy)*bw]<tt) {tt=Units[unum].blocks[x+xx+(y+yy)*bw]; tx=x+xx; ty=y+yy;};
			};
			if (tt!=999) Units[unum].blocks[x+y*bw]=Units[unum].blocks[tx+ty*bw]+1;
		};
	};
};

void Store_PRC::Proc()
{
	//int RotDex[16]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};
	int RotDex[16]={-1,-1,-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1};
	int i=0,j=0,x,y;
	for (i=0;i<=pNW->Units_Created;i++)
	{
		if (Units[i].type)
		{
			if (Units[i].health<=0 && Units[i].state!=UNIT_STATE_DYING)
			{
				Units[i].state=UNIT_STATE_DYING;
				bool free_found=false;
				j=0;
				if (pNW->Relanims_Created)
				{
					for (j=0; j<pNW->Relanims_Created; j++)
					{
						if (!Relanims[j].startframe)
						{
							free_found=true;
							break;
						};
					};
				};
				if (!free_found)
				{
					pNW->Relanims_Created++;
					j=pNW->Relanims_Created-1;
				};
				
				Relanims[j].startframe=160;
				Relanims[j].duration=15;
				Relanims[j].frame=0;
				Relanims[j].x=Units[i].x;
				Relanims[j].y=Units[i].y;
				Relanims[j].w=4;
				Relanims[j].h=4;
				Relanims[j].transparent=true;
				
				Units[i].state_data2=j;
			};
			if (Units[i].state==UNIT_STATE_DYING)
			{
				if (!Relanims[Units[i].state_data2].startframe)
				{
					Units[i].type=0;
					//if (i==pNW->Units_Created-1) pNW->Units_Created--;
					pNW->Bmap[Units[i].x][Units[i].y]=0;
				};
			};
			if (Units[i].state==UNIT_STATE_ATTACKING)
			{
				bool skip=false;
				if (Units[Units[i].state_data2].state==UNIT_STATE_DYING)
				{
					Units[i].state_data=0;
					Units[i].state_data2=0;
					Units[i].state=UNIT_STATE_WAITING;
					skip=true;
				};
			
				if (!skip)
				{
					int dx=Units[Units[i].state_data2].x;
					int dy=Units[Units[i].state_data2].y;
					
					int MoveX=0;
					int MoveY=0;
					
					if (dx<Units[i].x) MoveX=-1;
					if (dx>Units[i].x) MoveX=1;
					if (dy<Units[i].y) MoveY=-1;
					if (dy>Units[i].y) MoveY=1;
		
					for (int j=0;j<8;j++)
					{
						if (RotDex[j*2]==MoveX && RotDex[j*2+1]==MoveY)
						{
							Units[i].dr=j*3;
							if (Units[i].dr=8) Units[i].dr=0;
						};
					};
		
					if (Units[i].dr!=Units[i].r)
					{
						int nsteps_l=0;
						for (int j=Units[i].r; j!=Units[i].dr;)
						{
							nsteps_l++;
							j--;
							if (j<0) j=23;
						};
						int nsteps_r=0;
						for (int j=Units[i].r; j!=Units[i].dr;)
						{
							nsteps_r++;
							j++;
							if (j>23) j=0;
						};
						if (nsteps_l<nsteps_r) {Units[i].r--;} else {Units[i].r++;};
						if (Units[i].r<0) Units[i].r=23;
						if (Units[i].r>23) Units[i].r=0;
					};

					if (Units[i].dr==Units[i].r)
					{
						Units[i].state_counter++;
						if (Units[i].state_counter>=2)
						{
							Units[i].state_counter=0;
							Units[i].state_data++;
							if (Units[i].state_data==4)
							{
								Units[Units[i].state_data2].health-=1;
								Units[i].state_data=0;
							};
						};
					};
				};
			};
			if (Units[i].state==UNIT_STATE_MOVING)
			{
				NW_Unit wunit;
				memcpy (&wunit,&Units[i],sizeof(NW_Unit));
				if (wunit.dx==wunit.x && wunit.dy==wunit.y && wunit.relx==0 && wunit.rely==0)
				{
					/*free(wunit.blocks);
					wunit.blocks=0;*/
					wunit.state=UNIT_STATE_WAITING;
					wunit.dx=0;
					wunit.dy=0;
					pNW->Bmap[wunit.x][wunit.y]=i+1;
				}
				else
				{
					bool xnot=false;
					bool ynot=false;
					
					for (y=wunit.y-wunit.h; y<=wunit.y; y++)
					{
						for (x=wunit.x-wunit.w; x<=wunit.x; x++)
						{
							pNW->Bmap[x][y]=0;
						};
					};
					
					int speed=3;
	
					if (wunit.relx>=16) {wunit.x++; wunit.relx=(-16)+speed; xnot=true;};
					if (wunit.relx<=-16) {wunit.x--; wunit.relx=(16)-speed; xnot=true;};
					if (wunit.rely>=16) {wunit.y++; wunit.rely=(-16)+speed; ynot=true;};
					if (wunit.rely<=-16) {wunit.y--; wunit.rely=(16)-speed; ynot=true;};
	
					int MoveX=0;
					int MoveY=0;
					
					
					
					// PHIND
					
					/*int sx=wunit.x;
					int sy=wunit.y;
					int tt=wunit.blocks[sx+sy*100];
					int tx=0,ty=0;
					
					for (y=-1; y<2; y++) for (x=-1; x<2; x++)
					{
						if (wunit.blocks[sx+x+(sy+y)*100]>0)
						{
							if (wunit.blocks[sx+x+(sy+y)*100]<tt) {tt=wunit.blocks[sx+x+(sy+y)*100]; tx=sx+x; ty=sy+y;};
						};
					};*/
					
					if (wunit.dx<wunit.x) MoveX=-1;
					if (wunit.dx>wunit.x) MoveX=1;
					if (wunit.dy<wunit.y) MoveY=-1;
					if (wunit.dy>wunit.y) MoveY=1;
	
					// End of PHIND
	
					// BMapTest
					
					int tst=0;
					
					for (y=wunit.y-wunit.h; y<=wunit.y; y++)
					{
						for (x=wunit.x-wunit.w; x<=wunit.x; x++)
						{
							if (pNW->Bmap[x+MoveX][y+MoveY]>0 && pNW->Bmap[x+MoveX][y+MoveY]!=i+1) tst=1;
						};
					};
	
					int quadspeed=speed*speed;
	
					// power of 2 to eliminate signedness
	
					if (MoveX==0 && wunit.relx*wunit.relx>quadspeed)
					{
						if (wunit.relx>0) MoveX=-1;
						if (wunit.relx<0) MoveX=1;
					};
					if (MoveY==0 && wunit.rely*wunit.rely>quadspeed)
					{
						if (wunit.rely>0) MoveY=-1;
						if (wunit.rely<0) MoveY=1;
					};
					
					for (int j=0;j<8;j++)
					{
						if (RotDex[j*2]==MoveX && RotDex[j*2+1]==MoveY)
						{
							wunit.dr=j*3;
						};
					};
	
					if (wunit.dr!=wunit.r)
					{
						int nsteps_l=0;
						for (int j=wunit.r; j!=wunit.dr;)
						{
							nsteps_l++;
							j--;
							if (j<0) j=23;
						};
						int nsteps_r=0;
						for (int j=wunit.r; j!=wunit.dr;)
						{
							nsteps_r++;
							j++;
							if (j>23) j=0;
						};
						if (nsteps_l<nsteps_r) {wunit.r--;} else {wunit.r++;};
						if (wunit.r<0) wunit.r=23;
						if (wunit.r>23) wunit.r=0;
					};
	
					if (wunit.dr==wunit.r && !tst)
					{
						if (!xnot) wunit.relx+=MoveX*speed;
						if (!ynot) wunit.rely+=MoveY*speed;
					};
					
					for (y=wunit.y-wunit.h; y<=wunit.y; y++)
					{
						for (x=wunit.x-wunit.w; x<=wunit.x; x++)
						{
							pNW->Bmap[x][y]=i+1;
							//int rtx=(x-pNW->mapx)*32+(y-pNW->mapy)*32;				
							//int rty=pNW->NW_HEIGHT/2+(y-pNW->mapy)*16-(x-pNW->mapx)*16;
							int tx=x-pNW->mapx;
							int ty=y-pNW->mapy;
							int rtx=0,rty=0;
							/*for (int ly=0; ly<30; ly++)
								for (int lx=0; lx<10; lx++)
									if (pNW->Cmap[lx][ly].x==tx && pNW->Cmap[lx][ly].y==ty)
							{
								rtx=lx*64+(ly&1)*32;
								rty=ly*16;
							};
							if (rtx && rty) pG32->Blix(61,rtx,rty);*/
							/*if (!xnot && !ynot)
							{
								Bmap[x+MoveX][y+MoveY]=i+1;
								rtx=(MoveX+x-pNW->mapx)*32+(MoveY+y-pNW->mapy)*32;				
								rty=NW_HEIGHT/2+(MoveY+y-pNW->mapy)*16-(MoveX+x-pNW->mapx)*16;
								G32.Blix(61,rtx,rty);
							};*/
						};
					};
				};
				pNET->UpdateUnit(i,&wunit,0);
			};
		};
	};
};
