// see App.h
//
// Converted from the original Windows version.  See the README for details.

#include "App.h"
#include "GLWindow.h"

App::App( void )
	: BApplication( APP_SIGNATURE ),
	  window( 0 )
{
}

App::~App( void )
{
}

void App::ReadyToRun( void )
{
	// Create our window; the Wind constructor will add a view and show
	// the window, so we don't have to do anything else here.
	window = new GLWindow();
}

bool App::QuitRequested( void )
{
	// Close the window and exit the application.
	window->Lock();
	window->Quit();
	return true;
}
