// OpenGL tutorial window object
//
// Window object for NeHe's OpenGL tutorials; nice and simple.

#ifndef OpenGL_Wind_h
#define OpenGL_Wind_h

#include <opengl/DirectGLWindow.h>
#include <kernel/OS.h>

#include "Tutorial.h"

class BLocker;

#define WINDOW_TITLE "Soeki OpenGL"

// OpenGL window messages
enum {
	GO_FULLSCREEN = 'gofu',
};

int32 render_thread( void *data );

class GLWindow : public BDirectGLWindow
{
public:
	GLWindow( void );
	virtual ~GLWindow( void );

	// Override BWindow/BDirectGLWindow methods:
	virtual bool QuitRequested( void );
	virtual void MessageReceived( BMessage *msg );
	virtual void FrameResized( float width, float height );
	virtual void DeviceInfo( uint32 device_id, uint32 monitor, const char *name, bool depth, bool stencil, bool accum );

	void SetFPS( float target );

	void Render( void );

	// OpenGL methods - these just call through to the Tutorial object.
	void gInit( void ) { tutorial->gInit(); }
	void gReshape( int width, int height ) { tutorial->gReshape( width, height ); }
	void gDraw( void ) { tutorial->gDraw(); }
	void gCleanup( void ) { tutorial->gCleanup(); }

	// You can override this to handle different keys; return true if you
	// handled the key, otherwise false.  The default handles ESC to exit
	// the program, so you might want to return GLWindow::HandleKeyDown( ... )
	// instead...
	virtual bool HandleKeyDown( const char *bytes, int32 size );

	// Load and fix a texture bitmap.  Caller deletes the returned bitmap,
	// which is unsuitable for use in DrawBitmap*() calls.
	BBitmap *LoadTexture( const char *tex_name );

	// BDirectGLWindow drawing bits...
	BLocker *draw_mutex;
	bool window_teardown;

	thread_id draw_thread;
	sem_id snooze_sem;

	// The OpenGL tutorial
	Tutorial *tutorial;

	// Frames/sec. target and counters (converted)
	float fps_target;
	bigtime_t render_target;
	bigtime_t render_min;
	bigtime_t render_max;

	bigtime_t targets_missed;
	bigtime_t total_frames;

	// Which OpenGL device should we render on?
	uint32 opengl_device;
};

#endif
