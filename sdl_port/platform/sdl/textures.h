
#ifndef SOEKI_TEX
#define SOEKI_TEX

class Store_TEX
{
		char fname[400];
		char buffer[200];
		char* SOEKI_PATH;
	public:
		NW_Texture* Connect(const char* n);
		void LoadTexture(int num,const char* filename,uint8_t flags);
		void LoadRawTexture(int num,const char* filename,uint8_t flags);
		void FreeTexture(int num);
		const char* MakeName(const char* name1,const char* name2,uint8_t flag);
};

#endif
