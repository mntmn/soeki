#include <GL/gl.h>
#include <OS.h>
#include <stdio.h>

#include "Scene.h"

struct ModelContainer
{

	ModelContainer *next;
	ModelContainer *prev;
	Model *m;
	
	float pos[3];
	float rot;
	float rotDelta;
	float rotAxis[3];
	float or;
	float orAxis[3];
};

Scene::Scene()
{
	head = 0;
	tail = 0;
}

Scene::~Scene()
{
	ModelContainer *m = head;
	while( m )
	{
		ModelContainer *next = m->next;
		delete m;
		m = next;
	}
}

void * Scene::AddModel( Model *m )
{
	ModelContainer *mc = new ModelContainer;
	mc->m = m;
	mc->pos[0] = 0.f;	
	mc->pos[1] = 0.f;	
	mc->pos[2] = 0.f;	
	mc->rot = 0.f;
	mc->rotDelta = 0.f;	
	mc->rotAxis[0] = 0.f;	
	mc->rotAxis[1] = 0.f;	
	mc->rotAxis[2] = 1.f;	
	mc->or = 0.f;
	mc->orAxis[0] = 0.f;	
	mc->orAxis[1] = 0.f;	
	mc->orAxis[2] = 1.f;	

	if( tail )
	{
		tail->next = mc;
		mc->prev = tail;
		tail = mc;
		mc->next = 0;
	}
	else
	{
		head = mc;
		tail = mc;
		mc->next = 0;
		mc->prev = 0;
	}
	return mc;
}

void Scene::SetOrientation( void *model, float rot, float ax, float ay, float az )
{
	ModelContainer *mc = (ModelContainer *)model;
	mc->or = rot;
	mc->orAxis[0] = ax;
	mc->orAxis[1] = ay;
	mc->orAxis[2] = az;
}

void Scene::SetPosition( void *model, float x, float y, float z )
{
	ModelContainer *mc = (ModelContainer *)model;
	mc->pos[0] = x;
	mc->pos[1] = y;
	mc->pos[2] = z;
}

void Scene::SetRotation( void *model, float rot, float drot, float ax, float ay, float az )
{
	ModelContainer *mc = (ModelContainer *)model;
	mc->rot = rot;
	mc->rotDelta = drot;
	mc->rotAxis[0] = ax;
	mc->rotAxis[1] = ay;
	mc->rotAxis[2] = az;
}



void Scene::RemoveModel( void *model )
{
	ModelContainer *toRemove = (ModelContainer *)model;
	ModelContainer *m = head;
	while( m )
	{
		if( m == toRemove )
		{
			if( m->prev )
				m->prev->next = m->next;
			if( m->next )
				m->next->prev = m->prev;
			if( m == head )
				head = m->next;
			if( m == tail )
				tail = m->prev;
			delete m;
			return;
		}
		m = m->next;
	}
}

void Scene::SetState()
{
}

void Scene::Draw( float delta )
{
	oldLighting = lighting;
	if( oldLighting )
		glEnable( GL_LIGHTING );
	else
		glDisable( GL_LIGHTING );
		
	oldTexturing = texturing;
	if( oldTexturing )
		glEnable( GL_TEXTURE_2D );
	else
		glDisable( GL_TEXTURE_2D );
	
		

	ModelContainer *mc = head;
	while( mc )
	{
		Model *m = mc->m;
		
		glPushMatrix();
		glTranslatef( mc->pos[0], mc->pos[1], mc->pos[2] );
		glRotatef( mc->or, mc->orAxis[0], mc->orAxis[1], mc->orAxis[2] );
		glRotatef( mc->rot, mc->rotAxis[0], mc->rotAxis[1], mc->rotAxis[2] );

		switch( drawMode )
		{
			case DRAW_MODE_TIM: m->DrawAsTriangles_IM(); break;
			case DRAW_MODE_TAE: m->DrawAsTriangles_AE(); break;
			case DRAW_MODE_TDE: m->DrawAsTriangles_DE(); break;
			case DRAW_MODE_TDL: m->DrawAsTriangles_DL(); break;
			case DRAW_MODE_SIM: m->DrawAsStrips_IM(); break;
			case DRAW_MODE_SAE: m->DrawAsStrips_AE(); break;
			case DRAW_MODE_SDE: m->DrawAsStrips_DE(); break;
			case DRAW_MODE_SDL: m->DrawAsStrips_DL(); break;
		}

		glPopMatrix();
		
		mc->rot += mc->rotDelta * delta;
		if( mc->rot > 360.0 )
			mc->rot -= 360.0;
		if( mc->rot < -360.0 )
			mc->rot += 360.0;
		mc = mc->next;
	}
		
}


void Scene::Init()
{
	static float color_Black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float color_DarkGrey[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	static float color_Grey[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	static float color_White[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float color_Red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	static float color_Green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	static float color_Blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	
	static float light_Position0[4] = { 1.f, 1.f, 1.f, 0.f };
	static float light_Position1[4] = { -1.f, 1.f, 0.f, 0.f };
	static float light_Position2[4] = { 0.f, -1.f, 0.f, 0.f };
	
	glMaterialfv( GL_FRONT, GL_AMBIENT, color_DarkGrey );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, color_Red );
	glMaterialfv( GL_FRONT, GL_SPECULAR, color_White );
	glMaterialf(GL_FRONT, GL_SHININESS, 40 );
	
	glEnable( GL_NORMALIZE );
	glShadeModel(GL_SMOOTH);

	glEnable( GL_LIGHT0 );
	glLightfv( GL_LIGHT0, GL_POSITION, light_Position0 );
	glLightfv( GL_LIGHT0, GL_AMBIENT, color_White );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, color_White );
	glLightfv( GL_LIGHT0, GL_SPECULAR, color_White );

	glEnable( GL_LIGHT1 );
	glLightfv( GL_LIGHT1, GL_POSITION, light_Position1 );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, color_Blue );
	glLightfv( GL_LIGHT1, GL_SPECULAR, color_Blue );

	glEnable( GL_LIGHT2 );
	glLightfv( GL_LIGHT2, GL_POSITION, light_Position2 );
	glLightfv( GL_LIGHT2, GL_DIFFUSE, color_Green );
	glLightfv( GL_LIGHT2, GL_SPECULAR, color_Green );


	glEnable( GL_DEPTH_TEST );
//	glEnable( GL_CULL_FACE );
}

void Scene::SetTextMode()
{
	if( oldLighting )
		glDisable( GL_LIGHTING );
	if( oldTexturing )
		glDisable( GL_TEXTURE_2D );
}

void Scene::ReturnFromTextMode()
{
	if( oldLighting )
		glEnable( GL_LIGHTING );
	if( oldTexturing )
		glEnable( GL_TEXTURE_2D );
}

