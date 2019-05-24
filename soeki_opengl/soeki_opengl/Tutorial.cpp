// OpenGL tutorial - Tutorial #2
//
// Display a triangle and a square.

#include "Tutorial.h"
#include "GLWindow.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Bitmap.h>

// ----------------------------------------------------------------------
// My Globals

#define NW_MAPW 20
#define NW_MAPH 20

GLfloat Blox[20*20];

GLfloat fct2=0;

struct normals
{
	double nx,ny,nz,nl;
};

normals UpperNrm[20*20];
normals LowerNrm[20*20];

GLfloat Light[20*20];
BBitmap* texture_bits;
GLuint texture[1];
BTranslationUtils* trans;

// ----------------------------------------------------------------------
// Constructor/destructor

Tutorial::Tutorial( GLWindow *owner )
	: GLTutorial( owner )
{
	universe=owner;
	Viewer_X=13.0f;
	Viewer_Y=0.0f;
	Viewer_Z=-76.0f;
	
	Rotation_X=88.0f;
	Rotation_Y=45.0f;
	Rotation_Z=2.0f;
}

Tutorial::~Tutorial( void )
{
	delete texture_bits;
}

// ----------------------------------------------------------------------
// OpenGL methods



void Tutorial::gReshape( int width, int height )
{
	// The OpenGL view has been resized, so we have to reconfigure our
	// OpenGL context to reflect that.

	if( height == 0 ) height = 1;	// prevent divide-by-zero
	
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 20.0, ((float)width)/((float)height), 0.1, 1000 );
	//glOrtho(-100,100,-100,100,-100,100);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

// ---------------------------------------------------------------------------

void MakeLight(int x,int y)
{
	if (x<1 || y<1 || x>18 || y>18) return;
	
	double lx=-150;
	double ly=-150;
	double lz=150;
	double llen=sqrt(lx*lx+ly*ly+lz*lz);
	lx/=llen; //normalisieren des Lichts
	ly/=llen;
	lz/=llen;

	double p1x=0,p1y=0,p2x=32,p2y=0,p3x=32,p3y=32,p4x=0,p4y=32;
	
	double p1z=32*Blox[x+y*NW_MAPW]; //z1  1 2
	double p2z=32*Blox[x+1+y*NW_MAPW]; //z2  4 3
	double p3z=32*Blox[x+1+(y+1)*NW_MAPW]; //z3
	double p4z=32*Blox[x+(y+1)*NW_MAPW]; //z4
	//calculate upper normal
	double kpx=(p1y-p2y)*(p1z-p4z)-(p1z-p2z)*(p1y-p4y);
	double kpy=(p1z-p2z)*(p1x-p4x)-(p1x-p2x)*(p1z-p4z);
	double kpz=(p1x-p2x)*(p1y-p4y)-(p1y-p2y)*(p1x-p4x);
	double len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
	if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0;}
	UpperNrm[x+y*NW_MAPW].nx=kpx;
	UpperNrm[x+y*NW_MAPW].ny=kpy;
	UpperNrm[x+y*NW_MAPW].nz=kpz;

	//double lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;

	//calculate lower normal
	kpx=(p4y-p2y)*(p4z-p3z)-(p4z-p2z)*(p4y-p3y);
	kpy=(p4z-p2z)*(p4x-p3x)-(p4x-p2x)*(p4z-p3z);
	kpz=(p4x-p2x)*(p4y-p3y)-(p4y-p2y)*(p4x-p3x);
	len=sqrt(kpx*kpx+kpy*kpy+kpz*kpz);
	if(len!=0){kpx/=len;kpy/=len;kpz/=len;}else{kpx=0;kpy=1;kpz=0;}
	//lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz))*64;
	LowerNrm[x+y*NW_MAPW].nx=kpx;
	LowerNrm[x+y*NW_MAPW].ny=kpy;
	LowerNrm[x+y*NW_MAPW].nz=kpz;
	
	kpx=(UpperNrm[x+y*NW_MAPW].nx+UpperNrm[x+(y-1)*NW_MAPW].nx+UpperNrm[x-1+y*NW_MAPW].nx+
	LowerNrm[x-1+(y-1)*NW_MAPW].nx+LowerNrm[x-1+y*NW_MAPW].nx+LowerNrm[x+(y-1)*NW_MAPW].nx)/6.0;
	kpy=(UpperNrm[x+y*NW_MAPW].ny+UpperNrm[x+(y-1)*NW_MAPW].ny+UpperNrm[x-1+y*NW_MAPW].ny+
	LowerNrm[x-1+y*NW_MAPW].ny+LowerNrm[x-1+y*NW_MAPW].ny+LowerNrm[x+(y-1)*NW_MAPW].ny)/6.0;
	kpz=(UpperNrm[x+y*NW_MAPW].nz+UpperNrm[x+(y-1)*NW_MAPW].nz+UpperNrm[x-1+y*NW_MAPW].nz+
	LowerNrm[x-1+(y-1)*NW_MAPW].nz+LowerNrm[x-1+y*NW_MAPW].nz+LowerNrm[x+(y-1)*NW_MAPW].nz)/6.0;
	double lf=(lx*kpx+ly*kpy+lz*kpz)/(sqrt(kpx*kpx+kpy*kpy+kpz*kpz)*sqrt(lx*lx+ly*ly+lz*lz));
	Light[x+y*NW_MAPW]=(GLfloat)lf;
};

void MakeTextures()
{
	// Create the texture from the bitmap.
	glGenTextures( 1, &texture[0] );
	glBindTexture( GL_TEXTURE_2D, texture[0] );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	if( texture_bits->ColorSpace() == B_RGBA32 ) {
		glTexImage2D( GL_TEXTURE_2D, 0, 
					  4, 
					  texture_bits->Bounds().IntegerWidth() + 1,
					  texture_bits->Bounds().IntegerHeight() + 1,
					  0, GL_RGBA, GL_UNSIGNED_BYTE,
					  texture_bits->Bits());
	} else if( texture_bits->ColorSpace() == B_RGB32 ) {
		glTexImage2D( GL_TEXTURE_2D, 0, 
					  3, 
					  texture_bits->Bounds().IntegerWidth() + 1,
					  texture_bits->Bounds().IntegerHeight() + 1,
					  0, GL_RGBA, GL_UNSIGNED_BYTE,
					  texture_bits->Bits());
	} else {
		// That's bad.
		exit (666);
	}
}

void SetupMap()
{
	int x,y;

	for (x=0; x<11; x++)
	for (y=0; y<16; y++)
	{
		//Blox[x+y*NW_MAPW]=((float)rand()/RAND_MAX)/2;
		
		Blox[x+y*NW_MAPW]=sin(y*4)*0.2;
		
		/*printf ("x: %d y: %d h: %f\n",x,y,Blox[x][y]);
		Blox[x][y]=0;*/
	};
	
	for (x=0; x<11; x++)
	for (y=0; y<16; y++)
	{
		MakeLight(x,y);
		printf ("x: %d y: %d l: %f\n",x,y,Light[x+y*NW_MAPW]);
	};
	
	//Blox[5][7]=0.5;
};

void stuff()
{
	//glRotatef(rtri,0.0f,1.0f,0.0f);
	//glRotatef(rtri,0.01f,0.0f,0.0f);

	GLfloat x_shift=0;

	int incx=0;
	int incy=0;

	int sr=0;	
	int sc=0;
	
	GLfloat z=0;

	glPushMatrix();

	//fct2+=1.0f;
	//if (fct2>40.0f) fct2=0.0f;
	
	fct2=20;

	for (GLfloat y=(GLfloat)sr; y<15; y++)
	{
		
		for (GLfloat x=(GLfloat)sc; x<15; x++)
		{
			int bx=x;
			int by=y;
			
			//printf ("x: %d y: %d\n",bx,by);

			GLfloat cx=x-7.5;
			GLfloat cy=y-7.5;
	
			/*int bx=(int)x+1;
			int by=(int)y*2+1;*/

			if (bx>=0 && bx<=15 && by>=0 && by<=15)
			{
				GLfloat fct=4.0f;
		
				GLfloat vy1=fct2*Blox[bx+by*NW_MAPW];
				GLfloat vy2=fct2*Blox[bx+1+by*NW_MAPW];
				GLfloat vy3=fct2*Blox[bx+(by+1)*NW_MAPW];
				GLfloat vy4=fct2*Blox[bx+1+(by+1)*NW_MAPW];

				GLfloat light1=Light[bx+by*NW_MAPW];
				GLfloat light2=Light[bx+1+by*NW_MAPW];
				GLfloat light3=Light[bx+(by+1)*NW_MAPW];
				GLfloat light4=Light[bx+1+(by+1)*NW_MAPW];
		
				z=y*0.1;
		
				glBindTexture( GL_TEXTURE_2D, texture[0] );				
				
				glBegin(GL_TRIANGLES);
					// Left

			   		glTexCoord2f(0.0f, 0.0f);
			   		glColor3f ( light1, light1, light1);
					glVertex3f( fct*(0.0f+cx), vy1,fct*(0.0f+cy));
					
					glTexCoord2f(1.0f, 0.0f);
					glColor3f ( light2, light2, light2);
					glVertex3f( fct*(1.0f+cx), vy2,fct*(0.0f+cy));
					
					glTexCoord2f(0.0f, 1.0f);
					glColor3f ( light3, light3, light3);
					glVertex3f( fct*(0.0f+cx), vy3,fct*(1.0f+cy));

					// Right
				
					glTexCoord2f(1.0f, 0.0f);
					glColor3f ( light2, light2, light2);
					glVertex3f( fct*(1.0f+cx), vy2,fct*(0.0f+cy));

					glTexCoord2f(1.0f, 1.0f);
			   		glColor3f ( light4, light4, light4);
					glVertex3f( fct*(1.0f+cx), vy4,fct*(1.0f+cy));
					
					glTexCoord2f(0.0f, 1.0f);
					glColor3f ( light3, light3, light3);
					glVertex3f( fct*(0.0f+cx), vy3,fct*(1.0f+cy));
				glEnd();
			};
			//printf ("z in row %d: %f\n",(int)(y*2),z);
		};
		incx+=(int)(x_shift*2);
		incy+=1-(int)(x_shift*2);
	};
	//rtri+=4.0f;

	glPopMatrix();
};

void Tutorial::gInit( void )
{
	texture_bits=universe->LoadTexture("/boot/home/code/Soeki/tex/desert.jpg");
	MakeTextures();

	SetupMap();
	
	// Set up our OpenGL context.

	// Clear to black
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	
	// Set up the depth buffer
	glClearDepth( 1.0 );
	glDepthFunc( GL_LESS );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	
	// Set up perspective view

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glShadeModel( GL_SMOOTH );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
}

void Tutorial::gDraw( void )
{
	// The actual OpenGL scene.

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glEnable( GL_DEPTH_TEST );

	glTranslatef(Viewer_X,Viewer_Y,Viewer_Z);
	glRotatef(Rotation_X,1.0f,0.0f,0.0f);
	glRotatef(Rotation_Y,0.0f,1.0f,0.0f);
	glRotatef(Rotation_Z,0.0f,0.0f,1.0f);

	stuff();

};
