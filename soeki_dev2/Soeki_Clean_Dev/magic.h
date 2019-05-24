
#ifndef SOEKI_MAGIC
#define SOEKI_MAGIC

#include <AppKit.h>

typedef struct TriangleDef
{
	int32	a[5];
	int32	b[5];
	int32	c[5];
}TriangleDef;

class AlphasMagic
{
		unsigned char multab2[256][256];
	public:
		uint32* array;       // Output buffer, 32-bit
		uint32* array_tex1;  // Texture buffer, 32-bit, 256*256 pixels
		int16 Zmap[(640+256)*(480+128)+128]; // Z-Buffer (64 pixels scrolling buffer)
		AlphasMagic();
		void MakeTable();
		inline void TriTexGouLine(int16 z,int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2, int32 g1, int32 g2);
		inline void TriTexGouLine2(int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2, int32 g1, int32 g2);
		inline void TriTexLine(int32 x1, int32 x2, int32 y, int32 tx1, int32 tx2, int32 ty1, int32 ty2 );
		inline void ClearLine(int32 z,int32 x1,int32 x2,int32 y);
		void Triangle(TriangleDef *d,int16 z);
		void Transangle(TriangleDef *d);
		void FlatTriangle(TriangleDef *d);
		void Clear();
};

#endif