/*
	ChunkyLib
*/

#define CHUNKYLIB 1

struct chape
{
	UBYTE w;
	UBYTE h;
	UBYTE xhandle;
	UBYTE yhandle;
	APTR chunk;
};

extern "Asm"
{
	void c2p030init(register ULONG d0,register ULONG d1);		// Width, Height
	void c2p030(register APTR d0,register APTR d1);			// Chunky, Bitmap
	void ChunkInit(register APTR d0,register APTR d1);		// ChapesBase, CLUT
	void UseChunk(register APTR d0);							// ChunkyBuf
	void ChunkyBlit(register ULONG d0,register ULONG d1,		// 
					register ULONG d2);						// ShpNum, x, y
	void ChunkyBlitMix2(register ULONG d0,register ULONG d1,	// 
						register ULONG d2);					// ShpNum, x, y
	UBYTE MouseButt();
	void ChunKlear();
	void VWait();
	void ChunKopy(register APTR a0,register APTR a1);
};

