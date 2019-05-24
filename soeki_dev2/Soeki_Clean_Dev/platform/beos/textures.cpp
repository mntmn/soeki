/*
	Soeki The Plague - Texture Managment
	©1999 Lukas Hartmann / Atomatrix
*/

#include <AppKit.h>
#include <TranslationKit.h>
#include <InterfaceKit.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "roster.h"
#include "independent/structures.h"
#include "textures.h"

NW_Texture Textures[100];

NW_Texture* Store_TEX::Connect(char* n)
{
	SOEKI_PATH=n;
	return Textures;
};

const char* Store_TEX::MakeName(char* name1,char* name2,uint8 flag)
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
	
void Store_TEX::LoadTexture(int num,char* filename,uint8 flags)
{
	if (Textures[num].data) FreeTexture(num);

	sprintf (fname,"%stex/%s",SOEKI_PATH,filename);
	
	printf ("Loading texture: %s\n",fname);
	
	Textures[num].transmap=BTranslationUtils::GetBitmapFile(fname,NULL);
	
	if (!Textures[num].transmap)
	{
		printf ("Error: Texture %s doesn't contain a valid image.\n",fname);
		be_app->PostMessage(B_QUIT_REQUESTED);
		exit(666);
	};
	Textures[num].data=(uint32*)Textures[num].transmap->Bits();
	Textures[num].flags=flags;
};

void Store_TEX::LoadRawTexture(int num,char* filename,uint8 flags)
{
	if (Textures[num].data) FreeTexture(num);

	sprintf (fname,"%stex/%s",SOEKI_PATH,filename);
	
	printf ("Loading texture: %s\n",fname);

	FILE* diz=fopen (fname,"r");
	Textures[num].data=(uint32*)malloc(256*256*4);
	fread(Textures[num].data,1,256*256*4,diz);
	fclose(diz);

	Textures[num].flags=flags;
};

void Store_TEX::FreeTexture(int num)
{
	delete Textures[num].transmap;
	Textures[num].data=NULL;
	Textures[num].flags=0;
};
