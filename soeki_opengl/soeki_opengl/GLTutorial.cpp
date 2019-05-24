// OpenGL tutorial - abstract class

#include "GLTutorial.h"

// OpenGL
#include <opengl/GL/gl.h>
#include <opengl/GL/glu.h>

// ----------------------------------------------------------------------
// Constructor/destructor

GLTutorial::GLTutorial( GLWindow *owner )
	: _owner( owner )
{
	// You can use owner->LoadTexture() in your constructor to get BBitmaps 
	// for later use as textures...
}

GLTutorial::~GLTutorial( void )
{
}

// ----------------------------------------------------------------------
// Key-down handler
//
// Return true if you did something with the key, otherwise false.  If
// you return false, the GLWindow will try to handle it (it handles ESC
// to quit the app); if GLWindow doesn't handle it, it gets passed off to
// the window.

bool GLTutorial::HandleKeyDown( const char *bytes, int32 len )
{
	return false;
}

// ----------------------------------------------------------------------
// OpenGL methods
//
// You implement these in your subclass.

void GLTutorial::gInit( void )
{
	// Set up your OpenGL drawing context, textures, etc.
}

void GLTutorial::gReshape( int width, int height )
{
	// Handle the OpenGL display area being resized.
}

void GLTutorial::gDraw( void )
{
	// Draw your OpenGL scene.
}

void GLTutorial::gCleanup( void )
{
	// Clean up display lists and whatnot
}
