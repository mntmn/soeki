/*
	Atomatrix 32 bit graphics master library
	Developed for Soeki - The Plague
	©1999,2000 L. Hartmann / Atomatrix
*/

	#include "gfx32.h"

	#define BUFFER_WIDTH (640+256)
	#define BUFFER_HEIGHT (480+128)

	gfx_32::gfx_32(int w,int h)
	{
		NW_WIDTH=w;
		NW_HEIGHT=h;
	};
	
	void gfx_32::Connect(chape* chp)
	{
		Chapes=chp;
	};

	void gfx_32::Use(uint32* what)
	{
		work=what;
	};

	void gfx_32::Line(int x1, int y1, int x2, int y2, uint32 colour)
	{
		uint32* dest=work;
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

	void gfx_32::Grab(int num,int x,int y,int w,int h)
	{
		if (Chapes[num].chunk) free(Chapes[num].chunk);
		uint32* chunk=(uint32*)malloc((w+1)*(h+1)*4);
		Chapes[num].chunk=chunk;
		Chapes[num].w=w;
		Chapes[num].h=h;
		Chapes[num].xhandle=0;
		Chapes[num].yhandle=0;
		
		int loop=0;
		
		uint32* peek=work+(y*NW_WIDTH)+x;
	
		int scrmod=(NW_WIDTH-w)-1;

		while (h-->=0)
		{
			for (loop=w; loop>=0; loop--) 
			{
				*(chunk++) = *(peek++);
			};
			peek+=scrmod;
		};
		
		// Und feddich.
	};
	
	void gfx_32::Grap(uint16* src,int num,int x,int y,int w,int h)
	{
		if (!Chapes[num].chunk) Chapes[num].chunk=(uint32*)malloc((w+1)*(h+1)*4);
		Chapes[num].w=w;
		Chapes[num].h=h;
		Chapes[num].xhandle=0;
		Chapes[num].yhandle=0;
		
		uint32* chunk=Chapes[num].chunk;
		
		int loop=0;
		
		uint16* peek=src+(y*NW_WIDTH)+x;
	
		int scrmod=(NW_WIDTH-w)-1;

		while (h-->=0)
		{
			for (loop=w; loop>=0; loop--) 
			{
				*(chunk++) = *(peek++);
			};
			peek+=scrmod;
		};
	};
	
	void gfx_32::Blit(int num,int x,int y)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
		
		if (y<0)
		{
			y=-y;
			//chunk += y * (w-1);
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
		
		if (!w) printf ("gfx_32: x!%d\n",num);
		if (!h) printf ("gfx_32: y!%d\n",num);
		
		if (w<0 || h<0) return;
		
		uint32* poke=work+(y*NW_WIDTH)+x;
		
		//xsmod=xsmod<<2;
		//xemod=xemod<<2;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		/*printf ("scrmod: %d\n",scrmod);
		printf ("x+w   : %d\n",x+w);
		printf ("x+w+s : %d\n",scrmod+x+w);*/
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000) *(poke) = *(chunk);
				poke++;
				chunk++;
			};
			chunk+=xemod;
			poke+=scrmod;
		};
		
		// Und feddich.
	};
	
	void gfx_32::CBlit(int num,int x,int y)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int size=(Chapes[num].w+1)*(Chapes[num].h+1);
	
		uint32* onewchunk=malloc(size*4);
		uint32* newchunk=onewchunk;
		uint32 sz=0;
		while (sz<size)
		{
			uint32 block=(*(chunk)&0xff000000)>>24;
			while (block-->0)
			{
				*(newchunk+sz)=*(chunk)&0xffffff;
				sz++;
			};
			chunk++;
		};
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) {free (onewchunk); return;};
		
		if (y<0)
		{
			y=-y;
			newchunk += (w+1)*y;
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
		
		if (w<0 || h<0) {free (onewchunk); return;};
		
		uint32* poke=work+(y*NW_WIDTH)+x;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		while (h-->=0)
		{
			newchunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(newchunk)!=0xff0000) *(poke) = *(newchunk);
				poke++;
				newchunk++;
			};
			newchunk+=xemod;
			poke+=scrmod;
		};
		
		free (onewchunk);
	};
	
	void gfx_32::CZBlit(int num,int x,int y,int16* zbuf,int16 z,int smx,int smy)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int size=(Chapes[num].w+1)*(Chapes[num].h+1);
	
		uint32* onewchunk=malloc(size*4);
		uint32* newchunk=onewchunk;
		uint32 sz=0;
		while (sz<size)
		{
			uint32 block=(*(chunk)&0xff000000)>>24;
			while (block-->0)
			{
				*(newchunk+sz)=*(chunk)&0xffffff;
				sz++;
			};
			chunk++;
		};
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) {free (onewchunk); return;};
		
		if (y<0)
		{
			y=-y;
			newchunk += (w+1)*y;
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
		
		if (w<0 || h<0) {free (onewchunk); return;};
		
		uint32* poke=work+(y*NW_WIDTH)+x;
		
		int scrmod=(NW_WIDTH-w)-1;
		int zscrmod=(BUFFER_WIDTH-w)-1;
		int16* zmap=zbuf+((y+smy+64)*BUFFER_WIDTH)+x+128+smx;
	
		while (h-->=0)
		{
			newchunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(newchunk)!=0xff0000 && *(zmap)<=z) *(poke) = *(newchunk);
				poke++;
				newchunk++;
				zmap++;
			};
			newchunk+=xemod;
			poke+=scrmod;
			zmap+=zscrmod;
		};
		
		free (onewchunk);
	};
	
	void gfx_32::ZBlit(int num,int x,int y,int16* zbuf,int16 z,int smx,int smy)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
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
		int zscrmod=(BUFFER_WIDTH-w)-1;
		int16* zmap=zbuf+((y+smy+32)*BUFFER_WIDTH)+x+64+smx;
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--)
			{
				if (*(chunk)!=0xff0000 && *(zmap)<=z)
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
				zmap++;
			};
			chunk+=xemod;
			poke+=scrmod;
			zmap+=zscrmod;
		};
	};
	
	void gfx_32::ZSBlit(int num,int x,int y,int16* zbuf,int16 z)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
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
		int16* zmap=zbuf+(y*NW_WIDTH)+x;
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--)
			{
				if (*(chunk)!=0xff0000 && *(zmap)<=z)
				{
					uint32 pix=*(poke);
					int16 r=((pix & 0xff0000)>>16)-10;
					int16 g=((pix & 0xff00)>>8)-10;
					int16 b=(pix & 0xff)-10;
					if (r<0) r=0;
					if (g<0) g=0;
					if (b<0) b=0;
					*(poke)=r<<16|g<<8|b;
				};
				poke++;
				chunk++;
				zmap++;
			};
			chunk+=xemod;
			poke+=scrmod;
			zmap+=scrmod;
		};
	};
	
	void gfx_32::ShadowBlit(int num,int x,int y)
	{
	
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
		
		if (y<0)
		{
			y=-y;
			//chunk += y * (w-1);
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
		
		//xsmod=xsmod<<2;
		//xemod=xemod<<2;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		/*printf ("scrmod: %d\n",scrmod);
		printf ("x+w   : %d\n",x+w);
		printf ("x+w+s : %d\n",scrmod+x+w);*/
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000)
				{
					int r=(*(poke) & 0x00ff0000) >> 16;
					int g=(*(poke) & 0x0000ff00) >> 8;
					int b=(*(poke) & 0x000000ff);

					r=r-20;
					g=g-20;
					b=b-20;
					
					if (r<0) r=0;
					if (g<0) g=0;
					if (b<0) b=0;
					
					*(poke)=r<<16|g<<8|b;
				};
				chunk++;
				poke++;
			};
			chunk+=xemod;
			poke+=scrmod;
		};
		
		// Und feddich.
	};
	
	void gfx_32::Blint(int num,int x,int y,uint8 offs)
	{
		uint32* chunk=Chapes[num].chunk;
		if (!chunk) return;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		int xsmod=0,xemod=0,loop=0;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
		
		if (y<0)
		{
			y=-y;
			//chunk += y * (w-1);
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
		
		//xsmod=xsmod<<2;
		//xemod=xemod<<2;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		/*printf ("scrmod: %d\n",scrmod);
		printf ("x+w   : %d\n",x+w);
		printf ("x+w+s : %d\n",scrmod+x+w);*/
	
		int dsy=offs;
		int dsx=0;
	
		while (h-->=0)
		{
			chunk+=xsmod;
			int ls=h&1;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000)
				{
					int m=*(distort+dsx+dsy*256)/2;

					int r=(*(chunk) & 0x00ff0000) >> 16;
					int g=(*(chunk) & 0x0000ff00) >> 8;
					int b=(*(chunk) & 0x000000ff);

					r=r-m-(offs&0xf)*4-ls*100;
					g=g-m-ls*50;
					b=b-m-(offs&0xf)*4-ls*80;

					if (r<0) r=0;
					if (g<0) g=0;
					if (b<0) b=0;

					*(poke)=r<<16|g<<8|b;
				}
				dsx++;
				if (dsx>255) dsx=0;
				chunk++;
				poke++;
			};
			chunk+=xemod;
			poke+=scrmod;
			dsy++;
			if (dsy>255) dsy=0;
		};
		
		// Und feddich.
	};	
	
	void gfx_32::Plit(uint16* dest,int num,int x,int y)
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
			h -= (h+y)-NW_HEIGHT;
		};
		if ((x+w)>=NW_WIDTH)
		{
			xemod = (w+x)-NW_WIDTH;
			w -= xemod;
		};
		
		if (w<1 || h<1) return;
		
		uint16* poke=dest+(y*NW_WIDTH)+x;
		int scrmod=(NW_WIDTH-w)-1;

		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000) *(poke) = ((*(chunk) & 0xf8)>>3) | ((*(chunk) & 0xfc00)>>5) | ((*(chunk) & 0xf80000)>>8); 
				poke++;
				chunk++;
			};
			chunk+=xemod;
			poke+=scrmod;
		};
	};
	
	void gfx_32::Blit16(uint16* dest,int num,int x,int y)
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
			h -= (h+y)-NW_HEIGHT;
		};
		if ((x+w)>=NW_WIDTH)
		{
			xemod = (w+x)-NW_WIDTH;
			w -= xemod;
		};
		
		if (w<1 || h<1) return;
		
		uint16* poke=dest+(y*NW_WIDTH)+x;
		int scrmod=(NW_WIDTH-w)-1;

		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--)
			{
				if (*(chunk)!=0xff0000) *(poke) = *(chunk);
				poke++;
				chunk++;
			};
			chunk+=xemod;
			poke+=scrmod;
		};
	};
	
	void gfx_32::Blix(int num,int x,int y,int intensity)
	{
	
		uint32* chunk=Chapes[num].chunk;
		x-=Chapes[num].xhandle;
		y-=Chapes[num].yhandle;
		int w=Chapes[num].w;
		int h=Chapes[num].h;
		
		if (x>=NW_WIDTH || y>=NW_HEIGHT) return;
		
		int xsmod=0,xemod=0,loop=0;
		
		if (y<0) {chunk += (-y * w); h += y; y=0;};
		if (x<0) {w += x; xsmod = -x; x=0;};
		
		if ((y+h)>=NW_HEIGHT)
		{
			h -= (h+y)-NW_HEIGHT;
		};
		if ((x+w)>=NW_WIDTH)
		{
			xemod = (w+x)-NW_WIDTH;
			w -= xemod;
		};
		
		if (w<1 || h<1) return;
		
		uint32* poke=work+(y*NW_WIDTH)+x;
		
		//xsmod=xsmod<<2;
		//xemod=xemod<<2;
	
		int scrmod=(NW_WIDTH-w)-1;
	
		/*printf ("scrmod: %d\n",scrmod);
		printf ("x+w   : %d\n",x+w);
		printf ("x+w+s : %d\n",scrmod+x+w);*/
	
		int intenzity=128-intensity;
	
		while (h-->=0)
		{
			chunk+=xsmod;
			for (loop=w; loop>=0; loop--) 
			{
				if (*(chunk)!=0xff0000) 
				{
					int r=((*(poke) & 0x00ff0000)*intenzity) >> (16+7);
					int g=((*(poke) & 0x0000ff00)*intenzity) >> (8+7);
					int b=((*(poke) & 0x000000ff)*intenzity) >> 7;
					
					int rw=((*(chunk) & 0x00ff0000)*intensity) >> (16+7);
					int gw=((*(chunk) & 0x0000ff00)*intensity) >> (8+7);
					int bw=((*(chunk) & 0x000000ff)*intensity) >> 7;
					
					r=(r+rw);
					g=(g+gw);
					b=(b+bw);
					
					*(poke)=r<<16|g<<8|b;
				};
				poke++;
				chunk++;
			};
			chunk+=xemod;
			poke+=scrmod;
		};
		
		// Und feddich.
	};
	
	void gfx_32::Rect(int x,int y,int x1,int y1,uint32 col)
	{
		if (x>x1)
		{
			int temp=x;
			x=x1;
			x1=temp;
		};
		if (y>y1)
		{
			int temp=y;
			y=y1;
			y1=temp;
		};
		
		int d=y1-y;
		loop2:
			uint32* poke=work+(y+d)*NW_WIDTH+x;
			int c=x1-x;
		loop1: *(poke++)=col;
			if (c--) goto loop1;
		if (d--) goto loop2;
	};
	
	void gfx_32::Box(int x,int y,int x1,int y1,uint32 col)
	{
		if (x>x1)
		{
			int temp=x;
			x=x1;
			x1=temp;
		};
		if (y>y1)
		{
			int temp=y;
			y=y1;
			y1=temp;
		};
		
		int rc=(col & 0x00ff0000) >> 16;
		int gc=(col & 0x0000ff00) >> 8;
		int bc=(col & 0x000000ff);
		
		int d=y1-y;
		loop2:
			uint32* poke=work+(y+d)*NW_WIDTH+x;
			int c=x1-x;
		loop1:	int r=(*(poke) & 0x00ff0000) >> 16;
				int g=(*(poke) & 0x0000ff00) >> 8;
				int b=(*(poke) & 0x000000ff);
				
				r=(r+rc)>>1;
				g=(g+gc)>>1;
				b=(b+bc)>>1;
				
				*(poke)=r<<16|g<<8|b;
				poke++;
			if (c--) goto loop1;
			if (rc) rc--;
			if (gc) gc--;
			if (bc) bc--;
		if (d--) goto loop2;
	};
	
	void gfx_32::Box(int x,int y,int x1,int y1,uint32 col,uint32 col2)
	{
		if (x>x1)
		{
			int temp=x;
			x=x1;
			x1=temp;
		};
		if (y>y1)
		{
			int temp=y;
			y=y1;
			y1=temp;
		};
		
		int rc=(col & 0x00ff0000) >> 16;
		int gc=(col & 0x0000ff00) >> 8;
		int bc=(col & 0x000000ff);
		
		int rc2=(col2 & 0x00ff0000) >> 16;
		int gc2=(col2 & 0x0000ff00) >> 8;
		int bc2=(col2 & 0x000000ff);
		
		float rstep=0,gstep=0,bstep=0;
		
		if (y1!=y)
		{
			rstep=(rc2-rc)/(y1-y);
			gstep=(gc2-gc)/(y1-y);
			bstep=(bc2-bc)/(y1-y);
		};
		
		for (int d=y; d<=y1; d++)
		{
			uint32* poke=work+d*NW_WIDTH+x;
			
			for (int c=x; c<=x1; c++)
			{
				int r=(*(poke) & 0x00ff0000) >> 16;
				int g=(*(poke) & 0x0000ff00) >> 8;
				int b=(*(poke) & 0x000000ff);
				
				r=(r+rc)>>1;
				g=(g+gc)>>1;
				b=(b+bc)>>1;
				
				*(poke)=r<<16|g<<8|b;
				poke++;
			};
			rc=int ((float)rc+rstep);
			gc=int ((float)gc+gstep);
			bc=int ((float)bc+bstep);
		};
	};
	
	void gfx_32::Write(int x,int y,char* text)
	{
		char sub='a';
		
		for (unsigned int i=0; i<strlen(text); i++)
		{
			int chp=*(text+i)-sub;
			Blix(chp,x,y,128);
			x+=Chapes[chp].w+1;
		};
	};
	
	void gfx_32::Coords(int x,int y,int xnum,int ynum)
	{
		if (xnum<10)
		{
			Blit(31+xnum,x,y);
			Blit(30,x+6,y);
		}
		else
		{
			Blit(31+xnum-10,x,y);
			Blit(31+xnum-(xnum-10),x+6,y);
			Blit(30,x+13,y);
		};
		if (ynum<10)
		{
			Blit(31+ynum,x+13,y);
		}
		else
		{
			Blit(31+ynum-10,x+16,y);
			Blit(31+ynum-(ynum-10),x+22,y);
		};
	};
	
	void gfx_32::Kopy(uint32* src,uint32* dest)
	{
		for (int lot=NW_WIDTH*NW_HEIGHT; lot>0; lot--) *(dest++)=*(src++);
	};
	
	#define WIDTH (BUFFER_WIDTH-64)
	
	void gfx_32::ScrollHoriz(uint32* src,uint32* dest,int16* zsrc,int16* zdst)
	{
		/*uint32* die=0x00000000;
		*(die)=1;*/
		if (dest<src)
		{
			for (uint32 lot=BUFFER_HEIGHT; lot>0; lot--)
			{
				/*for (uint32 xlot=WIDTH; xlot>0; xlot--)	{*(dest++)=*(src++);};
				for (uint32 xlot=WIDTH; xlot>0; xlot--) {*(zdst++)=*(zsrc++);};*/
				memcpy(dest,src,WIDTH*4);
				memcpy(zdst,zsrc,WIDTH*2);
				src+=WIDTH+64;
				dest+=WIDTH+64;
				zsrc+=WIDTH+64;
				zdst+=WIDTH;
				for (uint32 xlot=64; xlot>0; xlot--) {*(zdst++)=-999;};
			};
		}
		else
		{
			src+=BUFFER_WIDTH*BUFFER_HEIGHT-1;
			dest+=BUFFER_WIDTH*BUFFER_HEIGHT-1;
			zsrc+=BUFFER_WIDTH*BUFFER_HEIGHT-1;
			zdst+=BUFFER_WIDTH*BUFFER_HEIGHT-1;
			for (uint32 lot=BUFFER_HEIGHT; lot>0; lot--)
			{
				src-=64;
				zsrc-=64;
				dest-=64;
				
				for (uint32 xlot=64; xlot>0; xlot--) {*(zdst--)=-999;};
				for (uint32 xlot=WIDTH; xlot>0; xlot--) {*(dest--)=*(src--); *(zdst--)=*(zsrc--);};

				//xlot=WIDTH;
				//while (xlot) {*(dest--)=*(src--); *(zdst--)=*(zsrc--); xlot--;};

			};
		};
	};
	
	void gfx_32::ScrollVert(uint32* src,uint32* dest,int16* zsrc,int16* zdst)
	{
		if (dest<src)
		{
			for (uint32 lot=BUFFER_HEIGHT-32; lot>0; lot--)
			{
				for (uint32 xlot=BUFFER_WIDTH; xlot>0; xlot--) {*(dest++)=*(src++); *(zdst++)=*(zsrc++)-2;};
			};
			for (uint32 lot=BUFFER_WIDTH*32; lot>0; lot--) *(zdst++)=-999;
		}
		else
		{
			src+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			dest+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			zsrc+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			zdst+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			for (uint32 lot=BUFFER_HEIGHT-32; lot>0; lot--)
			{
				for (uint32 xlot=BUFFER_WIDTH; xlot>0; xlot--) {*(dest--)=*(src--); *(zdst--)=*(zsrc--)+2;};
			};
			for (uint32 lot=BUFFER_WIDTH*32; lot>0; lot--) *(zdst--)=-999;
		};
	};
	
	void gfx_32::ScrollDiag(uint32* src,uint32* dest,int16* zsrc,int16* zdst)
	{
		//uint32 width=BUFFER_WIDTH-64;
		uint32 xlot=0;
		uint32 lot=0;
		if (dest<src)
		{
			for (lot=BUFFER_HEIGHT-32; lot>0; lot--)
			{
				for (xlot=BUFFER_WIDTH-64; xlot>0; xlot--) {*(dest++)=*(src++); *(zdst++)=*(zsrc++)-2;};
				src+=64;
				dest+=64;
				zsrc+=64;
				for (xlot=64; xlot>0; xlot--) *(zdst++)=-999;
			};
			for (lot=32*BUFFER_WIDTH; lot>0; lot--) *(zdst++)=-999;
		}
		else
		{
			src+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			dest+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			zsrc+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			zdst+=BUFFER_WIDTH*(BUFFER_HEIGHT-32)-1;
			
			for (lot=BUFFER_HEIGHT-32; lot>0; lot--)
			{
				src-=64;
				dest-=64;
				zsrc-=64;
				for (xlot=64; xlot>0; xlot--) *(zdst--)=-999;
				for (xlot=BUFFER_WIDTH-64; xlot>0; xlot--) {*(dest--)=*(src--); *(zdst--)=*(zsrc--)+2;};
			};
			for (lot=BUFFER_WIDTH*32+64; lot>0; lot--) *(zdst--)=-999;
		};
	};
	
	void gfx_32::SmoothCopy(uint32* base,int xoff,int yoff,uint32* dest)
	{
		base+=yoff*BUFFER_WIDTH;
		base+=xoff;
		for (int loty=480; loty>0; loty--)
		{
			for (int lotx=640; lotx>0; lotx--)
			{
				*(dest++)=*(base++);
			};
			base+=256;
		};
	};
	
	void gfx_32::Konvert(uint32* src,uint16* dest)
	{
		// 15.10.99 20:12 VICTORY!
		// 00000000rrrrrrrrggggggggbbbbbbbb  32 bit BGR
		// rrrrrggggggbbbbb                  16 bit BGR

		uint32 lot=(640*479);
		uint32 wuerg;
		lot--;
	quickloop: wuerg=*(src++);
	 	*(dest++)=((wuerg & 0xf8)>>3) | ((wuerg & 0xfc00)>>5) | ((wuerg & 0xf80000)>>8); 
		lot--;
		if (lot) goto quickloop;
	};