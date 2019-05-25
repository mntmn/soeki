/*
	Networ Master Functions And Data
	© 1999 L.Hartmann/Atomatrix Entertainment
	BeOS version
*/

#include "master.h"
#include "../../independent/engine.h"
#include <stdlib.h>
#include <math.h>
	
#define FINETRIANGLES 1
	
#ifdef FINETRIANGLES
#include "magic.h"
AlphasMagic GTT;
#else
#include "trimap.h"
AlphasMagic GTT(640);
#endif

gfx_32* nG32;
assd* nASS;
Store_DAT* nDAT;

//key_map* KEYZ;
char* CHARZ;

int32_t WIDTH=640;
int32_t HEIGHT=480;
	
#define BUF_WIDTH (640+256)
#define BUF_HEIGHT (480+128)
	
MouseAround::MouseAround()
{
};
	
bool NetworDisplay::md()
{
  return _md;
};
	
uint32_t NetworDisplay::mx()
{
  return _mx;
};
	
uint32_t NetworDisplay::my()
{
  return _my;
};

NetworDisplay::NetworDisplay()
{
  kick_me=(uint32_t*)malloc(WIDTH*HEIGHT*4*2);

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Soeki", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI );
  if (window == NULL) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }
  screenSurface = SDL_GetWindowSurface( window );
  SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

  Update();
  
  nASS->Debug ("Screen set up.\n");
  didthejob=true;
};

void NetworDisplay::Update() {

  for (int y=0; y<HEIGHT; y++) {
    for (int x=0; x<WIDTH; x++) {
      uint32_t *p = ((uint32_t *)screenSurface->pixels) + y * WIDTH + x;
      *p = *(kick_me + y * WIDTH + x);
    }
  }
  
  SDL_UpdateWindowSurface( window );
  
  SDL_Event e;
  
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT) {
      exit(0);
    }
    if(e.type == SDL_MOUSEBUTTONDOWN) {
      _md = 1;
    }
    if(e.type == SDL_MOUSEBUTTONUP) {
      _md = 0;
    }
    if(e.type == SDL_MOUSEMOTION) {
      _mx = e.motion.x;
      _my = e.motion.y;
    }
  }
  
  SDL_PumpEvents();
}

void NetworDisplay::ScreenConnected(bool really)
{
};
	
bool NetworDisplay::QuitRequested()
{
  nASS->Debug("NetworDisplay::QuitRequested()\n");
  didthejob=false;
  printf ("Display disconnected.\n");
  return true;
};
	
void NetworDisplay::MessageReceived(void* msg)
{
  /*char debuffer[100];
		sprintf(debuffer,"Msg: 0x%x",(unsigned int)msg->what);
		nASS->Debug(debuffer);*/
		
  int32_t key=0,len=0;

  // FIXME
  switch (0) //msg->what)
		{
		case 1: //B_KEY_DOWN:
			
			break;
      //case B_KEY_UP:
      //	kd=0;
		};
};
	
//*****************************************************************************

void Store::Connect(assd* a,gfx_32* g,Store_DAT* d)
{
  nASS=a;
  nG32=g;
  nDAT=d;
};

bool Store::MouseButt()
{
  if (running) 
		{
			return NWWindow->md();
		};
  return 0;
};

int Store::GetKey()
{
  return 0;
};
	
void Store::FreeChape(int c)
{
  if (Chapes[c].chunk)
		{
			free(Chapes[c].chunk);
			Chapes[c].chunk=0;
			Chapes[c].w=0;
			Chapes[c].h=0;
			Chapes[c].xhandle=0;
			Chapes[c].yhandle=0;
		};
};

void Store::Show()
{
  /*#ifndef PAGEFLIP*/
  Chunky=NWWindow->kick_me; //+NW_WIDTH*NW_HEIGHT;
  /*#endif*/

  if (!running) return;
  int i=0;

  nG32->Use(Chunky);
  //if (PreMain) nG32->Kopy(Chunky2,Chunky);
  if (Console_Running)
		{
			for (i=0;i<=Console_Y;i++)
        {
          Console_X=Dynt(10,10+i*(Chapes[1].h+3),&Console[i][0]);
        };
					
			if (ub) nG32->Blit(36,10,10+(Console_Y+1)*(Chapes[1].h+3));
		};

		
  //nG32->Konvert(Chunky,NWWindow->kick_me);
		
  //#ifdef PAGEFLIP
  /*	if (!ub)
			{
      NWWindow->MoveDisplayArea(0,NW_HEIGHT);
      Chunky=NWWindow->kick_me;
			}
			else
			{
      NWWindow->MoveDisplayArea(0,0);
      Chunky=NWWindow->kick_me+NW_WIDTH*NW_HEIGHT;
			};*/
  /*#else
    NWWindow->HardwareBlit(0,480,0,0,639,479);
    NWWindow->HardwareSync();
		#endif*/
		
  nG32->Use(Chunky);

  nG32->Blix(62,MouseX(),MouseY(),40);

  ub=1-ub;

  char Out[50];

  if (GetKey()==0x21)
		{
			sprintf (Out,"screenshots/shot%d.dat",ScreenShot);

			FILE* TheFile=nDAT->Open(Out,DAT_WRITE);
			nDAT->Write(TheFile,Chunky,NW_WIDTH*NW_HEIGHT*4);
			nDAT->Close(TheFile);
			ScreenShot++;
		};
		
  PreMain=true;
  int cnt=0;
  //while (PreMain)
  //{
  //snooze(1000);
  //};

  NWWindow->Update();
};
	
bool Store::IsActive()
{
  // implementation needed!
  return true;
};
	
void Store::LoadChape(int chapenum,const char fname[],int w,int h)
{
  int res=0;

  if (Chapes[chapenum].chunk) free(Chapes[chapenum].chunk);

  FILE* TheFile=nDAT->Open(fname,DAT_READ);
  if (!TheFile) {
    printf("error: file %s not found.\n",fname);
    exit(1);
  }
 
  Chapes[chapenum].w=w-1;
  Chapes[chapenum].h=h-1;
  Chapes[chapenum].xhandle=0;
  Chapes[chapenum].yhandle=0;
  Chapes[chapenum].chunk=(uint32_t*)malloc(w*h*4);
		
  res=nDAT->Read(TheFile,Chapes[chapenum].chunk,w*h);
  nDAT->Close (TheFile);
		
  /*		if (Console_Running)
        {
        strncat(Out,strupr(fname),25);
        strcat(Out," LOADED!");
        this->OutCon(Out);
        this->Show();
        };*/
		
  if (!res)
		{
			printf("Error loading chape %s",fname);
      //			exit(1005);
		};
};
	
void Store::LoadChape(int chapenum,const char fname[])
{
  int res=0;
  char buf[6]="\0\0\0\0";
  char Out[75]="b  CHAPE ";

  FILE* TheFile=nDAT->Open(fname,DAT_READ);
  if (!TheFile) {
    printf("error: file %s not found.\n",fname);
    exit(1);
  }
    
  int w,h;

  res=nDAT->Read(TheFile,buf,4);
		
  printf("magic: %c%c%c%c\n",buf[0],buf[1],buf[2],buf[3]);
		
  if (strncmp("AMXC",buf,4))
		{
			printf("Sorry, file \"%s\" is no Atomatrix Chape.\n",fname);
			nDAT->Close(TheFile);
      //			exit(1113);
			goto outback2;
		};

  if (Chapes[chapenum].chunk) free(Chapes[chapenum].chunk);

  res=nDAT->Read(TheFile,&Chapes[chapenum],8);

  w=Chapes[chapenum].w+1;
  h=Chapes[chapenum].h+1;
  Chapes[chapenum].chunk=(uint32_t*)malloc(w*h*4);
		
  res=nDAT->Read(TheFile,Chapes[chapenum].chunk,w*h*4);
  nDAT->Close (TheFile);
		
 outback2:	if (!res)
		{
			printf("Error loading chape %s",fname);
      //			exit(1005);
		};
};
	
void Store::LoadChapes(int chapenum,int max,const char fname[])
	{
		int res=0;
		char buf[5]="\0\0\0\0";
		int cnt=1;

		FILE* TheFile=nDAT->Open(fname,DAT_READ);
    if (!TheFile) {
      printf("error: file %s not found.\n",fname);
      exit(1);
    }

		res=nDAT->Read(TheFile,buf,4);
		int w,h;
		int cmpr=0;
		
		printf("res2: %d magic2: %c%c%c%c\n",res,buf[0],buf[1],buf[2],buf[3]);
		
		if (strncmp("AMXC",buf,4))
		{
			if (strncmp("AMCC",buf,4))
			{
				printf("Sorry, file \"%s\" is no Atomatrix Chape.\n",fname);
				nDAT->Close(TheFile);
				goto outback;
			}
			else
			{
				printf ("File \"%s\" is compressed!\n",fname);
				cmpr=1;
			};
		};

	ReadLoop:

		if (Chapes[chapenum].chunk) free(Chapes[chapenum].chunk);

		res=nDAT->Read(TheFile,&Chapes[chapenum],16);

		w=Chapes[chapenum].w+1;
		h=Chapes[chapenum].h+1;

		if (!cmpr)
		{
			Chapes[chapenum].chunk=(uint32_t*)malloc(w*h*4);
			res=nDAT->Read(TheFile,Chapes[chapenum].chunk,w*h*4);
		}
		else
		{
			uint32_t ncnt=0;
			nDAT->Read(TheFile,&ncnt,4);
			ncnt++;
			Chapes[chapenum].chunk=(uint32_t*)malloc(ncnt*4);
			nDAT->Read(TheFile,Chapes[chapenum].chunk,ncnt*4);
		};
		
		/*printf ("About to read: %d\n",(w+1)*(h+1)*4);
		printf ("Really read  : %d\n",res);*/
		
		strcpy(buf,"    ");
		res=nDAT->Read(TheFile,buf,4);
		if ((!strncmp("AMXC",buf,4) || !strncmp("AMCC",buf,4)) && max>=chapenum)
		{
			//printf ("Chapenum: %d\n",chapenum);
			chapenum++;
			cnt++;
			//printf ("Chapenum: %d\n",chapenum);
			goto ReadLoop;
		};
		
/*		if (Console_Running)
		{
			strncat(Out,strupr(fname),40);
			strcat(Out," LOADED!");
			this->OutCon(Out);
			this->Show();
		};*/
			
outback:	nDAT->Close (TheFile);
		printf ("%d chapes loaded from %s\n",cnt,fname);
	};
	
	void Store::LoadBuilding(int num,const char fname[])
	{
		FILE* test=fopen("./test.amxb","r");
		char header[5];
		header[4]=0;
		fread (header,1,4,test);
		printf ("Header1: %s\n",header);
		bool got=false;
		
		for (int i=0; i<4; i++)
		{
			if (!got) {fread (header,1,4,test); printf ("Header2: %s\n",header);};
			if (!strcmp(header,"STAT"))
			{
				int chp=CHAPESBASE_BUILDINGS+i;
				Buildings[num].statics[i]=chp+1;
				fread (&Chapes[chp].w,1,4,test);
				fread (&Chapes[chp].h,1,4,test);
				fread (&Chapes[chp].xhandle,1,4,test);
				fread (&Chapes[chp].yhandle,1,4,test);
				
				printf ("w: %d h: %d xhandle: %d yhandle: %d\n",Chapes[chp].w,Chapes[chp].h,Chapes[chp].xhandle,Chapes[chp].yhandle);
				
				Chapes[chp].chunk=(uint32_t*)malloc((Chapes[chp].w+1)*(Chapes[chp].h+1)*4);
				
				fread (Chapes[chp].chunk,1,(Chapes[chp].w+1)*(Chapes[chp].h+1)*4,test);
				fread (&Buildings[num].sshadow[i],1,1,test);
				/*Ranges[i].start=i;
				Ranges[i].end=i;*/
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
			fread (Buildings[num].bmap,1,5*5,test);
		};
		fclose(test);
		printf ("Done.\n");
	};

	Store::Store()
	{
		NW_WIDTH=640;
		NW_HEIGHT=480;
		M=NW_HEIGHT/32;
	
		//get_key_map(&KEYZ,&CHARZ);
	
		printf ("Reaching the boiling point...\n");
		Chunky2=(uint32_t*)malloc(((BUF_WIDTH)*(BUF_HEIGHT))*4);

		printf ("Memory allocated.\n");

		mapx=0;
		mapy=0;
		Its_My_First_Time=true;

		Console_X=0;
		Console_Y=0;
		Console_Running=false;
		Console_LineDrawn=true;
		
		running=false;
		boxd=0;
		
		EditMode=true;
		BuildMode=false;
		Dragging=false;
		
		GRID=false;
		
		// --
		
		PreMain=true;
		ScreenShot=1;
		
		printf ("Calling GTT.MakeTable()...\n");
		
		GTT.array=Chunky2;
		GTT.MakeTable();
		
		zbuffer=GTT.Zmap;

		ub=0;

		printf ("Store::Store() success.\n");
	};
	
Store::~Store()
{	
  printf ("-[Second Half]----------------------------------\n");
  nASS->Debug ("Atomatrix Master Library cleanup:\n");
  int i=0;
  int cnt=0;
  // Chape-mem freigeben
  while (i<3000)
		{
			if (Chapes[i].chunk)
        {
          free(Chapes[i].chunk);
          cnt++;
        };
			i++;
		};
  printf("%d Chapes cleaned up.\n",cnt);

  free (Chunky2);
  running=false;
  printf ("Atomatrix Master Library cleaned up and halted.\n");
  printf ("So long, and thanks for all the fish!\n");
};
	
void Store::ToFront()
{
  //NWWindow->MakeFocus();
};
	
uint32_t Store::MouseX()
{
  if (running) 
		{
			return NWWindow->mx();
		};
  return 0;
};
	
uint32_t Store::MouseY()
{
  if (running) 
		{
			return NWWindow->my();
		};
  return 0;
};
	
void Store::CustomTri(int x1,int y1,int x2,int y2,int x3,int y3,int f,int tx1,int ty1,int tx2,int ty2,int tx3,int ty3)
{
  GTT.array=Chunky;
  GTT.array_tex1=Textures[20].data;
		
  int l[9]={127,127,180,190,180,64,32,64,127};
		
  TriangleDef td;
	
  td.a[0]=x1 << 16;
  td.a[1]=y1;
  td.a[2]=tx1 << 16;
  td.a[3]=ty1 << 16;
  td.a[4]=64 << 16;
					
  td.b[0]=x2 << 16;
  td.b[1]=y2;
  td.b[2]=tx2 << 16;
  td.b[3]=ty2 << 16;
  td.b[4]=l[f] << 16;

  td.c[0]=x3 << 16;
  td.c[1]=y3;
  td.c[2]=tx3 << 16;
  td.c[3]=ty3 << 16;
  td.c[4]=l[f+1] << 16;
	
  //GTT.Triangle(&td);
  GTT.array=Chunky2;
};
	
void Store::IsoScape(int sc,int ec,int sr,int er,int ymode)
{		
  int mapx=this->mapx;
  int mapy=this->mapy;
  int ysub,ysub2,ysub3,ysub4;
  int lsub,lsub2,lsub3,lsub4;
  int tex;
		
  int m=BUF_HEIGHT/64;
		
  int cdx[5],cdy[5];

  int x=0,y=0,incx=0,incy=0,lineswitch;
  int16_t rows,cols;
  int ty1, tx2;
		
  incy=sr>>1;
  incy+=sr&1;		
  incx=sr>>1;

  nG32->Use(Chunky2);
  nG32->NW_WIDTH=BUF_WIDTH; // Very dirty hack
  nG32->NW_HEIGHT=BUF_HEIGHT; // Dirty hack #2

  for (rows=sr;rows<er;rows++)
		{
			lineswitch=rows & 1;
			for (cols=sc;cols<ec;cols++)
        {
          TriangleDef	td;
          x=-2+(m+cols)-incx;   // -2 because of scroll trick offset
          y=-2+(cols-m)+incy;   // -2 because of scroll trick offset

          if (Its_My_First_Time)
            {
              if (cols>=0 && rows>=0 && cols<=39 && rows<=39)
                {
                  Cmap[cols][rows].x=x;
                  Cmap[cols][rows].y=y+4;   // +4 because of scroll trick offset
                };
            };
				
          if (mapx+x>=0 && mapy+y>=0)
            {
              tex=Tex[mapx+x][mapy+y];

              //printf("use tex: %d %p\n",Tex[mapx+x][mapy+y],Textures[Tex[mapx+x][mapy+y]].data);
              GTT.array_tex1=Textures[Tex[mapx+x][mapy+y]].data;
					
              ysub=Blox[mapx+x][mapy+y]; //fact;
              ysub2=Blox[mapx+x+1][mapy+y]; //fact;
              ysub3=Blox[mapx+x][mapy+y+1]; //fact;
              ysub4=Blox[mapx+x+1][mapy+y+1]; //fact;
					
              ty1 = (rows<<4);
              tx2 = (cols<<6)+(lineswitch<<5);
	
              cdx[1]=tx2;
              cdy[1]=ty1+16-ysub;
					
              cdx[2]=tx2+32;
              cdy[2]=ty1-ysub2;
					
              cdx[4]=tx2+64;
              cdy[4]=ty1+16-ysub4;
	
              cdx[3]=cdx[2];
              cdy[3]=ty1+32-ysub3;
					
              bool skip=false;
					
              if (ymode==1) // Scrolling upwards?
                {
                  if (cdy[2]>=64) skip=true;
                };
					
              lsub=(((int)Light[mapx+x][mapy+y])<<1)&0xf0;
              lsub2=(((int)Light[mapx+x+1][mapy+y])<<1)&0xf0;
              lsub3=(((int)Light[mapx+x][mapy+y+1])<<1)&0xf0;
              lsub4=(((int)Light[mapx+x+1][mapy+y+1])<<1)&0xf0;
					
              if (cdy[2]<cdy[3] && !skip)
                {
                  td.a[0]=cdx[1] << 16;
                  td.a[1]=cdy[1];
                  td.a[2]=1 << 16;
                  td.a[3]=1 << 16;
                  td.a[4]=lsub << 16;
						
                  td.b[0]=cdx[2] << 16;
                  td.b[1]=cdy[2];
                  td.b[2]=254 << 16;
                  td.b[3]=1 << 16;
                  td.b[4]=lsub2 << 16;
						
                  td.c[0]=cdx[3] << 16;
                  td.c[1]=cdy[3];
                  td.c[2]=1 << 16;
                  td.c[3]=254 << 16;
                  td.c[4]=lsub3 << 16;
	
                  // draw left triangle
						
                  if (ymode!=2)
                    {
                      GTT.Triangle(&td,rows-1);
                    }
                  else
                    {
                      GTT.Triangle(&td,600+rows-1);
                    };

                  td.a[0]=cdx[2] << 16;
                  td.a[1]=cdy[2];
                  td.a[2]=254 << 16;
                  td.a[3]=1 << 16;
                  td.a[4]=lsub2 << 16;
						
                  td.b[0]=cdx[4] << 16;
                  td.b[1]=cdy[4];
                  td.b[2]=254 << 16;
                  td.b[3]=254 << 16;
                  td.b[4]=lsub4 << 16;
						
                  td.c[0]=cdx[3] << 16;
                  td.c[1]=cdy[3];
                  td.c[2]=1 << 16;
                  td.c[3]=254 << 16;
                  td.c[4]=lsub3 << 16;
	
                  // draw right triangle
						
                  if (ymode!=2)
                    {
                      GTT.Triangle(&td,rows-1);
                    }
                  else
                    {
                      GTT.Triangle(&td,600+rows-1);
                    };
                };
            }
          else
            {
              ty1 = (rows<<4);
              tx2 = (cols<<6)+(lineswitch<<5);
              nG32->Blit(560,tx2,ty1);
            };
        };
			incx+=(lineswitch);
			incy+=(1-lineswitch);
		};
  Its_My_First_Time=false;	
  nG32->Use(Chunky);
  nG32->NW_WIDTH=640; // Clean up...
  nG32->NW_HEIGHT=480; // ...dirty hacks
};
	
void Store::MakeLight(int x,int y)
{
  if (x<1 || y<1 || x>98 || y>98) return;
		
  double lx=-150;
  double ly=-150;
  double lz=180;
  double llen=sqrt(lx*lx+ly*ly+lz*lz);
  lx/=llen; //normalisieren des Lichts
  ly/=llen;
  lz/=llen;

  double p1x=0,p1y=0,p2x=32,p2y=0,p3x=32,p3y=32,p4x=0,p4y=32;
		
  double p1z=Blox[x][y]; //z1  1 2
  double p2z=Blox[x+1][y]; //z2  4 3
  double p3z=Blox[x+1][y+1]; //z3
  double p4z=Blox[x][y+1]; //z4
  //calculate upper normal
  double kpx=(p1y-p2y)*(p1z-p4z)-(p1z-p2z)*(p1y-p4y);
  double kpy=(p1z-p2z)*(p1x-p4x)-(p1x-p2x)*(p1z-p4z);
  double kpz=(p1x-p2x)*(p1y-p4y)-(p1y-p2y)*(p1x-p4x);
  double len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
  if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0;}
  UpperNrm[x][y].nx=kpx;
  UpperNrm[x][y].ny=kpy;
  UpperNrm[x][y].nz=kpz;

  //double lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;

  //calculate lower normal
  kpx=(p4y-p2y)*(p4z-p3z)-(p4z-p2z)*(p4y-p3y);
  kpy=(p4z-p2z)*(p4x-p3x)-(p4x-p2x)*(p4z-p3z);
  kpz=(p4x-p2x)*(p4y-p3y)-(p4y-p2y)*(p4x-p3x);
  len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
  if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0;}
  //lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;
  LowerNrm[x][y].nx=kpx;
  LowerNrm[x][y].ny=kpy;
  LowerNrm[x][y].nz=kpz;
		
  kpx=(UpperNrm[x][y].nx+UpperNrm[x][y-1].nx+UpperNrm[x-1][y].nx+
       LowerNrm[x-1][y-1].nx+LowerNrm[x-1][y].nx+LowerNrm[x][y-1].nx)/6.0;
  kpy=(UpperNrm[x][y].ny+UpperNrm[x][y-1].ny+UpperNrm[x-1][y].ny+
       LowerNrm[x-1][y-1].ny+LowerNrm[x-1][y].ny+LowerNrm[x][y-1].ny)/6.0;
  kpz=(UpperNrm[x][y].nz+UpperNrm[x][y-1].nz+UpperNrm[x-1][y].nz+
       LowerNrm[x-1][y-1].nz+LowerNrm[x-1][y].nz+LowerNrm[x][y-1].nz)/6.0;
  double lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*30+30;
  Light[x][y]=(int16_t)lf;	
};
	
void Store::DyNum(int x,int y,unsigned int num)
{
  int i;
  char buf[10];
  sprintf(buf,"%d",num);
  for (i=0;i<5;i++)
		{
			if (buf[i]!=0) nG32->Blit(301+(buf[i]-0x30)*4,x+i*4,y);
		};
};
	
void Store::Attex(int x,int y,int t,int b)
{	
  unsigned char BlockBitz[16]=
		{
     0,8,12,4,
     5,1,3,2,
     10,7,11,13,
     14,9,6,15
     /*	%00000000, %00001000, %00001100, %00000100,
        %00000101, %00000001, %00000011, %00000010,
        %00001010, %00000111, %00001011, %00001101,
        %00001110, %00001001, %00000110, %00001111*/
		};
		
  for (int i=0;i<16;i++)
		{
			if (BlockBitz[i]==(BlockBitz[Tex[x][y]-b]|BlockBitz[t])) {Tex[x][y]=i+b; /*printf("Hit: %d | %d = %d",BlockBitz[Tex[x][y]-b],BlockBitz[t-b],BlockBitz[i+b]);*/}
		};
};
	
void Store::Dyntex(int x,int y)
{
  unsigned char Tile;
  unsigned char This[5];
		
  int i;
		
  unsigned char BlockBitz[16]=
		{
     0,4,12,8,
     9,1,3,2,
     6,11,7,13,
     14,5,10,15
     /*	%00000000, %00000100, %00001100, %00001000,
        %00001001, %00000001, %00000011, %00000010,
        %00000110, %00001011, %00000111, %00001101,
        %00001110, %00000101, %00001010, %00001111*/
		};
		
  Tile=0;
  This[0]=(Tex[x][y]/15)*15;
  This[1]=(Tex[x][y-1]/15)*15;
  This[2]=(Tex[x+1][y]/15)*15;
  This[3]=(Tex[x][y+1]/15)*15;
  This[4]=(Tex[x-1][y]/15)*15;
  for (i=1;i<5;i++)
		{
			if (This[i]==0 || This[i]==15 || This[i]==30 || This[i]==45 || This[i]==60)
        {
          if (This[0]<This[i])
            {
              Tile|=1<<(i-1); 
              if (i==4) Tile|=1;
              else Tile|=1<<i;
            };
        };
		};
  This[1]=(Tex[x-1][y-1]/15)*15;
  This[2]=(Tex[x+1][y-1]/15)*15;
  This[3]=(Tex[x+1][y+1]/15)*15;
  This[4]=(Tex[x-1][y+1]/15)*15;
  for (i=1;i<5;i++)
		{
			if (This[i]==0 || This[i]==15 || This[i]==30 || This[i]==45 || This[i]==60)
        {
          if (This[0]<This[i])
            {
              Tile|=1<<(i-1);
            };
        };
		};
  unsigned char T=((Tex[x][y])/15)*15;
  for (i=0;i<16;i++)
		{
			if (BlockBitz[i]==Tile) this->Attex(x,y,i,T);
		};
};
	
int Store::Dynt(int x,int y,char* text)
{
  int i=0;
  int base=0;
		
  char DynTable[12]=
		{
     '.',36,
     ',',37,
     ':',38,
     '/',39,
     '!',40,
     '\"',41
		};
		
  while (*(text+i))
		{
			if (*(text+i)>='A' && text[i]<='Z') {nG32->Blit(base+*(text+i)-'A',x,y); x+=Chapes[base+*(text+i)-'A'].w+2;}
			else
        if (*(text+i)>='0' && text[i]<='9') {nG32->Blit(base+26+*(text+i)-'0',x,y); x+=Chapes[base+26+*(text+i)-'0'].w+2;}
        else
          {
            bool got=false;
            for (int j=0;j<6;j++)
              {
                if (DynTable[j*2]==*(text+i))
                  {
                    nG32->Blit(base+DynTable[j*2+1],x,y);
                    x+=Chapes[base+DynTable[j*2+1]].w+2;
                    got=true;
                  };
              };
            if (!got) x+=6;
          };
			i++;
		};
  return i;
};
	
int Store::SuperDynt(int x,int y,const char* text)
{
  int i=0;
  int base=200;
  int c=0;
		
  while (*(text+i))
		{
			c=0;
			if (*(text+i)>='A' && text[i]<='Z') c=base+*(text+i)-0x41;
			else
        if (*(text+i)>='0' && text[i]<='9') c=base+26+*(text+i)-0x30;
			
			if (c)
        {
          nG32->Blit(c,x,y);
          x+=Chapes[c].w+2;
        }
			else x+=20;
			i++;
		};
  return i;
};
	
void Store::OutCon(const char* text)
{
  if (Console_Y<9) Console_Y++;
  else
		{
			for (int i=0;i<9;i++)
        {
          strncpy(&Console[i][0],&Console[i+1][0],70);
        };
		};
  strncpy(&Console[Console_Y][0],text,70);
  Console_LineDrawn=false;
};
	
void Store::MidHandle(int c)
{
  Chapes[c].xhandle=Chapes[c].w/2;
  Chapes[c].yhandle=Chapes[c].h/2;
};
	
void Store::ExChape(int c1,int c2)
{
  chape Buf;
  Buf=Chapes[c2];
  Chapes[c2]=Chapes[c1];
  Chapes[c1]=Buf;
};
	
void Store::NewStream(int chp,const char fname[])
{
  char Buf[5]="    ";
  if (Stream)
		{
			nDAT->Close(Stream);
		};
  FreeChape(chp);
		
  Stream=nDAT->Open(fname,DAT_READ);
  int res=nDAT->Read(Stream,Buf,4);
  nDAT->Read(Stream,&Chapes[chp],8);
  if (strcmp(Buf,"AMXC"))
		{
			nDAT->Close(this->Stream);
			printf("Error: %s is no valid ChapeStream file.",fname);
			exit(3000);
		};
  Chapes[chp].chunk=(uint32_t*)malloc((Chapes[chp].w+1)*(Chapes[chp].h+1)*4);
  nDAT->Read(Stream,Chapes[chp].chunk,(Chapes[chp].w+1)*(Chapes[chp].h+1)*4);
};
	
void Store::DoStream(int chp)
{
  if (Stream)
		{
			unsigned char Buf[12];
			int res=nDAT->Read(Stream,Buf,4);
			nDAT->Read(Stream,&Chapes[chp],4);
			nDAT->Read(Stream,Buf,4);
			res=nDAT->Read(Stream,Chapes[chp].chunk,(Chapes[chp].w+1)*(Chapes[chp].h+1)*4);
			if (!res)
        {
          nDAT->Close(Stream);
          Stream=0;
        };
		};
};
