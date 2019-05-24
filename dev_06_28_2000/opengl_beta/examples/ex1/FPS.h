#include <GL/gl.h>

class FPS
{
public:
	FPS();
	~FPS();
	
	static void drawCounter( GLfloat frameRate );

private:
	static void drawChar( GLfloat x, GLfloat y, GLint number );

};