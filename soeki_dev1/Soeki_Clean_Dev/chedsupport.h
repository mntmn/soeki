/*
	Atomatrix ChapEd support classes
*/

BTranslationUtils* unitrans;

#include <posix/malloc.h>

uint32 cutcolor=0xffffff;

struct chape
{
	uint32 w;
	uint32 h;
	int32 xhandle;
	int32 yhandle;
	uint32* chunk;
};

chape Chapes[1000];

class CESupport
{
	public:
		~CESupport();
		
		uint32* poke;
		bool working;

		void FreeChape(int num);
		void GrabChape(int num,int x,int y,int x2,int y2);
		void Blit(int num,int x,int y);
		void Line(int x1, int y1, int x2, int y2, uint32 col);
		void Copy(BBitmap* src, BBitmap* dest);
		void Clear();
		void Clear(uint32 col);
		BPoint ImportImage(char* name);
		uint32 CPoint(int x,int y);
		bool Tolerated(uint32 test, uint32 what, int tol);
};

CESupport::~CESupport()
{
	for (int i=0;i<1000;i++)
	{
		if (Chapes[i].chunk) FreeChape(i);
	};
};

void CESupport::FreeChape(int num)
{
	free(Chapes[num].chunk);
	Chapes[num].chunk=0;
};

void CESupport::GrabChape(int num,int x, int y, int x2, int y2)
{
	int swap,xs,ys,bytez=0;
	if (x>x2) {swap=x;x=x2;x2=swap;}
	if (y>y2) {swap=y;y=y2;y2=swap;}
	
	if (Chapes[num].chunk) FreeChape(num);
	
	Chapes[num].w=x2-x;
	Chapes[num].h=y2-y;
	Chapes[num].xhandle=0;
	Chapes[num].yhandle=0;
	Chapes[num].chunk=(uint32*)malloc(((x2-x)+1)*((y2-y)+1)*4);
	
	for (ys=y;ys<y2+1;ys++)
	{
		for (xs=x;xs<x2+1;xs++)
		{
			*(Chapes[num].chunk+bytez)=0x00ffffff & *(poke+xs+ys*NW_WIDTH);
			if (*(Chapes[num].chunk+bytez)==cutcolor) *(Chapes[num].chunk+bytez)=0xff0000;
			bytez++;
		};
	};
};

void CESupport::Blit(int num,int x,int y)
	{
	
		uint32* chunk=Chapes[num].chunk;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
		
		if (y<0) {chunk += (-y * w); h += y; y=0;};
		if (x<0) {w += x; xsmod = -x; x=0;};
		
		if ((y+h)>=NW_HEIGHT)
		{
			h -= (NW_HEIGHT + h) - y;
		};
		if ((x+w)>=NW_WIDTH)
		{
			xemod = (NW_WIDTH + w) - x;
			w -= xemod;
		};
		
		if (w<1 || h<1) return;
		
		uint32* pooke=poke+(y*NW_WIDTH)+x;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000) *(pooke) = *(chunk);
				pooke++;
				chunk++;
			};
			chunk+=xemod;
			pooke+=scrmod;
		};
		
		// Und feddich.
	};

void CESupport::Clear()
{
	for (int y=0; y<NW_HEIGHT; y++)
	{
		for (int x=0; x<NW_WIDTH; x++)
		{
			*(poke+x+y*NW_WIDTH)=0x00000000;
		};
	};
};

void CESupport::Clear(uint32 col)
{
	for (int y=0; y<NW_HEIGHT; y++)
	{
		for (int x=0; x<NW_WIDTH; x++)
		{
			*(poke+x+y*NW_WIDTH)=col;
		};
	};
};

void CESupport::Copy(BBitmap* src, BBitmap* dest)
{
	uint32* peek=(uint32*)src->Bits();
	uint32* poke=(uint32*)dest->Bits();
	for (int y=0; y<NW_HEIGHT; y++)
	{
		for (int x=0; x<NW_WIDTH; x++)
		{
			*(poke)=*(peek);
			peek++;
			poke++;
		};
	};
};

void CESupport::Line(int x1, int y1, int x2, int y2, uint32 colour)
	{
		uint32* dest=poke;
		int xDiff,yDiff,
		xDirection,
		minLength,
		startLength,
		runLength,
		endLength,
		errorTerm,
		fractionalAdvance,
		turnOver_reset;

		if (x1>=NW_WIDTH) x1=NW_WIDTH-1;
		if (x1<0) x1=0;
		if (y1>=NW_HEIGHT) y1=NW_HEIGHT-1;
		if (y1<0) y1=0;
		if (x2>=NW_WIDTH) x2=NW_WIDTH-1;
		if (x2<0) x2=0;
		if (y2>=NW_HEIGHT) y2=NW_HEIGHT-1;
		if (y2<0) y2=0;
		int i,j;

		if(y1>y2)
		{
			yDiff=y1;
			y1=y2;
			y2=yDiff;
			xDiff=x1;
			x1=x2;
			x2=xDiff;
		};

		dest+=x1+y1*NW_WIDTH;

		xDiff=x2-x1;
		yDiff=y2-y1;

		if(xDiff<0)
		{
			xDiff=-xDiff;
			xDirection=-1;
		}
		else
			xDirection=1;
			if(!xDiff)
			{
				for(i=0;i<=yDiff;i++)
				{
					*dest=colour;
					dest+=NW_WIDTH;
				};
				return;
			};
			if(!yDiff)
			{
				for(i=0;i<=xDiff;i++)
				{
					*dest=colour;
					dest+=xDirection;
				};
				return;
			};
			if(xDiff==yDiff)
			{
				for(i=0;i<=yDiff;i++)
				{
					*dest=colour;
					dest+=NW_WIDTH+xDirection;
				}
				return;
			};
		if(xDiff > yDiff)
		{
			minLength=xDiff/yDiff;
			fractionalAdvance=(xDiff%yDiff)<<1;
			turnOver_reset=yDiff<<1;
			errorTerm=(fractionalAdvance>>1)-turnOver_reset;
			startLength=endLength=(minLength>>1)+1;

			if(minLength&1)
				errorTerm+=yDiff;
			else
			{
				if(!fractionalAdvance)
				startLength--;
			};

			for(i=0;i<startLength;i++)
			{
				*dest=colour;
				dest+=xDirection;
			};

			dest+=NW_WIDTH;

			for(j=1;j<yDiff;j++)
			{
				runLength=minLength;
				errorTerm+=fractionalAdvance;
				if(errorTerm > 0)
				{
					errorTerm-=turnOver_reset;
					runLength++;
				};
				for(i=0;i<runLength;i++)
				{
					*dest=colour;
					dest+=xDirection;
				}
				dest+=NW_WIDTH;
			};
			for(i=0;i<endLength;i++)
			{
				*dest=colour;
				dest+=xDirection;
			};
		}
		else
		{
			minLength=yDiff/xDiff;
			fractionalAdvance=(yDiff%xDiff)<<1;
			turnOver_reset=xDiff<<1;
			errorTerm=(fractionalAdvance>>1)-turnOver_reset;

			startLength=endLength=(minLength>>1)+1;

			if(minLength&1)
				errorTerm+=xDiff;
			else 
			{
				if(!fractionalAdvance)
				startLength--;
			};

			for(i=0;i<startLength;i++)
			{
				*dest=colour;
				dest+=NW_WIDTH;
			};
			dest+=xDirection;

			for(j=1;j<xDiff;j++)
			{
				runLength=minLength;
				errorTerm+=fractionalAdvance;
				if(errorTerm > 0 )
				{
					errorTerm-=turnOver_reset;
					runLength++;
				};

				for(i=0;i<runLength;i++)
				{
					*dest=colour;
					dest+=NW_WIDTH;
				}
				dest+=xDirection;
			};

			for(i=0;i<endLength;i++)
			{
				*dest=colour;
				dest+=NW_WIDTH;
			};
		};
	};

BPoint CESupport::ImportImage(char* name)
{
	BBitmap* tempmap=unitrans->GetBitmapFile(name);
	BRect heckler=tempmap->Bounds();
	
	int width=(int)heckler.right+1;
	int height=(int)heckler.bottom+1;
	
	uint32* source=(uint32*)tempmap->Bits();
	uint32* dest=poke;
	
	for (int y=0;y<NW_HEIGHT;y++)
	{
		for (int x=0;x<NW_WIDTH;x++)
		{
			if (width>x && height>y)
			{
				*(dest)=*(source);
				source++;
			}
			else *(dest)=cutcolor;
			dest++;
		};
		if (width>NW_WIDTH)
		{
			source+=width-NW_WIDTH;
		};
	};
	
	delete tempmap;
	return BPoint(width,height);
};

uint32 CESupport::CPoint(int x,int y)
{
	uint32 yep=*(poke+x+y*NW_WIDTH);
	return yep & 0x00ffffff;
};

bool CESupport::Tolerated(uint32 test, uint32 what, int tol)
{
	int r1=(test&0xff0000)>>16;
	int g1=(test&0xff00)>>8;
	int b1=test&0xff;
	
	int r2=(what&0xff0000)>>16;
	int g2=(what&0xff00)>>8;
	int b2=what&0xff;
	
	int d=(abs(r1-r2)+abs(g1-g2)+abs(b1-b2))/3;
	
	if (d>tol) return false;
	return true;
};