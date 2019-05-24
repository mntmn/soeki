
#ifndef SOEKI_GFX32
#define SOEKI_GFX32

	#include <AppKit.h>
	#include <malloc.h>
	#include <memory.h>
	#include <independent/structures.h>
	#include <stdio.h>

	class gfx_32
	{
		private:
			uint32* work;
			chape* Chapes;
		public:
			uint8* distort;
			int32 NW_WIDTH;
			int32 NW_HEIGHT;
			
			gfx_32(int w,int h);
			void Connect(chape* chp);
			void Line(int x1,int y1,int x2,int y2,uint32 colour);
			void Grab(int num,int x,int y,int w,int h);
			void Grap(uint16* src,int num,int x,int y,int w,int h);
			void Blit(int num,int x,int y);
			void CBlit(int num,int x,int y);
			void CZBlit(int num,int x,int y,int16* zbuf,int16 z,int smx,int smy);
			void Blint(int num,int x,int y,uint8 offs);
			void ZBlit(int num,int x,int y,int16* zbuf,int16 z,int smx,int smy);
			void ZSBlit(int num,int x,int y,int16* zbuf,int16 z);
			void Plit(uint16* dest,int num,int x,int y);
			void Blit16(uint16* dest,int num,int x,int y);
			void Blix(int num,int x,int y,int intensity);
			void ShadowBlit(int num,int x,int y);
			void Kopy(uint32* src, uint32* dest);
			void Use(uint32* what);
			void Box(int x,int y,int x1,int y1,uint32 col,uint32 col2);
			void Box(int x,int y,int x1,int y1,uint32 col);
			void Rect(int x,int y,int x1,int y1,uint32 col);
			void Write(int x,int y,char* text);
			void Coords(int x,int y,int xnum,int ynum);
			void SmoothCopy(uint32* base,int xoff,int yoff,uint32* dest);
			void Konvert(uint32* src,uint16* dest);
			void ScrollHoriz(uint32* src,uint32* dest,int16* zsrc,int16* zdst);
			void ScrollVert(uint32* src,uint32* dest,int16* zsrc,int16* zdst);
			void ScrollDiag(uint32* src,uint32* dest,int16* zsrc,int16* zdst);
	};

#endif
