/*
	Texas Support
*/

#include <math.h>
#include "../goutextri2.cpp"
AlphasMagic GTT;

int16 Light[100][100];
struct normals
{
	double nx,ny,nz,nl;
};
normals UpperNrm[100][100];
normals LowerNrm[100][100];
int Blox[100][100];
int Tex[100][100];

int Bergk[10][10]= { 0,0,0,0,0,0,0,0,0,0,
					 0,1,1,1,1,1,1,1,1,0,
					 0,1,2,2,2,2,2,2,1,0,
					 0,1,2,3,3,3,3,2,1,0,
					 0,1,2,3,4,3,3,2,1,0,
					 0,1,2,3,3,3,3,2,1,0,
					 0,1,2,3,3,3,3,2,1,0,
					 0,1,2,2,2,2,2,2,1,0,
					 0,1,1,1,1,1,1,1,1,0,
					 0,0,0,0,0,0,0,0,0,0};

int Texgk[10][10]= { 0,0,0,0,0,0,0,0,0,0,
					 0,1,2,2,2,3,0,0,0,0,
					 0,8,9,9,9,4,0,0,0,0,
					 0,8,9,9,9,4,0,0,0,0,
					 0,8,9,9,9,4,0,0,0,0,
					 0,7,6,6,6,5,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0};

class TexBerg
{
	public:
		TexBerg();
		void IsoScape(int sc,int ec,int sr,int er);
		void MakeLight(int x,int y);
};

TexBerg::TexBerg()
{
	GTT.MakeTable();
	
	for (int y=0;y<10;y++) for (int x=0;x<10;x++)
	{
		Blox[x][y]=8*Bergk[x][y];
		Tex[x][y]=Texgk[y][x];
	};
	
	for (int y=1;y<59;y++) for (int x=1;x<59;x++)
	{
		MakeLight(x,y);
	};
};

void TexBerg::IsoScape(int sc,int ec,int sr,int er)
{		
	int ysub,ysub2,ysub3,ysub4;
	int lsub,lsub2,lsub3,lsub4;
	int tex;
	
	int m=256/32;
	//int m=0;
	
	int cdx[5],cdy[5];

	int x=0,y=0,incx=0,incy=0,lineswitch;
	int rows,cols;
	int ty1, tx2;
	
	incy=sr>>1;
	incy+=sr&1;		
	incx=sr>>1;
	
	for (rows=sr;rows<er;rows++)
	{
		lineswitch=rows & 1;
		for (cols=sc;cols<ec;cols++)
		{
			TriangleDef	td;
			x=5+(cols)-incx;
			y=5+(-m+cols)+incy;
			
			if (x>=0 && y>=0)
			{
				GTT.array_tex1=Textures[0].data; //Textures[Tex[x][y]].data;
				ysub=Blox[x][y]; //fact;
				ysub2=Blox[x+1][y]; //fact;
				ysub3=Blox[x][y+1]; //fact;
				ysub4=Blox[x+1][y+1]; //fact;
				
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
				
				lsub=(((int)Light[x][y])<<1)&0xF0;
				lsub2=(((int)Light[x+1][y])<<1)&0xF0;
				lsub3=(((int)Light[x][y+1])<<1)&0xF0;
				lsub4=(((int)Light[x+1][y+1])<<1)&0xF0;
				
				td.a[0]=cdx[2] << 16;
				td.a[1]=cdy[2];
				td.a[2]=255 << 16;
				td.a[3]=0;
				td.a[4]=lsub2 << 16;
				
				td.b[0]=cdx[3] << 16;
				td.b[1]=cdy[3];
				td.b[2]=0;
				td.b[3]=255 << 16;
				td.b[4]=lsub3 << 16;
				
				td.c[0]=cdx[1] << 16;
				td.c[1]=cdy[1];
				td.c[2]=0;
				td.c[3]=0;
				td.c[4]=lsub << 16;

				GTT.Triangle(&td);
					
				td.a[0]=cdx[2] << 16;
				td.a[1]=cdy[2];
				td.a[2]=255 << 16;
				td.a[3]=0;
				td.a[4]=lsub2 << 16;
				
				td.b[0]=cdx[4] << 16;
				td.b[1]=cdy[4];
				td.b[2]=255 << 16;
				td.b[3]=255 << 16;
				td.b[4]=lsub4 << 16;
				
				td.c[0]=cdx[3] << 16;
				td.c[1]=cdy[3];
				td.c[2]=0;
				td.c[3]=255 << 16;
				td.c[4]=lsub3 << 16;
			
				GTT.Triangle(&td);
			};
		};
		incx+=(lineswitch);
		incy+=(1-lineswitch);
	};
};

void TexBerg::MakeLight(int x,int y)
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
	Light[x][y]=(int16)lf;	
};