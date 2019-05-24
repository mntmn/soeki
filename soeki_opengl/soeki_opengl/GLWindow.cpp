// see Wind.h
//
// Window object for NeHe's OpenGL tutorials; nice and simple.

// Class definition
#include "GLWindow.h"

// Misc. goodies we'll need
#include <app/Application.h>
#include <support/Locker.h>
#include <interface/InterfaceDefs.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

// For the LoadTexture() method:
#include <interface/Bitmap.h>
#include <translation/TranslationUtils.h>

// ----------------------------------------------------------------------
// OpenGL drawing thread

int32 render_thread( void *data )
{
	// Create the variables we'll need up here so we don't waste time in
	// the draw loop.
	GLWindow *self = (GLWindow *)data;
	bigtime_t start_render, end_render, render_dt;
	bigtime_t snooze_time;
	status_t retval;

	BRect r = self->Bounds();

	self->MakeCurrent();
	self->gInit();
	self->gReshape( r.IntegerWidth() + 1, r.IntegerHeight() + 1 );
	self->ReleaseCurrent();

	while( !self->window_teardown ) {
		snooze_time = 1;

		// Render and draw the OpenGL scene.
		self->total_frames++;

		start_render = system_time();
		self->Render();
		self->SwapBuffers();
		end_render = system_time();

		render_dt = end_render - start_render;

		if( render_dt > self->render_target ) self->targets_missed++;
		if( render_dt < self->render_target ) snooze_time = self->render_target - render_dt;

		if( render_dt < self->render_min ) self->render_min = render_dt;
		if( render_dt > self->render_max ) self->render_max = render_dt;

		retval = acquire_sem_etc( self->snooze_sem, 1, 
								  B_RELATIVE_TIMEOUT, snooze_time );
		if( retval == B_BAD_SEM_ID || retval == B_INTERRUPTED ) break;
	}

	self->MakeCurrent();
	self->gCleanup();
	self->ReleaseCurrent();

	return B_OK;
}

// ----------------------------------------------------------------------
// Constructor and destructor

GLWindow::GLWindow( void )
	: BDirectGLWindow( BRect( 100.0, 100.0, 319.0, 239.0 ),	// 640x480
			   		   WINDOW_TITLE,
			   		   B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
			   		   B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE ),
	  draw_mutex( NULL ),
	  window_teardown( false ),
	  draw_thread( -1 ),
	  snooze_sem( -1 ),
	  tutorial( NULL ),
	  fps_target( 0.0 ),
	  render_target( 0 ),
	  render_min( LONGLONG_MAX ),
	  render_max( LONGLONG_MIN ),
	  targets_missed( 0 ),
	  total_frames( 0 ),
	  opengl_device( BGL_DEVICE_SOFTWARE )
{
	// Create a drawing mutex
	draw_mutex = new BLocker( "window draw mutex", true );
	
	// Create a snoozer semaphore
	snooze_sem = create_sem( 0, "snoozer sem" );
	if( snooze_sem < 0 ) {
		fprintf( stderr, "Can't create snoozing semaphore, bailing out...\n" );
		
		be_app->PostMessage( B_QUIT_REQUESTED );
		return;
	}

	// Default fps; call this *after* creating the drawing mutex... it
	// locks so you can hack the FPS value on-the-fly.
	SetFPS( 60.0 );

	// Initialize OpenGL
	//
	// In theory you can also use single-buffering, s/DOUBLE/SINGLE/ in
	// these two.
	EnumerateDevices( BGL_MONITOR_PRIMARY, BGL_ANY | BGL_DOUBLE, BGL_ANY, BGL_NONE, BGL_NONE );
	InitializeGL( opengl_device, BGL_ANY | BGL_DOUBLE, BGL_ANY, BGL_NONE, BGL_NONE );

	tutorial = new Tutorial( this );

	// Start the drawing thread.
	draw_thread = spawn_thread( render_thread, 
								"OpenGL drawing thread",
								B_DISPLAY_PRIORITY,
								this );
	if( draw_thread < 0 ) {
		// Can't start the thread, that's bad...
		fprintf( stderr, "Can't spawn drawing thread, bailing out...\n" );
		be_app->PostMessage( B_QUIT_REQUESTED );
		return;
	}

	// Add a shortcut so Alt-F will toggle fullscreen.
	AddShortcut( 'f', 0, new BMessage( GO_FULLSCREEN ) );

	// Magically, the window will now appear on-screen.
	Show();
	Sync();	// <- should prevent the thread from racing the window

	// And we'll start drawing into it.
	(void)resume_thread( draw_thread );
}

GLWindow::~GLWindow( void )
{
	// We're closing the window now...
	window_teardown = true;

	// Wake up anyone who's blocking...
	delete_sem( snooze_sem );
	delete draw_mutex;

	// Make sure the window is hidden before we kill it
	Hide();
	Sync();
	
	// Wait for the drawing thread to exit... which it should've done as
	// soon as we killed the semaphore and mutex.
	int32 retval = B_OK;
	(void)wait_for_thread( draw_thread, &retval );

	if( tutorial ) delete tutorial;

	// Print some info to the user...
	printf( "Frames/second target: %g\n", fps_target );
	printf( "  usecs/frame target: %Ld\n", render_target );
	printf( "       fastest frame: %Ld usec (%g fps)\n", render_min, ( 1000000.0 / (float)render_min ) );
	printf( "       slowest frame: %Ld usec (%g fps)\n", render_max, ( 1000000.0 / (float)render_max ) );
	printf( "# of too-slow frames: %Ld/%Ld (%g%%)\n", targets_missed, total_frames, ((float)targets_missed)/((float)total_frames) * 100.0 );

	printf("\n\n");
	printf("Viewer   X: %f \tY: %f \tZ: %f\n",tutorial->Viewer_X,tutorial->Viewer_Y,tutorial->Viewer_Z);
	printf("Rotation X: %f \tY: %f \tZ: %f\n",tutorial->Rotation_X,tutorial->Rotation_Y,tutorial->Rotation_Z);
}

// ----------------------------------------------------------------------
// BWindow/BDirectGLWindow methods
bool GLWindow::QuitRequested( void )
{
	// Let the application close us.
	be_app->PostMessage( B_QUIT_REQUESTED );
	return false;
}

void GLWindow::MessageReceived( BMessage *msg )
{
	switch( msg->what ) {
	case GO_FULLSCREEN:
		SetFullScreen( !IsFullScreen() );
		break;

	case B_KEY_DOWN:
		{
			const char *bytes = msg->FindString( "bytes" );
			if( !tutorial->HandleKeyDown( bytes, strlen( bytes ) ) ) {
				if( !HandleKeyDown( bytes, strlen( bytes ) ) ) {
					BDirectGLWindow::MessageReceived( msg );
				}
			}
		}
		break;

	default:
		BDirectGLWindow::MessageReceived( msg );
		break;
	}
}

void GLWindow::FrameResized( float width, float height )
{
	MakeCurrent();
	gReshape( int( width ), int( height ) );
	ReleaseCurrent();
}

void GLWindow::DeviceInfo( uint32 device_id, uint32 monitor, 
						   const char *name, 
						   bool depth, bool stencil, bool accum )
{
	if( device_id == BGL_DEVICE_SOFTWARE) {
		opengl_device = device_id;
		
		printf( "Using OpenGL device #%ld: %s\n", device_id, name );
	}
}

// ----------------------------------------------------------------------
// OpenGL methods

void GLWindow::Render( void )
{
	MakeCurrent();
	gDraw();
	ReleaseCurrent();
}

bool GLWindow::HandleKeyDown( const char *bytes, int32 size )
{
	if( size == 1 ) {
		switch( bytes[0] )
		{
		case 'a':
			tutorial->Viewer_Z+=1.0f;
			break;
		case 'y':
			tutorial->Viewer_Z-=1.0f;
			break;
		case 's':
			tutorial->Viewer_Y+=1.0f;
			break;
		case 'x':
			tutorial->Viewer_Y-=1.0f;
			break;
		case 'q':
			tutorial->Viewer_X+=1.0f;
			break;
		case 'w':
			tutorial->Viewer_X-=1.0f;
			break;
		case 'd':
			tutorial->Rotation_X+=1.0f;
			break;
		case 'c':
			tutorial->Rotation_X-=1.0f;
			break;
		case 'f':
			tutorial->Rotation_Y+=1.0f;
			break;
		case 'v':
			tutorial->Rotation_Y-=1.0f;
			break;
		case 'g':
			tutorial->Rotation_Z+=1.0f;
			printf ("RZ: %f\n",tutorial->Rotation_Z);
			break;
		case 'b':
			tutorial->Rotation_Z-=1.0f;
			printf ("RZ: %f\n",tutorial->Rotation_Z);
			break;
		case B_ESCAPE:
			be_app->PostMessage( B_QUIT_REQUESTED );

			return true;
			break;
		}
	}
	
	return false;
}

// ----------------------------------------------------------------------
// Set the frames/second target and times

void GLWindow::SetFPS( float target )
{
	if( target < 0.0 ) {
		fprintf( stderr, "You set the frames/sec target negative: %g", target );
		target = -target;
	}

	// target of 0 means "draw once"
	if( target == 0.0 ) {
		draw_mutex->Lock();
		fps_target = target;
		render_target = 0;
		draw_mutex->Unlock();
		return;
	}

	// Now we calculate the number of microseconds each frame can take to
	// give us that FPS rating.
	//
	// 1 usecond is 1,000,000.0 of a second... there might be a bit of a
	// round-off error here, but a fraction of a microsecond is pretty fast.
	//
	// We use this extra temporary here to avoid locking the mutex for very
	// long... probably not necessary, but floating-point -> integer
	// conversions are notoriously expensive.
	bigtime_t the_target = (bigtime_t)( 1000000.0 / target );

	draw_mutex->Lock();
	fps_target = target;
	render_target = the_target;
	draw_mutex->Unlock();
}

// ----------------------------------------------------------------------
// Load a bitmap and fix it up for use as a texture bitmap, which is
// unsuitable for use in DrawBitmap*() calls due to differences in the
// BeOS and OpenGL co-ordinate systems.
//
// Caller owns the returned bitmap, LoadTexture() returns NULL if the bitmap
// isn't suitable (only handles 32-bit images).  Remember to delete it when
// you're done.

BBitmap *GLWindow::LoadTexture( const char *tex_name )
{
	// NOTE: This replaces auxDIBImageLoad() in the original!
	BBitmap *bits = BTranslationUtils::GetBitmap( tex_name );
	if( !bits ) return bits;

	// We'll only deal with 32-bit textures, because we're lazy.
	// If you're not lazy, you could convert the bitmap here, or
	// add more colour space handlers below where we make the texture
	// with glTexImage2D().
	if( bits->ColorSpace() != B_RGBA32 && bits->ColorSpace() != B_RGB32 ) {
    	delete bits;
    	return NULL;
    }

	// BeOS bitmaps have 0,0 in the top-left; OpenGL expects them in the
	// lower-left.  Dang.
	//
	// Note that this isn't going to behave if you've got an odd number of
	// rows in the bitmap.  Then again, you won't be able to use that as an
	// OpenGL texture.
	bits->Lock();

	int32 bpr = bits->BytesPerRow();

	char *top = static_cast<char *>( bits->Bits() );
	char *bottom = top + bits->Bounds().IntegerHeight() * bpr;

	char *tmp_bytes = new char[bpr];
	while( top < bottom ) {
		// Save a line into the temp buffer.
		memcpy( tmp_bytes, bottom, bpr );

#if 0
		// The way we'd like to do it:
		memcpy( bottom, top, bpr );
		memcpy( top, tmp_bytes, bpr );
#else
		// The way we have to do it.  Why?  BBitmap and OpenGL don't
		// even agree on the order of bytes within an RGBA colour.  :-(
		rgb_color *b = (rgb_color *)( bottom );
		rgb_color *t = (rgb_color *)( top );
		for( int i1 = 0; i1 < ( bpr / 4 ); i1++ ) {
			b->red = t->blue;
			b->green = t->green;
			b->blue = t->red;
			b->alpha = t->alpha;
			b++, t++;
		}
		t = (rgb_color *)( top );
		b = (rgb_color *)( tmp_bytes );
		for( int i2 = 0; i2 < ( bpr / 4 ); i2++ ) {
			t->red = b->blue;
			t->green = b->green;
			t->blue = b->red;
			t->alpha = b->alpha;
			b++, t++;
		}
#endif
		bottom -= bpr;
		top += bpr;
	}

	bits->Unlock();

	return bits;
}
