
// Written by the mighty Alpha of Vortex
// Fix, Cleanup and Coffee consume started on 22.8.99 at 4:00 in the night by L.Hartmann / Atomatrix
// First working version done on 22.8.99 at 14:28. I'm a hero =) [Not really]
// Slept 3 hours + 3 hours pause.
// Copyright 1999 Atomatrix Entertainment
// www.atomatrix.com

// * Note: Please don't ask me about internal math details. That's why I can't optimize this
// myself...
// Sorry for bad english in the translated comments

// * Target:
// Triangle() ought to achieve at least 10 fps with 200-400 triangles on a 166 Mhz machine.

// * Your contact: atomatrix@gmx.de (Lukas Hartmann)

#include "magic.h"

#define SCREEN_WIDTH (640+256)
#define SCREEN_HEIGHT (480+128)

void AlphasMagic::Clear()
{
	for (int i=0;i<SCREEN_WIDTH*SCREEN_HEIGHT;i++) *(array+i)=0x000000;
};

AlphasMagic::AlphasMagic()
{	
};

//-----------------------------------------------
// - A multiplication table is needed for the following GouTexTri-Routine.
// - The original color (R-, G- or B-value) for brightness values 0 to 127 
//   is calculated ranging from black to full color.
// - Values 128-255 are brighter shades of the color, i.e. up to total white.
// - This makes complete 24-bit Gouraud with 256 shades of brightness possible.

void AlphasMagic::MakeTable()
{
		// x*2 is the original value of the color, y ranges from 0 to 255
		// and shifting it by 8 makes it range 0 to 1.0
        for(int x=0;x<128;x++)  //Brightness is converted to 0 to 254
          for(int y=0;y<256;y++) //Color
            multab2[x][y]=((x*2)*y)>>8;

        for(int x=0;x<128;x++) //No brightness conversion to 0 to 254 anymore, 
        					   //we just divide dif into 127 parts

          for(int y=0;y<256;y++)
          {
            int32 dif=((long)256-(int32)y)/(long)127;
            int erg=(int)((int32)y+dif*(int32)x);
            if(erg>255)erg=255;
            if(erg<0)erg=0;
            multab2[128+x][y]=erg;
          }
          
          // Init ZBuffer
          for (int x=0; x<640*480; x++) Zmap[x]=-999;
};

// Function for a single line of the triangle

void AlphasMagic::TriTexGouLine(int16 z,int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2, int32 g1, int32 g2)
{
		// Round to ensure that problems caused by rounding errors don't occur (jumping lines)
        x2&=0xFFFF0000;
        x1&=0xFFFF0000;

		// Sort values to make drawing from left to right possible
        if(x2<x1)
        {
            int32 temp=x2;x2=x1;x1=temp;
            temp=tx2;tx2=tx1;tx1=temp;
            temp=ty2;ty2=ty1;ty1=temp;
            temp=g2;g2=g1;g1=temp;
        }

        int32 xdelta=(x2-x1)>>16;
        if(xdelta<1) return;

        int xd=xdelta;

		//Calculate start Tex-X and Tex-X-Increment
        int txi=tx1; //fixed point
        int32 txd=(tx2-tx1)/xdelta;
        int txdi=txd; //same here

        //Same for Tex-Y and Tex-Y-Increment
        int tyi=ty1; //fixed point
        int32 tyd=(ty2-ty1)/xdelta;
        int tydi=tyd; //same here

        //Gouraud
        int gi=g1; //fixed point
        int32 gd=(g2-g1)/xdelta;
        int gdi=gd; //same here


		x1>>=16;
		x2>>=16;
//Clipping begin
//If line isn't inside screen -> outta here
        if(x1>((SCREEN_WIDTH-1)<<16)||(x2<0))return;
/*If the line is clipped at the left screen border (where we start), the left out
gouraud and texture steps have to be calculated; x is set to 0 */
        if(x1<0)
        {
            int xm=-x1;
            gi+=gdi*xm;
            x1=0;
        }
/* x is simply clipped at the right border. That's where the loop is going to end
then */
        if(x2>(SCREEN_WIDTH-1))x2=(SCREEN_WIDTH-1);
//End of clipping and calculation of screen start address
        uint32* arrayptr=array+(y*SCREEN_WIDTH)+x1;
		int16* ztab=Zmap+y*SCREEN_WIDTH+x1;

//Recalculate X-Delta because of clipping
        xdelta=(x2-x1);
        if(xdelta<=0)return;
        xd=(int)(xdelta);

        int r;
        int g;
        int b;
        int pix;
		unsigned char* mtab;


        for(int x=0;x<=xd;x++)
        {
        	if (*(ztab)<=z)
	        {
			//Fetch a pixel from the texture (256*256)
	          pix=array_tex1[(txi>>16)+((tyi>>8)&0xff00)];
	        //Point to the right 256-values range of multiplication table
	          mtab=multab2[gi>>16];
	          r=*(mtab+((pix&0x00ff0000)>>16));
	          g=*(mtab+((pix&0x0000ff00)>>8));
	          b=*(mtab+((pix&0x000000ff)));
			//Construct and write 24-bit value
	          *(arrayptr)=(r<<16)|(g<<8)|b;
	          *(ztab)=z;
	        };
	        //Increase Texture- and Gouraud-counter
	        txi+=txdi;
	        tyi+=tydi;
	        gi+=gdi;
	        arrayptr++;
        	ztab++;
        }
    }

void AlphasMagic::TriTexGouLine2(int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2, int32 g1, int32 g2)
{
		// WOW! Transparency ;)
		// Added by minute.man on 12/02/99


		// Round to ensure that problems caused by rounding errors don't occur (jumping lines)
        x2&=0xFFFF0000;
        x1&=0xFFFF0000;

		// Sort values to make drawing from left to right possible
        if(x2<x1)
        {
            int32 temp=x2;x2=x1;x1=temp;
            temp=tx2;tx2=tx1;tx1=temp;
            temp=ty2;ty2=ty1;ty1=temp;
            temp=g2;g2=g1;g1=temp;
        }

        int32 xdelta=(x2-x1)>>16;
        if(xdelta<1) return;

        int xd=xdelta;

		//Calculate start Tex-X and Tex-X-Increment
        int txi=tx1; //fixed point
        int32 txd=(tx2-tx1)/xdelta;
        int txdi=txd; //same here

        //Same for Tex-Y and Tex-Y-Increment
        int tyi=ty1; //fixed point
        int32 tyd=(ty2-ty1)/xdelta;
        int tydi=tyd; //same here

        //Gouraud
        int gi=g1; //fixed point
        int32 gd=(g2-g1)/xdelta;
        int gdi=gd; //same here


		x1>>=16;
		x2>>=16;
//Clipping begin
//If line isn't inside screen -> outta here
        if(x1>((SCREEN_WIDTH-1)<<16)||(x2<0))return;
/*If the line is clipped at the left screen border (where we start), the left out
gouraud and texture steps have to be calculated; x is set to 0 */
        if(x1<0)
        {
            int xm=-x1;
            gi+=gdi*xm;
            x1=0;
        }
/* x is simply clipped at the right border. That's where the loop is going to end
then */
        if(x2>(SCREEN_WIDTH-1))x2=(SCREEN_WIDTH-1);
//End of clipping and calculation of screen start address
        uint32* arrayptr=array+(y*SCREEN_WIDTH)+x1;

//Recalculate X-Delta because of clipping
        xdelta=(x2-x1);
        if(xdelta<=0)return;
        xd=(int)(xdelta);

        int r,rs;
        int g,gs;
        int b,bs;
        int pix,pix2;
		unsigned char* mtab;

        for(int x=0;x<=xd;x++)
        {
		//Fetch a pixel from the texture (256*256)
          pix=array_tex1[(txi>>16)+((tyi>>8)&0xff00)];
          pix2=*(arrayptr);
        //Point to the right 256-values range of multiplication table
          mtab=multab2[gi>>16];
          r=*(mtab+((pix&0x00ff0000)>>16));
          g=*(mtab+((pix&0x0000ff00)>>8));
          b=*(mtab+((pix&0x000000ff)));
          
          rs=(pix2&0x00ff0000)>>16;
          gs=(pix2&0x0000ff00)>>8;
          bs=pix2&0x000000ff;
          
          r=(r+rs);
          if (r>255) r=255;
          g=(g+gs);
          if (g>255) g=255;
          b=(b+bs);
          if (b>255) b=255;
        //Construct and write 24-bit value
          *(arrayptr++)=(r<<16)|(g<<8)|b;
        
        //Increase Texture- and Gouraud-counter
          txi+=txdi;
          tyi+=tydi;
          gi+=gdi;
        }
    }

void AlphasMagic::TriTexLine(int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2 )
{
		// Round to ensure that problems caused by rounding errors don't occur (jumping lines)
        x2&=0xFFFF0000;
        x1&=0xFFFF0000;

		// Sort values to make drawing from left to right possible
        if(x2<x1)
        {
            int32 temp=x2;x2=x1;x1=temp;
            temp=tx2;tx2=tx1;tx1=temp;
            temp=ty2;ty2=ty1;ty1=temp;
        }

        int32 xdelta=(x2-x1)>>16;
        if(xdelta<1) return;

        int xd=xdelta;

		//Calculate start Tex-X and Tex-X-Increment
        int txi=tx1; //fixed point
        int32 txd=(tx2-tx1)/xdelta;
        int txdi=txd; //same here

        //Same for Tex-Y and Tex-Y-Increment
        int tyi=ty1; //fixed point
        int32 tyd=(ty2-ty1)/xdelta;
        int tydi=tyd; //same here


//Clipping begin
//If line isn't inside screen -> outta here
		x1>>=16;
		x2>>=16;

        if(x1>((SCREEN_WIDTH-1))||(x2<0))return;
/*If the line is clipped at the left screen border (where we start), the left out
gouraud and texture steps have to be calculated; x is set to 0 */
        if(x1<0)
        {
            //int xm=-x1;
            x1=0;
        }
/* x is simply clipped at the right border. That's where the loop is going to end
then */
        if(x2>(SCREEN_WIDTH-1))x2=(SCREEN_WIDTH-1);
//End of clipping and calculation of screen start address
        int arrayptr=(y*SCREEN_WIDTH)+(x1);

//Recalculate X-Delta because of clipping
        xdelta=(x2-x1);
        if(xdelta<=0)return;
        xd=(int)(xdelta);

        for(int x=0;x<=xd;x++)
        {
		//Fetch a pixel from the texture (256*256)
          *(array+(arrayptr++))=array_tex1[(txi>>16)+((tyi>>8)&0xff00)];;
        
        //Increase Texture- and Gouraud-counter
          txi+=txdi;
          tyi+=tydi;
        }
    }


void AlphasMagic::ClearLine(int32 z,int32 x1, int32 x2, int32 y)
{
      x2&=0xFFFF0000;
      x1&=0xFFFF0000;

      if(x2<x1)
      {
          int32 temp=x2;x2=x1;x1=temp;
      }

      int32 xdelta=(x2-x1)>>16;
      if(xdelta<1) return;

      int xd=xdelta;

	x1>>=16;
	x2>>=16;

      if(x1>((SCREEN_WIDTH-1))||(x2<0))return;
      if(x1<0)
      {
          x1=0;
      }
      if(x2>(SCREEN_WIDTH-1))x2=(SCREEN_WIDTH-1);
	  int16* ztab=Zmap+y*SCREEN_WIDTH+x1;

      xdelta=(x2-x1);
      if(xdelta<=0)return;
      xd=(int)(xdelta);

	for(int x=0;x<=xd;x++)
	{
		if (*(ztab)<=z) *(ztab)=-999;
		ztab++;
	};
};


// Here comes the action

/*
 Coordinates are passed on in the 3 arrays (int32)
 [0]=x
 [1]=y
 [2]=z
 [3]=texture_x 0-256
 [4]=texture_y 0-256
 [5]=gouraud-Wert (brightness) 0-256
*/

void AlphasMagic::Triangle(TriangleDef *d,int16 z)
{
	int32 *dataa, *datab, *datac;

    int32 xs1,xs2,xs3,txs1,txs2,txs3,tys1,tys2,tys3,gs1,gs2,gs3;
    int32* tempdata;


	dataa= d->a;
	datab= d->b;
	datac= d->c;

  // Very simple sorting of the three y coordinates
  
  //if (dataa[1]>datac[1]) return;
  
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}
  if(datab[1]>datac[1]){tempdata=datab;datab=datac;datac=tempdata;}
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}


  // Calculate some deltas 
  int32 xd1=datab[0]-dataa[0];
  int32 xd2=datac[0]-dataa[0];
  int32 xd3=datac[0]-datab[0];
  int32 yd1=datab[1]-dataa[1];
  int32 yd2=datac[1]-dataa[1];
  int32 yd3=datac[1]-datab[1];
  int32 txd1=datab[2]-dataa[2];
  int32 txd2=datac[2]-dataa[2];
  int32 txd3=datac[2]-datab[2];
  int32 tyd1=datab[3]-dataa[3];
  int32 tyd2=datac[3]-dataa[3];
  int32 tyd3=datac[3]-datab[3];
  int32 gd1=datab[4]-dataa[4];
  int32 gd2=datac[4]-dataa[4];
  int32 gd3=datac[4]-datab[4];

  // Calculate steps per line while taking care of division by 0
  if(yd1!=0)
  {xs1=xd1/yd1;txs1=txd1/yd1;tys1=tyd1/yd1;gs1=gd1/yd1;}
  else
  {xs1=xd1;txs1=txd1;tys1=tyd1;gs1=gd1;}
  if(yd2!=0)
  {xs2=xd2/yd2;txs2=txd2/yd2;tys2=tyd2/yd2;gs2=gd2/yd2;}
  else
  {xs2=xd2;txs2=txd2;tys2=tyd2;gs2=gd2;}
  if(yd3!=0)
  {xs3=xd3/yd3;txs3=txd3/yd3;tys3=tyd3/yd3;gs3=gd3/yd3;}
  else
  {xs3=xd3;txs3=txd3;tys3=tyd3;gs3=gd3;}

  /*
     Variable meanings:
     
     xs? xstep=delta x
     txs? delta tx
     tys? delta ty
     xd? xdelta
     yd? dunno
     txd?  "
     tyd?  "
     xw? current x-value used in loop
     txw? for tx
     tyw? for ty

  */

  /*
   Start values for the first part (up to y of point 2)
   xw1 and xw2 are x-values for the current line. The triangle is drawn from
   top to bottom line after line...
   txw, tyw and gw are values for texture and brightness
   always for start- and ending-point of the current line
   A line is also called "Span".
  */

  int32 xw1=dataa[0]; //pax
  int32 xw2=dataa[0];
  int32 txw1=dataa[2]; //tax
  int32 txw2=dataa[2];
  int32 tyw1=dataa[3]; //tay
  int32 tyw2=dataa[3];
  int32 gw1=dataa[4]; //gou
  int32 gw2=dataa[4];
  if(yd1)
  for(int sz=dataa[1];sz<=datab[1];sz++)
  {
    // draw if y is inside the screen (clipping)   
    if(sz>=SCREEN_HEIGHT)break;
	if(sz>=0)
	{
		if (z<500)
		{
			TriTexGouLine(z,xw1,xw2,(int32)sz,txw1,txw2,tyw1,tyw2,gw1,gw2);
		}
		else
		{
			ClearLine(z-600,xw1,xw2,(int32)sz);
		};
	}
	xw1+=xs1;
	xw2+=xs2;
	txw1+=txs1;
	txw2+=txs2;
	tyw1+=tys1;
	tyw2+=tys2;
	gw1+=gs1;
	gw2+=gs2;
  }
  /*
   New start values for the second part of the triangle
  */
  xw1=datab[0]+xs3;
  txw1=datab[2]+txs3;
  tyw1=datab[3]+tys3;
  gw1=datab[4]+gs3;
  if(yd3) //If Span-Height 1 or higher
  for(int sz=datab[1]+1;sz<datac[1];sz++)
  {
  	if(sz>=SCREEN_HEIGHT)break;
    if(sz>=0)
    {
    	if (z<500)
		{
			TriTexGouLine(z,xw1,xw2,(int32)sz,txw1,txw2,tyw1,tyw2,gw1,gw2);
		}
		else
		{
			ClearLine(z-600,xw1,xw2,(int32)sz);
		};
    }
	xw1+=xs3;
	xw2+=xs2;
	txw1+=txs3;
	txw2+=txs2;
	tyw1+=tys3;
	tyw2+=tys2;
	gw1+=gs3;
	gw2+=gs2;
  }
};

void AlphasMagic::Transangle(TriangleDef *d )
{
	int32 *dataa, *datab, *datac;

    int32 xs1,xs2,xs3,txs1,txs2,txs3,tys1,tys2,tys3,gs1,gs2,gs3;
    int32* tempdata;


	dataa= d->a;
	datab= d->b;
	datac= d->c;

  // Very simple sorting of the three y coordinates
  
  //if (dataa[1]>datac[1]) return;
  
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}
  if(datab[1]>datac[1]){tempdata=datab;datab=datac;datac=tempdata;}
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}


  // Calculate some deltas 
  int32 xd1=datab[0]-dataa[0];
  int32 xd2=datac[0]-dataa[0];
  int32 xd3=datac[0]-datab[0];
  int32 yd1=datab[1]-dataa[1];
  int32 yd2=datac[1]-dataa[1];
  int32 yd3=datac[1]-datab[1];
  int32 txd1=datab[2]-dataa[2];
  int32 txd2=datac[2]-dataa[2];
  int32 txd3=datac[2]-datab[2];
  int32 tyd1=datab[3]-dataa[3];
  int32 tyd2=datac[3]-dataa[3];
  int32 tyd3=datac[3]-datab[3];
  int32 gd1=datab[4]-dataa[4];
  int32 gd2=datac[4]-dataa[4];
  int32 gd3=datac[4]-datab[4];

  // Calculate steps per line while taking care of division by 0
  if(yd1!=0)
  {xs1=xd1/yd1;txs1=txd1/yd1;tys1=tyd1/yd1;gs1=gd1/yd1;}
  else
  {xs1=xd1;txs1=txd1;tys1=tyd1;gs1=gd1;}
  if(yd2!=0)
  {xs2=xd2/yd2;txs2=txd2/yd2;tys2=tyd2/yd2;gs2=gd2/yd2;}
  else
  {xs2=xd2;txs2=txd2;tys2=tyd2;gs2=gd2;}
  if(yd3!=0)
  {xs3=xd3/yd3;txs3=txd3/yd3;tys3=tyd3/yd3;gs3=gd3/yd3;}
  else
  {xs3=xd3;txs3=txd3;tys3=tyd3;gs3=gd3;}

  /*
     Variable meanings:
     
     xs? xstep=delta x
     txs? delta tx
     tys? delta ty
     xd? xdelta
     yd? dunno
     txd?  "
     tyd?  "
     xw? current x-value used in loop
     txw? for tx
     tyw? for ty

  */

  /*
   Start values for the first part (up to y of point 2)
   xw1 and xw2 are x-values for the current line. The triangle is drawn from
   top to bottom line after line...
   txw, tyw and gw are values for texture and brightness
   always for start- and ending-point of the current line
   A line is also called "Span".
  */

  int32 xw1=dataa[0]; //pax
  int32 xw2=dataa[0];
  int32 txw1=dataa[2]; //tax
  int32 txw2=dataa[2];
  int32 tyw1=dataa[3]; //tay
  int32 tyw2=dataa[3];
  int32 gw1=dataa[4]; //gou
  int32 gw2=dataa[4];
  if(yd1)
  for(int sz=dataa[1];sz<=datab[1];sz++)
  {
    // draw if y is inside the screen (clipping)   
    if(sz>=SCREEN_HEIGHT)break;
	if(sz>=0)
	{
		TriTexGouLine2(xw1,xw2,(int32)sz,txw1,txw2,tyw1,tyw2,gw1,gw2);
	}
	xw1+=xs1;
	xw2+=xs2;
	txw1+=txs1;
	txw2+=txs2;
	tyw1+=tys1;
	tyw2+=tys2;
	gw1+=gs1;
	gw2+=gs2;
  }
  /*
   New start values for the second part of the triangle
  */
  xw1=datab[0]+xs3;
  txw1=datab[2]+txs3;
  tyw1=datab[3]+tys3;
  gw1=datab[4]+gs3;
  if(yd3) //If Span-Height 1 or higher
  for(int sz=datab[1]+1;sz<datac[1];sz++)
  {
  	if(sz>=SCREEN_HEIGHT)break;
    if(sz>=0)
    {
    	TriTexGouLine2(xw1,xw2,sz,txw1,txw2,tyw1,tyw2,gw1,gw2);
    }
	xw1+=xs3;
	xw2+=xs2;
	txw1+=txs3;
	txw2+=txs2;
	tyw1+=tys3;
	tyw2+=tys2;
	gw1+=gs3;
	gw2+=gs2;
  }
};

void AlphasMagic::FlatTriangle( TriangleDef *d )
{
	int32 *dataa, *datab, *datac;

    int32 xs1,xs2,xs3,txs1,txs2,txs3,tys1,tys2,tys3;
    int32* tempdata;


	dataa= d->a;
	datab= d->b;
	datac= d->c;

  // Very simple sorting of the three y coordinates
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}
  if(datab[1]>datac[1]){tempdata=datab;datab=datac;datac=tempdata;}
  if(dataa[1]>datab[1]){tempdata=dataa;dataa=datab;datab=tempdata;}




  // Calculate some deltas 
  int32 xd1=datab[0]-dataa[0];
  int32 xd2=datac[0]-dataa[0];
  int32 xd3=datac[0]-datab[0];
  int32 yd1=datab[1]-dataa[1];
  int32 yd2=datac[1]-dataa[1];
  int32 yd3=datac[1]-datab[1];
  int32 txd1=datab[2]-dataa[2];
  int32 txd2=datac[2]-dataa[2];
  int32 txd3=datac[2]-datab[2];
  int32 tyd1=datab[3]-dataa[3];
  int32 tyd2=datac[3]-dataa[3];
  int32 tyd3=datac[3]-datab[3];

  // Calculate steps per line while taking care of division by 0
  if(yd1!=0)
  {xs1=xd1/yd1;txs1=txd1/yd1;tys1=tyd1/yd1;}
  else
  {xs1=xd1;txs1=txd1;tys1=tyd1;}
  if(yd2!=0)
  {xs2=xd2/yd2;txs2=txd2/yd2;tys2=tyd2/yd2;}
  else
  {xs2=xd2;txs2=txd2;tys2=tyd2;}
  if(yd3!=0)
  {xs3=xd3/yd3;txs3=txd3/yd3;tys3=tyd3/yd3;}
  else
  {xs3=xd3;txs3=txd3;tys3=tyd3;}

  /*
     Variable meanings:
     
     xs? xstep=delta x
     txs? delta tx
     tys? delta ty
     xd? xdelta
     yd? dunno
     txd?  "
     tyd?  "
     xw? current x-value used in loop
     txw? for tx
     tyw? for ty

  */

  /*
   Start values for the first part (up to y of point 2)
   xw1 and xw2 are x-values for the current line. The triangle is drawn from
   top to bottom line after line...
   txw, tyw and gw are values for texture and brightness
   always for start- and ending-point of the current line
   A line is also called "Span".
  */

  int32 xw1=dataa[0]; //pax
  int32 xw2=dataa[0];
  int32 txw1=dataa[2]; //tax
  int32 txw2=dataa[2];
  int32 tyw1=dataa[3]; //tay
  int32 tyw2=dataa[3];
  if(yd1)
  for(int sz=dataa[1];sz<=datab[1];sz++)
  {
    // draw if y is inside the screen (clipping)   
    if(sz>=SCREEN_HEIGHT)break;
	if((sz>=0))
	{
		TriTexLine(xw1,xw2,(int32)sz,txw1,txw2,tyw1,tyw2);
	}
	xw1+=xs1;
	xw2+=xs2;
	txw1+=txs1;
	txw2+=txs2;
	tyw1+=tys1;
	tyw2+=tys2;
  }
  /*
   New start values for the second part of the triangle
  */
  xw1=datab[0]+xs3;
  txw1=datab[2]+txs3;
  tyw1=datab[3]+tys3;
  if(yd3) //If Span-Height 1 or higher
  for(int sz=datab[1]+1;sz<datac[1];sz++)
  {
  	if(sz>=SCREEN_HEIGHT)break;
    if(sz>=0)
    {
    	TriTexLine(xw1,xw2,sz,txw1,txw2,tyw1,tyw2);
    }
	xw1+=xs3;
	xw2+=xs2;
	txw1+=txs3;
	txw2+=txs2;
	tyw1+=tys3;
	tyw2+=tys2;
  }
};
