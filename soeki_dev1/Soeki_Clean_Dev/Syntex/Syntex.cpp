/*
	Syntex
	Copyright 1999 Lukas Hartmann / Atomatrix Entertainment
	The end of pesky tile painting
*/

#define SYNTEX_SIG "application/x.vnd-syntex"

#include <TranslationKit.h>
#include <StorageKit.h>
#include "Syntex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

BTranslationUtils* trans;

STView::STView() : BView(BRect(10,15,265,270),"heckler",B_FOLLOW_NONE,B_WILL_DRAW)
{
};

void STView::Draw(BRect dummy)
{
	Window()->Lock();
	DrawBitmap(actual);
	Window()->Unlock();
};

void STWindow::GradientCircle(int sector,int resonance,int radius)
{
	// Gradient Circle
	
	float test=3.14/90;
	int xoff=0,yoff=-1;

	if (sector==1) xoff=255;
	if (sector==2) yoff=255;
	if (sector==3) {xoff=255; yoff=255;};
	
	for (int j=radius; j>0; j--)
	{
		/*uint32 grey=256+resonance-j;
		if (grey>255) grey=255;*/
		
		uint32 grey=0xff;
		
		uint32 col=grey<<16|grey<<8|grey;
		for (float i=0; i<360; i+=0.1)
		{
			int x=xoff+sin(test*i)*(float)j;
			int y=yoff+cos(test*i)*(float)j;
			
			if (x>=0 && y>=0 && x<=255 && y<=255)
			{
				*(display->work+x+y*256)=col;
			};
		};
	};
};

void STWindow::GradientBorder(int sector,int resonance)
{
	for (int j=160; j>0; j--)
	{
		/*uint32 grey=256+resonance-j;
		if (grey>255) grey=255;*/
		
		uint32 grey=0xff;
		
		uint32 col=grey<<16|grey<<8|grey;
		for (float i=0; i<256; i++)
		{
			int x,y;
			if (sector==0) {x=j-1; y=i;};
			if (sector==1) {x=256-j; y=i;};
			if (sector==2) {x=i; y=j-1;};
			if (sector==3) {x=i; y=256-j;};

			*(display->work+x+y*256)=col;
		};
	};
};

void STWindow::Distort(int type,int sector)
{
	// Diffuse
	
	if (type==0)
	{
		int startx=0,starty=0;
		int stopx=200,stopy=200;
		int eff=1;
		if (sector==1 || sector==3) {startx=40; stopx=255;};
		if (sector==2 || sector==3) {int temp=startx; startx=stopx; stopx=temp; starty=255; stopy=40; eff=-1;};
	
		for (int y=starty; y!=stopy; y+=eff)
		for (int x=startx; x!=stopx; x+=eff)
		{
			int much=(((float)rand()/(float)RAND_MAX)*40);
			
			int offs=x+y*256;
			if (sector==0 || sector==1)
			{
				offs+=much*256;
			}
			else
			{
				offs-=much*256;
			};
			if (sector==0 || sector==2)
			{
				offs+=much;
			}
			else
			{
				offs-=much;
			};
	
			if (offs>=0 && offs<256*256)
			{
				*(display->work+x+y*256)=*(display->work+offs);
			};
		};
	}
	else
	{
		int startx=0,starty=0;
		int stopx=168,stopy=256;
		int xeff=1,yeff=1;
		if (sector==1) {startx=255; stopx=88; xeff=-1;};
		if (sector==2 || sector==3) {startx=0; stopx=256;};
		if (sector==2) {starty=0; stopy=168;};
		if (sector==3) {starty=256; stopy=88; yeff=-1;};
	
		for (int y=starty; y!=stopy; y+=yeff)
		for (int x=startx; x!=stopx; x+=xeff)
		{
			int much=(((float)rand()/(float)RAND_MAX)*40);
			
			int offs=x+y*256;
			if (sector==2) offs+=much*256;
			if (sector==3) offs-=much*256;
			if (sector==0) offs+=much;
			if (sector==1) offs-=much;
	
			if (offs>=0 && offs<256*256)
			{
				*(display->work+x+y*256)=*(display->work+offs);
			};
		};
	};
};

void STWindow::Blur()
{
	// Blur
	
	for (int y=1; y<255; y++)
		for (int x=1; x<255; x++)
	{
	
		uint32 col1=*(display->work+x+y*256-256)>>16;
		uint32 col2=*(display->work+x+y*256-1)>>16;
		uint32 col3=*(display->work+x+y*256+1)>>16;
		uint32 col4=*(display->work+x+y*256+256)>>16;
		
		uint32 col=(col1+col2+col3+col4)>>2;
		
		*(display->work+x+y*256)=col<<16|col<<8|col;
	};
};

void STWindow::Invert()
{
	for (int y=0; y<256; y++)
	for (int x=0; x<256; x++)
	{
		uint32 col=(*(display->work+x+y*256)>>16)&0xff;
		col=255-col;
		*(display->work+x+y*256)=col<<16|col<<8|col;
	};
};

void STWindow::Mix(uint32* mixwork1,uint32* mixwork2)
{
	// Mix
	
	for (int y=0; y<256; y++)
		for (int x=0; x<256; x++)
	{
		uint32 col1=*(mixwork1+x+y*256);
		uint32 col2=*(mixwork2+x+y*256);
		
		int16 r1=(col1>>16)&0xff;
		int16 g1=(col1>>8)&0xff;
		int16 b1=col1&0xff;
		
		int16 r2=(col2>>16)&0xff;
		int16 g2=(col2>>8)&0xff;
		int16 b2=col2&0xff;
		
		float f1=*(display->work+x+y*256)>>16;
		float f2=255-f1;
		
		f1=f1/255;
		f2=f2/255;
		
		uint32 r=(uint32)((float)r1*f1+(float)r2*f2);
		uint32 g=(uint32)((float)g1*f1+(float)g2*f2);
		uint32 b=(uint32)((float)b1*f1+(float)b2*f2);

		*(display->work+x+y*256)=r<<16|g<<8|b;
	};
};

STWindow::STWindow() : BWindow(BRect(50,50,50+301,50+255+100),"Syntex",B_TITLED_WINDOW,B_NOT_RESIZABLE)
{
	display=new STView();
	display->actual=new BBitmap(BRect(0,0,255,255),B_RGB32);
	display->work=(uint32*)display->actual->Bits();

	displaybox=new BBox(BRect(0,0,300,290),"Heckler",B_FANCY_BORDER);
	displaybox->SetLabel("Synthesis");

	dirbox=new BBox(BRect(0,291,300,355),"Koch",B_FANCY_BORDER);
	dirbox->SetLabel("Controls");
	
	dobutton=new BButton(BRect(5,15,58,45),"synt","Synthesis",new BMessage('doit'));
	texture1=new BTextControl(BRect(60,15,285,35),"tex1","tex1","/boot/home/code/Soeki/tex/desert.jpg",new BMessage('tex1'));
	texture2=new BTextControl(BRect(60,37,285,75),"tex2","tex2","/boot/home/code/Soeki/tex/grass2.jpg",new BMessage('tex2'));
	
	texture1->SetDivider(30);
	texture2->SetDivider(30);
	
	displaybox->AddChild(display);
	dirbox->AddChild(dobutton);
	dirbox->AddChild(texture1);
	dirbox->AddChild(texture2);
	AddChild(displaybox);
	AddChild(dirbox);
};

bool STWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
};

const char* MakeName(char* name1,char* name2,uint8 flag)
{
	char buffer[200];
	for (int i=0; i<200; i++) buffer[i]=0;
	strncpy (buffer,name1,strlen(name1)-4);
	strcat (buffer,"-");
	strncat (buffer,name2,strlen(name2)-4);
	
	printf ("Construct: %s\n",buffer);
	
	switch (flag)
	{
		case 0:
			strcat (buffer,"-l.dat"); break;
		case 1:
			strcat (buffer,"-r.dat"); break;
		case 2:
			strcat (buffer,"-t.dat"); break;
		case 3:
			strcat (buffer,"-b.dat"); break;
		case 4:
			strcat (buffer,"-tl.dat"); break;
		case 5:
			strcat (buffer,"-tr.dat"); break;
		case 6:
			strcat (buffer,"-bl.dat"); break;
		case 7:
			strcat (buffer,"-br.dat"); break;
		case 8:
			strcat (buffer,"-tli.dat"); break;
		case 9:
			strcat (buffer,"-tri.dat"); break;
		case 10:
			strcat (buffer,"-bli.dat"); break;
		case 11:
			strcat (buffer,"-bri.dat"); break;
	};
	printf ("%s\n",buffer);
	return (const char*)buffer;
};

void STWindow::Synthesis()
{
	SetTitle("Loading Textures...");
	
	BBitmap* mix2=trans->GetBitmapFile(texture1->Text());
	BBitmap* mix1=trans->GetBitmapFile(texture2->Text());
	
	uint32* mixwork1=mix1->Bits();
	uint32* mixwork2=mix2->Bits();

	char* one=texture1->Text();
	int onelen=strlen(one);
	int last=0;

	for (int i=0; i<onelen; i++)
	{
		if (one[i]=='/') last=i+1;
	};
	
	char nameone[20];
	strcpy (nameone,&one[last]);
	
	one=texture2->Text();
	onelen=strlen(one);
	last=0;
	
	for (int i=0; i<onelen; i++)
	{
		if (one[i]=='/') last=i+1;
	};
	
	char nametwo[20];
	strcpy (nametwo,&one[last]);

	for (int j=0; j<4; j++)
	{
		for (int i=0; i<256*256;i++) *(display->work+i)=0;
	
		SetTitle("Alpha Curve...");
		GradientCircle(j,20,160);
		display->Draw();
		
		SetTitle("Distortion...");
		for (int x=0; x<2; x++)
		{	
			Distort(0,j);
			display->Draw();
		};
		
		SetTitle("Blur...");
		for (int x=0; x<8; x++) Blur();
		display->Draw();
		
		SetTitle("Mix...");
		Mix(mixwork1,mixwork2);
		display->Draw();
		
		SetTitle("Saving...");
		
		char buffer[200];
		strcpy (buffer,"/boot/home/code/Soeki/tex/");
		strcat (buffer,MakeName(nameone,nametwo,j+4));
		
		FILE* save=fopen(buffer,"w");
		fwrite(display->work,1,4*256*256,save);
		fclose (save);
		
		SetTitle("Done.");
		//snooze(2500000);
	};

	for (int j=0; j<4; j++)
	{
		for (int i=0; i<256*256;i++) *(display->work+i)=0;
	
		SetTitle("Alpha Curve...");
		GradientCircle(j,20,180);
		display->Draw();
		
		SetTitle("Invert...");
		Invert();
		display->Draw();
		
		SetTitle("Distortion...");
		for (int x=0; x<2; x++)
		{	
			Distort(0,j);
			display->Draw();
		};
		
		SetTitle("Blur...");
		for (int x=0; x<8; x++) Blur();
		display->Draw();
		
		SetTitle("Mix...");
		Mix(mixwork1,mixwork2);
		display->Draw();
		
		SetTitle("Saving...");
		
		char buffer[200];
		strcpy (buffer,"/boot/home/code/Soeki/tex/");
		strcat (buffer,MakeName(nameone,nametwo,j+8));
		
		FILE* save=fopen(buffer,"w");
		fwrite(display->work,1,4*256*256,save);
		fclose (save);
		
		SetTitle("Done.");
		snooze(3000000);
	};

	for (int j=0; j<4; j++)
	{
		for (int i=0; i<256*256;i++) *(display->work+i)=0;
	
		SetTitle("Alpha Border...");
		GradientBorder(j,20);
		display->Draw();
		
		SetTitle("Distortion...");
		for (int x=0; x<2; x++)
		{	
			Distort(1,j);
			display->Draw();
		};
		
		SetTitle("Blur...");
		for (int x=0; x<8; x++) Blur();
		display->Draw();
		
		SetTitle("Mix...");
		Mix(mixwork1,mixwork2);
		display->Draw();
		
		SetTitle("Saving...");
		
		char buffer[200];
		strcpy (buffer,"/boot/home/code/Soeki/tex/");
		strcat (buffer,MakeName(nameone,nametwo,j));
		
		FILE* save=fopen(buffer,"w");
		fwrite(display->work,1,4*256*256,save);
		fclose (save);
		
		SetTitle("Done.");
		//snooze(2500000);
	};
};

void STWindow::MessageReceived(BMessage* what)
{
	switch (what->what)
	{
		case 'doit':
			Synthesis();
	};
};

STApp::STApp() : BApplication(SYNTEX_SIG)
{
};

void STApp::ReadyToRun()
{
	mainwin=new STWindow();
	mainwin->Show();
	mainwin->display->Draw();
};

int main()
{
	be_app=new STApp();
	be_app->Run();
};