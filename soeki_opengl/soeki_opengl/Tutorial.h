// OpenGL tutorial - Tutorial #2
//
// Display a triangle and a square.

#ifndef Tutorial_h
#define Tutorial_h

#include "GLTutorial.h"
// OpenGL
#include <opengl/GL/gl.h>
#include <opengl/GL/glu.h>

class Tutorial : public GLTutorial
{
public:
	Tutorial( GLWindow *owner );
	virtual ~Tutorial( void );
	
	GLWindow* universe;
	
	GLfloat Viewer_X;
	GLfloat Viewer_Y;
	GLfloat Viewer_Z;
	
	GLfloat Rotation_X;
	GLfloat Rotation_Y;
	GLfloat Rotation_Z;
	
	// OpenGL methods
	virtual void gInit( void );
	virtual void gReshape( int width, int height );
	virtual void gDraw( void );
};

#endif
