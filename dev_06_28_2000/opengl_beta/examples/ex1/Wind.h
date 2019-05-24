#ifndef OpenGL_Wind_h
#define OpenGL_Wind_h

#include <DirectGLWindow.h>
#include <support/Locker.h>
#include <kernel/OS.h>

#define MSG_FULLSCREEN 'full'
#define MSG_LIGHT 'ligh'

#include "Scene.h"


#define MAX_DEVICES 16
typedef struct ModeInfoRec ModeInfo;
struct ModeInfoRec
{
	ModeInfo *next;
	uint32 xres;
	uint32 yres;
};

typedef struct GfxDeviceRec
{
	uint32 deviceID;
	ModeInfo *first;
} GfxDevice;


int32 render_thread( void *data );

class Wind : public BDirectGLWindow
{
public:
	Wind( const char *title );
	virtual ~Wind( void );

	virtual bool QuitRequested( void );
	virtual void MessageReceived( BMessage *msg );
	virtual void FrameResized( float width, float height );
	virtual BRect UpdateGLRect( BRect window_rect );
	
	virtual void DeviceInfo( uint32 device_id, uint32 monitor, const char *name, bool depth, bool stencil, bool accum );
	virtual void VideoModeInfo( uint32 width, uint32 height, uint32 color, uint32 depth, uint32 stencil, uint32 accum );
	

	bool window_teardown;
	bool initialized;
	thread_id draw_thread;
	
private:
	status_t RestartGL( uint32 deviceID );
	static int32 render_thread( void *data );
	Scene scene;

	bool lightingEnabled;
	bool syncEnabled;
	bool doubleBuffer;
	bool zBuffer;
	bool useSnooze;
	
	BMenuItem *checkedDrawMode;
	BMenuItem *checkedDevice;
	BMenu *DeviceMenu;
	BMenu *FullscreenMenu;
	
	bool fullscreenEnabled;
	int32 fullscreenWidth;
	int32 fullscreenHeight;
	
	int32 currentDevice;
	GfxDevice devices[MAX_DEVICES];
};

#endif
