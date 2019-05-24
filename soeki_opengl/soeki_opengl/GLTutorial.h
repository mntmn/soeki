// OpenGL tutorial - abstract class

#ifndef GLTutorial_h
#define GLTutorial_h

#include <support/SupportDefs.h>

class GLWindow;

class GLTutorial
{
public:
	GLTutorial( GLWindow *owner );
	virtual ~GLTutorial( void );
	
	// Key-down handler; default lets the GLWindow handle the Esc key 
	// to quit the app.
	virtual bool HandleKeyDown( const char *bytes, int32 len );

	// OpenGL methods; you have to override these with code.
	virtual void gInit( void ) = 0;
	virtual void gReshape( int width, int height ) = 0;
	virtual void gDraw( void ) = 0;
	virtual void gCleanup( void );		// optional

protected:
	GLWindow *_owner;
};

#endif
