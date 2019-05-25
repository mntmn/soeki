
#ifndef SOEKI_GFX32
#define SOEKI_GFX32

#include <string.h>
#include <memory.h>
#include "structures.h"
#include <stdio.h>

class gfx_32
{
private:
  uint32_t* work;
  chape* Chapes;
public:
  uint8_t* distort;
  int32_t NW_WIDTH;
  int32_t NW_HEIGHT;
			
  gfx_32(int w,int h);
  void Connect(chape* chp);
  void Line(int x1,int y1,int x2,int y2,uint32_t colour);
  void Grab(int num,int x,int y,int w,int h);
  void Grap(uint16_t* src,int num,int x,int y,int w,int h);
  void Blit(int num,int x,int y);
  void CBlit(int num,int x,int y);
  void CZBlit(int num,int x,int y,int16_t* zbuf,int16_t z,int smx,int smy);
  void Blint(int num,int x,int y,uint8_t offs);
  void ZBlit(int num,int x,int y,int16_t* zbuf,int16_t z,int smx,int smy);
  void ZSBlit(int num,int x,int y,int16_t* zbuf,int16_t z);
  void Plit(uint16_t* dest,int num,int x,int y);
  void Blit16(uint16_t* dest,int num,int x,int y);
  void Blix(int num,int x,int y,int intensity);
  void ShadowBlit(int num,int x,int y);
  void Kopy(uint32_t* src, uint32_t* dest);
  void Use(uint32_t* what);
  void Box(int x,int y,int x1,int y1,uint32_t col,uint32_t col2);
  void Box(int x,int y,int x1,int y1,uint32_t col);
  void Rect(int x,int y,int x1,int y1,uint32_t col);
  void Write(int x,int y,char* text);
  void Coords(int x,int y,int xnum,int ynum);
  void SmoothCopy(uint32_t* base,int xoff,int yoff,uint32_t* dest);
  void Konvert(uint32_t* src,uint16_t* dest);
  void ScrollHoriz(uint32_t* src,uint32_t* dest,int16_t* zsrc,int16_t* zdst);
  void ScrollVert(uint32_t* src,uint32_t* dest,int16_t* zsrc,int16_t* zdst);
  void ScrollDiag(uint32_t* src,uint32_t* dest,int16_t* zsrc,int16_t* zdst);
};

#endif
