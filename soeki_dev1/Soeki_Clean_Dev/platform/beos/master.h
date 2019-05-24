
#ifndef SOEKI_MASTER
#define SOEKI_MASTER

	#include <AppKit.h>
	#include <InterfaceKit.h>
	#include <TranslationKit.h>
	#include <KernelKit.h>
	#include <GameKit.h>
	
	#include <malloc.h>
	#include <stdio.h>
	#include <string.h>
	
	#include "platform/beos/storage.h"
	#include "independent/gfx32.h"
	#include "independent/structures.h"
	#include "platform/beos/assd.h"
	#include "roster.h"
	
	typedef long (*blit_hook)(long,long,long,long,long,long);
	typedef long (*sync_hook)();
	
	#define PAGEFLIP
	
	class MouseAround : public BView
	{
		public:
			MouseAround();
	};
	
	class NetworDisplay : public BWindowScreen
	{
		public:
			NetworDisplay();
			virtual void MessageReceived(BMessage* msg);
			virtual bool QuitRequested();
			virtual void ScreenConnected(bool really);

			bool didthejob;

			graphics_card_info* cardguts;
			status_t anyerror;
			
			blit_hook HardwareBlit;
			sync_hook HardwareSync;
			
			uint32* kick_me;
			
			MouseAround* m;
			
			bool md();
			uint32 mx();
			uint32 my();
			int32 kd;
	};
	
	class Store
	{
		public:
			uint32* Chunky;
			uint32* Chunky2;
			int mapx;
			int mapy;
			int smoothx;
			int smoothy;
			Dat* Stream;
			NetworDisplay* NWWindow;           // <- This is where the action takes place!
			uint32 omx;
			uint32 omy;
			
			int ub;			// Double Buffering
			int dsf;		// Weird Screen Effect Counter
			
			// General Important Values --------
			
			char* SOEKI_PATH;
			
			int NW_WIDTH;
			int NW_HEIGHT;
			int M;
			
			bool running;
			uint16 termination;

			int gridlockx;
			int gridlocky;
			
			bool EditMode;
			bool BuildMode;
			bool Dragging;
			bool GRID;
			int boxd;
			
			int Command;
			
			int ScreenShot;
			bool PreMain;
			
			// ---------------------------------
			
			// General Tables ------------------
			
			unsigned int Blox[100][100];
			unsigned char Tex[100][100];
			unsigned char Tmap[100][100];
			unsigned int Bmap[100][100];
			
			int16* zbuffer;
			
			xy Cmap[40][40];
			
			int16 Light[100][100];
	
			normals UpperNrm[100][100];
			normals LowerNrm[100][100];
			
			NW_Building Buildings[500];
			NW_Unit Units[500];
			NW_Object Objects[500];
			NW_Relanim Relanims[500];
			NW_Texture* Textures;

			chape Chapes[3000];

			int Buildings_Created;
			int Units_Created;
			int Objects_Created;
			int Relanims_Created;
			
			// ---------------------------------

			// Keyboard Input ------------------
			
			// ---------------------------------
			
			bool Console_Running;			
			
		private:
			bool Active;
			bool Its_My_First_Time;
			
			// Console -------------------------
			
			int Console_X;
			int Console_Y;
			char Console[10][70];
			bool Console_LineDrawn;
			
			// ---------------------------------
			
		public:
			Store();																// 100%
			~Store();																// 100%
			void Connect(assd* a,gfx_32* g,Store_DAT* d);
			void Show();															// 100%
			void FreeChape(int chapenum);											// 100%
			void LoadChape(int chapenum,char fname[],int w,int h);	// RAW			// 100%
			void LoadChape(int chapenum,char fname[]);				// AMXC			// 100%
			void LoadChapes(int chapenum,int max,char fname[]);	// AMXC				// 100%
			void LoadBuilding(int num,char fname[]);
			void ToFront();															// 100%
			bool IsActive();														// 0%
			uint32 MouseX();														// 100%
			uint32 MouseY();														// 100%
			bool MouseButt();
			void IsoScape(int sc,int ec,int sr,int er,int ymode);					// 90%
			void MakeLight(int x,int y);											// 100%
			void DyNum(int x,int y,unsigned int num);								// 100%
			void Attex(int x,int y,int t,int b);									// 100%
			void Dyntex(int x,int y);												// 100%
			int Dynt(int x,int y,char text[]);										// 100%
			int SuperDynt(int x,int y,char text[]);									// 100%
			void OutCon(char text[]);												// 100%
			void MidHandle(int c);													// 100%
			void ExChape(int c1,int c2);											// 100%
			void NewStream(int chp,char fname[]);									// 100%
			void DoStream(int chp);													// 100%
			int GetKey();
			void DrawWindow(int x,int y,int w,int h,char* title);
			void CustomTri(int x1,int y1,int x2,int y2,int x3,int y3,int f,
						   int tx1,int ty1,int tx2,int ty2,int tx3,int ty3);
	};
	
#endif