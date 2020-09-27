
#ifndef SOEKI_MAGIC
#define SOEKI_MAGIC

#include <stdlib.h>
#include <stdint.h>

typedef struct TriangleDef
{
	int32_t	a[5];
	int32_t	b[5];
	int32_t	c[5];
} TriangleDef;

class AlphasMagic
{
		unsigned char multab2[256][256];
	public:
		uint32_t* array;       // Output buffer, 32-bit
		uint32_t* array_tex1;  // Texture buffer, 32-bit, 256*256 pixels
		int16_t Zmap[(640+256)*(480+128)+128]; // Z-Buffer (64 pixels scrolling buffer)
		AlphasMagic();
		void MakeTable();
		inline void TriTexGouLine(int16_t z,int32_t x1, int32_t x2, int32_t y, int32_t tx1, int32_t tx2, int32_t ty1, int32_t ty2, int32_t g1, int32_t g2);
		inline void TriTexGouLine2(int32_t x1, int32_t x2, int32_t y, int32_t tx1, int32_t tx2, int32_t ty1, int32_t ty2, int32_t g1, int32_t g2);
		inline void TriTexLine(int32_t x1, int32_t x2, int32_t y, int32_t tx1, int32_t tx2, int32_t ty1, int32_t ty2 );
		inline void ClearLine(int32_t z,int32_t x1,int32_t x2,int32_t y);
		void Triangle(TriangleDef *d,int16_t z);
		void Transangle(TriangleDef *d);
		void FlatTriangle(TriangleDef *d);
		void Clear();
};

#endif
