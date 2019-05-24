#ifndef __MODEL_H__
#define __MODEL_H__

#include <InterfaceKit.h>
#include <stdlib.h>

struct Vertex
{
	float nx, ny, nz;
	float x, y, z;
};

struct Triangle
{
	int p1, p2, p3;
};

struct Strip
{
	int numPts;
	int *pts;
};

class Model
{
public:
	Model( const char *file );
	~Model();

	int GetTriangleCount();

	void DrawAsTriangles_IM();
	void DrawAsTriangles_AE();
	void DrawAsTriangles_DE();
	void DrawAsTriangles_DL();
	
	void DrawAsStrips_IM();
	void DrawAsStrips_AE();
	void DrawAsStrips_DE();
	void DrawAsStrips_DL();


private:	
	int vertexCount;
	Vertex *verticies;
	
	int triangleCount;
	Triangle *triangles;
	
	int stripCount;
	Strip *strips;
	
	GLuint displayListTriangleID;
	GLuint displayListStripID;

};




#endif