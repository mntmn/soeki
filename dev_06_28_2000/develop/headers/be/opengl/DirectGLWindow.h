/*******************************************************************************
/
/	File:		DirectGLLWindow.h
/
/	Copyright 1993-2000, Be Incorporated, All Rights Reserved.
/
*******************************************************************************/


#ifndef BDIRECTGLWINDOW_H
#define BDIRECTGLWINDOW_H

#include <GL/gl.h>
#include <DirectWindow.h>
#include <GLDefines.h>

extern "C" GLint __gl_tlIndex;


class BDirectGLWindow : public BDirectWindow
{
public:
						BDirectGLWindow(	BRect		frame,
											const char	*title, 
											window_type	type,
											uint32		flags,
											uint32		workspace = B_CURRENT_WORKSPACE);
									
									
			        	BDirectGLWindow(	BRect		frame,
											const char	*title, 
											window_look	look,
											window_feel feel,
											uint32		flags,
											uint32 		workspace = B_CURRENT_WORKSPACE);

virtual					~BDirectGLWindow();


/* defined for future extension (fragile base class). Identical to BWindow */
virtual void        	Quit(void);
virtual	void			DispatchMessage(BMessage *message, BHandler *handler);
virtual	void			MessageReceived(BMessage *message);
virtual	void			FrameMoved(BPoint new_position);
virtual void			WorkspacesChanged(uint32 old_ws, uint32 new_ws);
virtual void			WorkspaceActivated(int32 ws, bool state);
virtual	void			FrameResized(float new_width, float new_height);
virtual void			Minimize(bool minimize);
virtual void			Zoom(	BPoint rec_position,
								float rec_width,
								float rec_height);
virtual void			ScreenChanged(BRect screen_size, color_space depth);
virtual	void			MenusBeginning();
virtual	void			MenusEnded();
virtual	void			WindowActivated(bool state);
virtual	void			Show();
virtual	void			Hide();
virtual BHandler		*ResolveSpecifier(BMessage *msg,
										int32 index,
										BMessage *specifier,
										int32 form,
										const char *property);
virtual status_t		GetSupportedSuites(BMessage *data);
virtual status_t		Perform(perform_code d, void *arg);

/* new APIs */
						void EnumerateDevices( uint32 monitor, uint32 min_color, uint32 min_depth, uint32 min_stencil, uint32 min_accum );
virtual					void DeviceInfo( uint32 device_id, uint32 monitor, const char *name, bool depth, bool stencil, bool accum );
virtual					void VideoModeInfo( uint32 width, uint32 height, uint32 color, uint32 depth, uint32 stencil, uint32 accum );
						status_t InitializeGL( uint32 device_id, uint32 color, uint32 depth, uint32 stencil, uint32 accum );
						void ShutdownGL();

						void SetGLRect();
virtual					BRect UpdateGLRect( BRect window_rect );
virtual					void DirectConnected(direct_buffer_info *info);
						void MakeCurrent();
						void ReleaseCurrent();
						void YieldCurrent();
						bool IsCurrent();
						void SwapBuffers( bool vsync = true );
virtual					void ErrorCallback (GLenum errorCode);
						status_t FullscreenEnable( int32 width, int32 height );
						void FullscreenDisable();
						
						void SaveDebuggingInfo( const char *filename );

/* private */
private:
						static void pdc( direct_buffer_info	*info, BDirectWindow *dw );
						void processDC( direct_buffer_info	*info );
						static void scanlineHandler ( struct __glContextRec *m_gc, GLint x1, GLint x2);


virtual void        	_ReservedDirectGLWindow1();
virtual void        	_ReservedDirectGLWindow2();
virtual void        	_ReservedDirectGLWindow3();
virtual void        	_ReservedDirectGLWindow4();
virtual void        	_ReservedDirectGLWindow5();
virtual void        	_ReservedDirectGLWindow6();
virtual void        	_ReservedDirectGLWindow7();
virtual void        	_ReservedDirectGLWindow8();

static	int32			refresh_thread( void *data );
static	void			gl_error( struct __glContextRec * gc, GLenum code);
		void			SoftwareBlit();
		sem_id			context_sem;
		int32			context_ben;

		void			*gcAlloc;
		struct __glContextRec 	*m_gc;
		bool			glInitialized;

		bool			dwRequest;
		bool 			needResize;
		int32			resizeW;
		int32			resizeH;
		
		bool			isPrimaryMonitor;			// ture = displays to app-server controled monitor
		bool			fullscreenUserEnable;
		int32			fullscreenWidth;
		int32			fullscreenHeight;
		
		thread_id		refresh_thread_id;
		sem_id			refresh_sem;
		bool			refresh_shutdown;
		void			*clipInfo;
		int32			CurrentDeviceID;
		
		
		uint32 			_ReservedData[63];
};


#endif
