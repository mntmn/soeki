// OpenGL tutorial application object
//
// Converted from the original Windows version.  See the README for details.

#ifndef OpenGL_App_h
#define OpenGL_App_h

#include <app/Application.h>

#define APP_SIGNATURE "application/x-vnd.ads.gltutorial2"

class GLWindow;

class App : public BApplication
{
public:
	App( void );
	virtual ~App( void );

	// Override BApplication methods:
	virtual void ReadyToRun( void );
	virtual bool QuitRequested( void );

	// Pointer to our Window object:
	GLWindow *window;
};

#endif
