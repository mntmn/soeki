#include <app/Application.h>
#include <interface/Alert.h>
#include <InterfaceKit.h>
#include <FindDirectory.h>
#include <stdio.h>

#include "Wind.h"
#include "FPS.h"

#define MENU_HEIGHT 15

// ----------------------------------------------------------------------
// OpenGL drawing thread




int32 Wind::render_thread( void *data )
{
	Wind *wnd = (Wind *)data;
	int color = 0;
	int64 lastTime, time;
	int32 frameCount;
	int64 frameBatchTime;
	float fps = 0;

	lastTime = system_time();

	wnd->MakeCurrent();

	char findDir[PATH_MAX];
	char teapotPath[PATH_MAX];
	find_directory( B_BEOS_ETC_DIRECTORY,-1, TRUE,findDir,PATH_MAX );
	sprintf( teapotPath,"%s/%s",findDir,"teapot.data" );
printf( "path = %s\n", teapotPath );
	Model m( teapotPath );

	wnd->scene.SetDrawMode( DRAW_MODE_SAE );
	wnd->scene.LightingEnable( false );

	void *model = wnd->scene.AddModel( &m );
	wnd->scene.SetOrientation( model, -55, 1, 0, 0 );
	wnd->scene.SetPosition( model, 0, -0.4, 0 );
	wnd->scene.SetRotation( model, 0, 90, 0, 0, -1 );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -1, 1, -1, 1, -2, 2 );
	glMatrixMode( GL_MODELVIEW );

	wnd->scene.Init();

	frameBatchTime = 0;
	float delta = 0;

	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	while( !wnd->window_teardown )
	{
		float c = (color & 0x7f) / 255.0;

		color++;

		wnd->scene.Draw( delta );
		
		time = system_time();
		frameBatchTime += time - lastTime;
		delta = (float(time - lastTime)) / 1000000;
		lastTime = time;
		frameCount++;
		if( !(frameCount & 0x7f) )
		{
			fps = 0x7f / float(frameBatchTime) * 1000000;
			frameBatchTime = 0;
			if( !(frameCount & 0x1ff) )
				printf( "fps %f \n", fps );
		}
		if( fps > 0.1 )
		{
			glPushMatrix();
			glTranslatef( -.9, -.9, 0 );
			glScalef( .1, .1, .1 );
			glColor3f( 1, 0, 1 );
			wnd->scene.SetTextMode();
			glColor3f( 1, 1, 0 );
			FPS::drawCounter( fps );
			wnd->scene.ReturnFromTextMode();
			glPopMatrix();
		}

		if( wnd->doubleBuffer )
		{
			wnd->SwapBuffers( wnd->syncEnabled );
			glDrawBuffer( GL_BACK );
		}
		else
		{
			glDrawBuffer( GL_FRONT );
		}

		if( wnd->useSnooze )
		{
			wnd->ReleaseCurrent();
			snooze( 25000 );
			wnd->MakeCurrent();
		}
		else
		{
			wnd->YieldCurrent();
		}
		
//		glClearColor( c, c, c, 1.f );
		if( wnd->zBuffer )
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glEnable( GL_DEPTH_TEST );
		}
		else
		{
			glClear( GL_COLOR_BUFFER_BIT );
			glDisable( GL_DEPTH_TEST );
		}
	
	}
	wnd->scene.RemoveModel( model );
	
	wnd->ReleaseCurrent();
}

void Wind::DeviceInfo( uint32 device_id, uint32 monitor, const char *name, bool depth, bool stencil, bool accum )
{
	char buf[256];
	BMessage msg ('addm');
	msg.AddInt32("num",device_id);
	msg.what = 'dev';
	sprintf( buf, "%s  mon=%x", name, monitor );
	BMenuItem *item = new BMenuItem( buf, new BMessage(msg));
	DeviceMenu->AddItem( item );
	if( device_id == BGL_DEVICE_SOFTWARE )
	{
		item->SetMarked( true );
		checkedDevice = item;
	}
	
	currentDevice++;
	devices[currentDevice].deviceID = device_id;
	devices[currentDevice].first = 0;
	
	//printf( "DeviceInfo device_id=%x    monitor=%x    name=%s \n", device_id, monitor, name );
	//printf( "               depth=%i    stencil=%i   accum=%i \n", depth, stencil, accum );
}

void Wind::VideoModeInfo( uint32 width, uint32 height, uint32 color, uint32 depth, uint32 stencil, uint32 accum )
{
	ModeInfo *m = new ModeInfo;
	
	m->next = 0;
	m->xres = width;
	m->yres = height;
	
	if( devices[currentDevice].first )
	{
		ModeInfo *last = devices[currentDevice].first;
		while( last->next )
			last = last->next;
		last->next = m;
	}
	else
	{
		devices[currentDevice].first = m;
	}

	//printf( "VideoModeInfo   width=%i     height=%i \n", width, height );
	//printf( "                color=0x%x  depth=0x%x    stencil=0x%x   accum=0x%x \n", color, depth, stencil, accum );
}



// ----------------------------------------------------------------------
// Constructor and destructor

Wind::Wind( const char *title )
	: BDirectGLWindow( BRect( 100.0, 100.0, 499.0, 499.0 ), title,
			   		 B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL,
			   		 B_ASYNCHRONOUS_CONTROLS | B_NOT_ZOOMABLE )
{
	window_teardown = false;
	lightingEnabled = false;
	syncEnabled = false;
	zBuffer = true;
	doubleBuffer = true;
	useSnooze = false;
	draw_thread = -1;
	initialized = false;

	/* Create a menu */
	BRect r(0,0,0,MENU_HEIGHT);
	BMenuBar *mb;
	mb = new BMenuBar(r,"main menu");
	AddChild( mb );
	BMessage msg ('addm');
	BMenu *m;
	BMenuItem *i;
	
	fullscreenEnabled = false;
	fullscreenWidth = 640;
	fullscreenHeight = 480;
	currentDevice = -1;

	msg.AddInt32("num",256);
	mb->AddItem( m = new BMenu("File") );
	mb->ResizeToPreferred();
	m->AddItem( new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));

	msg.ReplaceInt32("num",256);
	msg.what = 'buf';
	mb->AddItem( m = new BMenu("Buffers") );
	mb->ResizeToPreferred();
	msg.ReplaceInt32("num", 'DBL' );
	m->AddItem( i = new BMenuItem("Use Double Buffer",new BMessage(msg)) );
	i->SetMarked( true );
	msg.ReplaceInt32("num", 'ZTST' );
	m->AddItem( i = new BMenuItem("Enable Depth Test",new BMessage(msg)) );
	i->SetMarked( true );
	msg.ReplaceInt32("num", 'SNOZ' );
	m->AddItem( new BMenuItem("Enable Snooze",new BMessage(msg)) );

	msg.ReplaceInt32("num",256);
	msg.what = 'draw';
	mb->AddItem( m = new BMenu("Drawing") );
	mb->ResizeToPreferred();
	msg.ReplaceInt32("num", 'TIM' );
	m->AddItem( new BMenuItem("Triangles Immediate Mode",new BMessage(msg)) );
	msg.ReplaceInt32("num", 'TAE' );
	m->AddItem( new BMenuItem("Triangles ArrayElement",new BMessage(msg)));
	msg.ReplaceInt32("num", 'TDE' );
	m->AddItem( new BMenuItem("Triangles DrawElements",new BMessage(msg)));
	msg.ReplaceInt32("num", 'TDL' );
	m->AddItem( new BMenuItem("Triangles DisplayList",new BMessage(msg)));
	msg.ReplaceInt32("num", 'SIM' );
	m->AddItem( new BMenuItem("Strips Immediate Mode",new BMessage(msg)));
	msg.ReplaceInt32("num", 'SAE' );
	m->AddItem( new BMenuItem("Strips ArrayElement",new BMessage(msg)));
	msg.ReplaceInt32("num", 'SDE' );
	m->AddItem( checkedDrawMode = new BMenuItem("Strips DrawElements",new BMessage(msg)));
	checkedDrawMode->SetMarked( true );
	msg.ReplaceInt32("num", 'SDL' );
	m->AddItem( new BMenuItem("Strips DisplayList",new BMessage(msg)));

	msg.ReplaceInt32("num",256);
	msg.what = 'opt';
	mb->AddItem( m = new BMenu("Options") );
	mb->ResizeToPreferred();
	msg.ReplaceInt32("num", 'LIGH' );
	m->AddItem( new BMenuItem("Lighting",new BMessage(msg)) );
	msg.ReplaceInt32("num", 'SYNC' );
	m->AddItem( new BMenuItem("Enable VSync",new BMessage(msg)));

	msg.ReplaceInt32("num",256);
	msg.what = 'dev';
	mb->AddItem( DeviceMenu = new BMenu("Device") );
	mb->ResizeToPreferred();

	msg.ReplaceInt32("num",256);
	msg.what = 'full';
	mb->AddItem( FullscreenMenu = new BMenu("Fullscreen") );
	mb->ResizeToPreferred();
	
	
//	msg.ReplaceInt32("num", 'LIGH' );
//	m->AddItem( new BMenuItem("Primary Display",new BMessage(msg)) );

	EnumerateDevices( BGL_MONITOR_ANY, BGL_ANY | BGL_DOUBLE, BGL_ANY, BGL_NONE, BGL_NONE );
	if( RestartGL( BGL_DEVICE_SOFTWARE ) < B_OK )
		return;
	Show();
}

Wind::~Wind( void )
{
	status_t ret;

	Hide();
	Sync();
	window_teardown = true;
	wait_for_thread( draw_thread, &ret );
}


status_t Wind::RestartGL( uint32 deviceID )
{
	status_t ret;

	window_teardown = true;
	if( draw_thread >= 0 )
		wait_for_thread( draw_thread, &ret );

	if( initialized )
	{
		ShutdownGL();
		initialized = false;
	}
	initialized = true;

	window_teardown = false;

	// Start the drawing thread.
	draw_thread = spawn_thread( render_thread, "OpenGL drawing thread", B_DISPLAY_PRIORITY, this );
	if( draw_thread < 0 )
	{
		fprintf( stderr, "Can't spawn drawing thread, bailing out...\n" );
		be_app->PostMessage( B_QUIT_REQUESTED );
		return B_ERROR;
	}

	fullscreenEnabled = false;
	if( InitializeGL( deviceID, BGL_ANY | BGL_DOUBLE, BGL_ANY, BGL_NONE, BGL_NONE ) < B_OK )
	{
		printf( "Error from InitializeGL \n" );
		be_app->PostMessage( B_QUIT_REQUESTED );
		exit(0);  // Fix me
	}

	BMessage msg ('addm');
	msg.AddInt32("XxY",0);
	msg.what = 'res';
	int32 ct;
	for( ct=0; ct<MAX_DEVICES; ct++ )
	{
		if( devices[ct].deviceID == deviceID )
			break;
	}

	if( ct < MAX_DEVICES )
	{
		int32 index = 0;
		while( FullscreenMenu->RemoveItem( index ) )
		{
		};
		ModeInfo *mInfo = devices[ct].first;
		while( mInfo )
		{
			if( mInfo->xres )
			{
				char buf[64];
				sprintf( buf, "%ix%i", mInfo->xres, mInfo->yres );
				msg.ReplaceInt32("XxY", (mInfo->xres << 16) | mInfo->yres );
				BMenuItem *item = new BMenuItem( buf, new BMessage(msg));
				FullscreenMenu->AddItem( item );
			}
			mInfo = mInfo->next;
		}
	}

	resume_thread( draw_thread );
	return B_OK;
}


bool Wind::QuitRequested( void )
{
	be_app->PostMessage( B_QUIT_REQUESTED );
	return false;
}

void Wind::MessageReceived( BMessage *msg )
{
	BMenuItem *i;
	switch( msg->what )
	{
	case 'buf':
		msg->FindPointer("source", (void **)&i);
		switch( msg->FindInt32( "num" ) )
		{
			case 'DBL':
				doubleBuffer ^= 1;
				i->SetMarked( doubleBuffer );
				break;
			case 'ZTST':
				zBuffer ^= 1;
				i->SetMarked( zBuffer );
				break;
			case 'SNOZ':
				useSnooze ^= 1;
				i->SetMarked( useSnooze );
				break;
		}
		break;

	case 'opt':
		msg->FindPointer("source", (void **)&i);
		switch( msg->FindInt32( "num" ) )
		{
			case 'LIGH':
				lightingEnabled ^= 1;
				scene.LightingEnable( lightingEnabled );
				i->SetMarked( lightingEnabled );
				break;
			case 'SYNC':
				syncEnabled ^= 1;
				i->SetMarked( syncEnabled );
				break;
		}
		break;

	case 'draw':
		msg->FindPointer("source", (void **)&i);
		checkedDrawMode->SetMarked( false );
		checkedDrawMode = i;
		checkedDrawMode->SetMarked( true );
		switch( msg->FindInt32( "num" ) )
		{
			case 'TIM':  scene.SetDrawMode( DRAW_MODE_TIM ); break;
			case 'TAE':  scene.SetDrawMode( DRAW_MODE_TAE ); break;
			case 'TDE':  scene.SetDrawMode( DRAW_MODE_TDE ); break;
			case 'TDL':  scene.SetDrawMode( DRAW_MODE_TDL ); break;
			case 'SIM':  scene.SetDrawMode( DRAW_MODE_SIM ); break;
			case 'SAE':  scene.SetDrawMode( DRAW_MODE_SAE ); break;
			case 'SDE':  scene.SetDrawMode( DRAW_MODE_SDE ); break;
			case 'SDL':  scene.SetDrawMode( DRAW_MODE_SDL ); break;
		}
		break;

	case 'dev':
		{
			msg->FindPointer("source", (void **)&i);
			checkedDevice->SetMarked( false );
			checkedDevice = i;
			checkedDevice->SetMarked( true );
	
			uint32 new_mode = msg->FindInt32( "num" );
			if( RestartGL( new_mode ) < B_OK )
				exit(0);
		}
		break;
	
	case 'res':
		{
			msg->FindPointer("source", (void **)&i);
			uint32 new_res = msg->FindInt32( "XxY" );
			fullscreenEnabled = true;
			fullscreenWidth = new_res >> 16;
			fullscreenHeight = new_res & 0xffff;

			MakeCurrent();	
			FullscreenEnable( fullscreenWidth, fullscreenHeight );
			glViewport( 0, 0, fullscreenWidth, fullscreenHeight );
			ReleaseCurrent();
		}
		break;
	
	case MSG_LIGHT:
		scene.LightingEnable( !scene.GetLightingEnable() );
		break;
		
	case B_KEY_DOWN:
		if( fullscreenEnabled )
		{
			fullscreenEnabled = false;
			FullscreenDisable();
			ResizeTo( fullscreenWidth-1, fullscreenHeight-1 );
			break;
		}
	
	default:
		BDirectWindow::MessageReceived( msg );
		break;
	}
}


void Wind::FrameResized( float width, float height )
{
//printf( "frameResized  %f, %f \n", width, height );
	MakeCurrent();
	if( fullscreenEnabled )
	{
		glViewport( 0, 0, fullscreenWidth, fullscreenHeight );
	}
	else
	{
		if( height > MENU_HEIGHT )
			glViewport( 0, 0, int(width-1), int(height-1) - MENU_HEIGHT );
	}
	ReleaseCurrent();
}

BRect Wind::UpdateGLRect( BRect window_rect )
{
	BRect r;
//printf( "UpdateGLRect in %f, %f \n", window_rect.right, window_rect.bottom );
	if( fullscreenEnabled )
	{
		r = BRect( 0, 0, fullscreenWidth-1, fullscreenHeight-1 );
	}
	else
	{
		r = window_rect;
		if( r.bottom > MENU_HEIGHT )
			r.top += MENU_HEIGHT;
		else
			r.bottom = 0;
	}
//printf( "UpdateGLRect %f, %f \n", r.right, r.bottom );
	return r;
}



