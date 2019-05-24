#ifndef __SCENE_H__
#define __SCENE_H__

#include "Model.h"

#define DRAW_MODE_TIM 1
#define DRAW_MODE_TAE 2
#define DRAW_MODE_TDE 3
#define DRAW_MODE_TDL 4
#define DRAW_MODE_SIM 5
#define DRAW_MODE_SAE 6
#define DRAW_MODE_SDE 7
#define DRAW_MODE_SDL 8

struct ModelContainer;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	
	virtual void * AddModel( Model *m );
	virtual void RemoveModel( void * );
	
	virtual void SetOrientation( void *model, float rot, float ax, float ay, float az );
	virtual void SetPosition( void *model, float x, float y, float z );
	virtual void SetRotation( void *model, float rot, float drot, float ax, float ay, float az );
	
	virtual void SetState();
	
	virtual void Draw( float delta );
	virtual void Init();
	
	virtual void LightingEnable( bool enable ) { lighting = enable; }
	virtual bool GetLightingEnable() { return lighting; }
	virtual void TexturingEnable( bool enable ) { texturing = enable; }
	virtual bool GetTexturingEnable() { return texturing; }
	virtual void SetDrawMode( int32 mode ) { drawMode = mode; }
	virtual int32 GetDrawMode() { return drawMode; }
	
	virtual void SetTextMode();
	virtual void ReturnFromTextMode();

private:

	ModelContainer *head;
	ModelContainer *tail;
	int32 drawMode;
	
	bool lighting;
	bool oldLighting;
	bool texturing;
	bool oldTexturing;

};









#endif