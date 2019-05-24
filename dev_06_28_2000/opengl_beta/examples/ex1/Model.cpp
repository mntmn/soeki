#include <OS.h>
#include <GL/gl.h>
#include <stdio.h>


#include "Model.h"


Model::Model( const char *filename )
{
	int ct;
	FILE *f = fopen( filename, "r" );
	
	if( !f )
	{
		printf( "ERROR loading model file %s \n", filename );
		vertexCount = 0;
		stripCount = 0;
		triangleCount = 0;
	}
	
	fscanf( f, "%d", &vertexCount );
	
	printf( "Vertex Count: %d\n", vertexCount );
	verticies = new Vertex[vertexCount];
	
	Vertex *v = verticies;
	float maxSize = 0.f;
	for ( ct=0; ct < vertexCount; ct++ )
	{
		fscanf(f,"%f %f %f %f %f %f", &v->x, &v->y, &v->z, &v->nx, &v->ny, &v->nz );
		if ( fabs(v->x) > maxSize )
			maxSize = fabs(v->x);
		if ( fabs(v->y) > maxSize )
			maxSize = fabs(v->y);
		if ( fabs(v->z) > maxSize )
			maxSize = fabs(v->z);
		v++;
	}
	for ( ct=0; ct < vertexCount; ct++ )
	{
		verticies[ct].x /= maxSize;
		verticies[ct].y /= maxSize;
		verticies[ct].z /= maxSize;
	}
		
	fscanf( f, "%d", &triangleCount );
	printf( "Triangle Count: %d\n", triangleCount );
	triangles = new Triangle[triangleCount];
	Triangle *t = triangles;
	for ( ct=0; ct < triangleCount; ct++ )
	{
		fscanf( f, "%d %d %d", &t->p1, &t->p2, &t->p3 );
		t++;
	}


	int qpts=4;
	int qp[1024];
	int index;
	Strip q;
	q.pts = qp;
	q.numPts = 4;
	q.pts[2] = triangles[0].p1;
	q.pts[0] = triangles[0].p2;
	q.pts[1] = triangles[0].p3;
	q.pts[3] = triangles[1].p3;

	stripCount = 0;
	for ( int i=2; i<triangleCount; i+=2 )
	{
		if ((triangles[i-1].p1 == triangles[i].p2) &&
			(triangles[i-1].p3 == triangles[i].p3))
		{
			q.pts[q.numPts++] = triangles[i+1].p1;
			q.pts[q.numPts++] = triangles[i+1].p3;
		}
		else
		{
			stripCount ++;
			q.numPts = 4;
			q.pts[2] = triangles[i].p1;
			q.pts[0] = triangles[i].p2;
			q.pts[1] = triangles[i].p3;
			q.pts[3] = triangles[i+1].p3;
		}
	}

printf( "strip count %i \n", stripCount );
	strips = new Strip[stripCount+1];

	index = 0;
	qpts = 4;
	q.pts = qp;
	q.numPts = 4;
	q.pts[2] = triangles[0].p1;
	q.pts[0] = triangles[0].p2;
	q.pts[1] = triangles[0].p3;
	q.pts[3] = triangles[1].p3;
	for ( int i=2; i<triangleCount; i+=2 )
	{
		if ((triangles[i-1].p1 == triangles[i].p2) &&
			(triangles[i-1].p3 == triangles[i].p3))
		{
			q.pts[q.numPts++] = triangles[i+1].p1;
			q.pts[q.numPts++] = triangles[i+1].p3;
			qpts+=2;
		}
		else
		{
			strips[index].numPts = q.numPts;
			strips[index].pts = new int[q.numPts];
			memcpy( strips[index].pts, qp, q.numPts*sizeof(int) );

			index++;
			qpts+=4;
			q.numPts = 4;
			q.pts[2] = triangles[i].p1;
			q.pts[0] = triangles[i].p2;
			q.pts[1] = triangles[i].p3;
			q.pts[3] = triangles[i+1].p3;
		};
	};

	strips[index].numPts = q.numPts;
	strips[index].pts = new int[q.numPts];
	memcpy( strips[index].pts, qp, q.numPts*sizeof(int) );

	displayListTriangleID = glGenLists( 1 );
	glNewList( displayListTriangleID, GL_COMPILE );
	DrawAsTriangles_IM();
	glEndList();

	displayListStripID = glGenLists( 1 );
	glNewList( displayListStripID, GL_COMPILE );
	DrawAsStrips_IM();
	glEndList();

	fclose(f);
}

Model::~Model()
{
	delete[] triangles;
	delete[] verticies;
	for( int i=0; i<stripCount; i++ )
		delete[] strips[i].pts;
	delete[] strips;
}

int Model::GetTriangleCount()
{
	return triangleCount;
}

void Model::DrawAsTriangles_IM()
{
	int ct;

	glBegin(GL_TRIANGLES);
	Triangle *t = triangles;
	for ( ct=0; ct<triangleCount; ct++ )
	{
		glNormal3fv( &verticies[t->p1].nx );
		glVertex3fv( &verticies[t->p1].x );
		glNormal3fv( &verticies[t->p2].nx );
		glVertex3fv( &verticies[t->p2].x );
		glNormal3fv( &verticies[t->p3].nx );
		glVertex3fv( &verticies[t->p3].x );
		t++;
	}
	glEnd();
}

void Model::DrawAsTriangles_AE()
{
	int ct;

	glInterleavedArrays( GL_N3F_V3F, 0, verticies );
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glBegin(GL_TRIANGLES);
	Triangle *t = triangles;
	for ( ct=0; ct<triangleCount; ct++ )
	{
		glArrayElement( t->p1 );
		glArrayElement( t->p2 );
		glArrayElement( t->p3 );
		t++;
	}
	glEnd();
}

void Model::DrawAsTriangles_DE()
{
	glInterleavedArrays( GL_N3F_V3F, 0, verticies );
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glDrawElements( GL_TRIANGLES, triangleCount*3, GL_UNSIGNED_INT, triangles );
}

void Model::DrawAsTriangles_DL()
{
	glCallList( displayListTriangleID );
}

void Model::DrawAsStrips_IM()
{
	for( int i=0; i<stripCount; i++ )
	{
		glBegin( GL_QUAD_STRIP );
		for ( int j=0; j<strips[i].numPts; j++ )
		{
			int t = strips[i].pts[j];
			glNormal3fv( &verticies[t].nx );
			glVertex3fv( &verticies[t].x );
		}
		glEnd();
	}
}

void Model::DrawAsStrips_AE()
{
	glInterleavedArrays( GL_N3F_V3F, 0, verticies );
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	for( int i=0; i<stripCount; i++ )
	{
		glBegin( GL_QUAD_STRIP );
		for ( int j=0; j<strips[i].numPts; j++ )
		{
			glArrayElement( strips[i].pts[j] );
		}
		glEnd();
	}
}

void Model::DrawAsStrips_DE()
{
	glInterleavedArrays( GL_N3F_V3F, 0, verticies );
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	for( int i=0; i<stripCount; i++ )
		glDrawElements( GL_QUAD_STRIP, strips[i].numPts, GL_UNSIGNED_INT, strips[i].pts );
}

void Model::DrawAsStrips_DL()
{
	glCallList( displayListStripID );
}

