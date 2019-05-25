/*
	Soeki The Plague - Texture Managment
	©1999 Lukas Hartmann / Atomatrix
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../independent/structures.h"
#include "../../independent/engine.h"
#include "textures.h"

#include <SDL2/SDL_image.h>

NW_Texture Textures[100];

NW_Texture* Store_TEX::Connect(const char* n)
{
	//SOEKI_PATH=n;
	return Textures;
};

const char* Store_TEX::MakeName(const char* name1,const char* name2,uint8_t flag)
{
	for (int i=0; i<200; i++) buffer[i]=0;
	strncpy (buffer,name1,strlen(name1)-4);
	strcat (buffer,"-");
	strncat (buffer,name2,strlen(name2)-4);
	
	printf ("Construct: %s\n",buffer);
	
	switch (flag)
	{
		case TEX_TOPLEFT+TEX_BOTTOMLEFT:
			strcat (buffer,"-l.jpg"); break;
		case TEX_TOPRIGHT+TEX_BOTTOMRIGHT:
			strcat (buffer,"-r.jpg"); break;
		case TEX_BOTTOMLEFT+TEX_BOTTOMRIGHT:
			strcat (buffer,"-b.jpg"); break;
		case TEX_TOPLEFT+TEX_TOPRIGHT:
			strcat (buffer,"-t.jpg"); break;
		case TEX_TOPLEFT:
			strcat (buffer,"-tl.jpg"); break;
		case TEX_TOPRIGHT:
			strcat (buffer,"-tr.jpg"); break;
		case TEX_BOTTOMLEFT:
			strcat (buffer,"-bl.jpg"); break;
		case TEX_BOTTOMRIGHT:
			strcat (buffer,"-br.jpg"); break;
	};
	printf ("%s\n",buffer);
	return (const char*)buffer;
};

uint32_t getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    uint8_t *p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(uint16_t *)p;
        break;

    case 3:
      //if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
            //else
            //return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(uint32_t *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
	
void Store_TEX::LoadTexture(int num,const char* filename,uint8_t flags)
{
	if (Textures[num].data) FreeTexture(num);

	sprintf (fname,"%stex/%s","./",filename);
	
	printf ("Loading texture: %s\n",fname);
    
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface *image;
  image=IMG_Load(fname);

  if(!image) {
    printf("IMG_Load: %s\n", IMG_GetError());
    exit(1);
  }

	Textures[num].data=(uint32_t*)malloc(256*256*4);

  for (int y=0; y<256; y++) {
    for (int x=0; x<256; x++) {
      Textures[num].data[y*256+x] = getpixel(image,x,y);
    }
  }
  
	Textures[num].flags=flags;
};

void Store_TEX::LoadRawTexture(int num,const char* filename,uint8_t flags)
{
	if (Textures[num].data) FreeTexture(num);

	sprintf (fname,"%stex/%s","./",filename);
	
	printf ("Loading texture %d: %s\n",num,fname);

	FILE* diz=fopen (fname,"r");
	Textures[num].data=(uint32_t*)malloc(256*256*4);
	fread(Textures[num].data,1,256*256*4,diz);
	fclose(diz);
  
	printf ("  loaded to %p\n",Textures[num].data);

	Textures[num].flags=flags;
};

void Store_TEX::FreeTexture(int num)
{
	//delete Textures[num].transmap;
	Textures[num].data=NULL;
	Textures[num].flags=0;
};
