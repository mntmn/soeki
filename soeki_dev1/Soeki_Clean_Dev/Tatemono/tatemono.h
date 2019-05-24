/*
	Tatemono
	Classes
*/

#define TATEMONO_SIG "application/x.vnd-tatemono"

class ChapeItem : public BListItem
{
	public:
		ChapeItem(BBitmap* cicon,char* text);
		virtual void DrawItem(BView *owner, BRect frame, bool complete = false);

		char data[100];
		BBitmap* icon;
};

class TListView : public BListView
{
	public:
		TListView();
		virtual void SelectionChanged();
};

class TEListView : public BListView
{
	public:
		TEListView();
		virtual void SelectionChanged();
};

class TMainView : public BView
{
	public:
		TMainView();
		virtual void Draw(BRect dummy=BRect(0,0,0,0));
		virtual void MouseDown(BPoint where);
		virtual void MouseUp(BPoint where);
		void DrawStatics();
		
		bool md;
		bool working;
		
		BBitmap* image;
		BBitmap* image2;
};

class TGridView : public BView
{
	public:
		TGridView();
		virtual void Draw(BRect dummy=BRect(0,0,0,0));
		virtual void MouseDown(BPoint where);
		void DrawGrid(int w,int h);
		
		BBitmap* image;
};

class TMainWin : public BWindow
{
	public:
		TMainWin();
		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage* what);

		TMainView* t_mainview;
		BBitmap* chapeicon;
		BBitmap* eventicon;
		
		BBox* t_chapelist;
			BButton* t_addchape;
			BButton* t_remchape;
			BScrollView* t_clistbox;
				TListView* t_clist;
		
		BBox* t_eventlist;
			BButton* t_addevent;
			BButton* t_remevent;
			BScrollView* t_elistbox;
				TEListView* t_elist;
		
		// Toolbar
		
		BBox* t_toolbar;
			BButton* t_loadbutton;
			BButton* t_savebutton;
			BTextControl* t_id;
			BTextControl* t_cost;
			BTextControl* t_name;
			BTextControl* t_descr;
			TGridView* t_grid;
		
		// Button bar below Mainview
		
		BButton* t_playbutton;
		BButton* t_gridbutton;
		
		// Chape Parameters
		
		BBox* t_paramview;
			BCheckBox* t_checkstatic;
			BCheckBox* t_checkshadow;
			BTextControl* t_chxoff;
			BTextControl* t_chyoff;
		
		BFilePanel* OpenPanel;
		
		// Event Parameters
		
		BBox* t_eventparams;
			BTextControl* t_eventname;
			BMenuField* t_eventchape;
				BMenu* t_evchpmenu;
			BTextControl* t_eventfps;
};


class TApp : public BApplication
{
	public:
		TMainWin* t_mainwin;
		
		TApp();
		//~TApp();
		virtual void ReadyToRun();
		virtual void MessageReceived(BMessage* msg);
		virtual void RefsReceived(BMessage* msg);
};