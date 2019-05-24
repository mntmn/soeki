/*
	Syntex .h
*/

#include <AppKit.h>
#include <InterfaceKit.h>

class STView : public BView
{
public:
	STView();
	virtual void Draw(BRect dummy=BRect(0,0,0,0));

	BBitmap* actual;
	uint32* work;
};

class STWindow : public BWindow
{
public:
	STWindow();
	virtual bool QuitRequested();
	virtual void MessageReceived(BMessage* what);
	
	void GradientCircle(int sector,int resonance,int radius);
	void GradientBorder(int sector,int resonance);
	void Distort(int type,int sector);
	void Blur();
	void Invert();
	void Mix(uint32* mixwork1,uint32* mixwork2);
	
	void Synthesis();
	
	BBox* displaybox;
		STView* display;
	BBox* dirbox;
		BTextControl* texture1;
		BTextControl* texture2;
		BButton* dobutton;
};

class STApp : public BApplication
{
public:
	STApp();
	virtual void ReadyToRun();

	STWindow* mainwin;
};