#include <OS.h>

#include "GLViewer.h"
#include "Wind.h"

GLViewer::GLViewer( void )
	: BApplication( APP_SIGNATURE ), window( 0 )
{
}

GLViewer::~GLViewer( void )
{
}

void GLViewer::ReadyToRun( void )
{
	window = new Wind( "OpenGL Viewer" );
}

bool GLViewer::QuitRequested( void )
{
	window->Lock();
	window->Quit();
	return true;
}


int main( void )
{
	GLViewer the_app;
	the_app.Run();
	return 0;
}
