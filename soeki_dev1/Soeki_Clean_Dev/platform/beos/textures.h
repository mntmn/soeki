
#ifndef SOEKI_TEX
#define SOEKI_TEX

class Store_TEX
{
		char fname[400];
		char buffer[200];
		BTranslationUtils* trans;
		char* SOEKI_PATH;
	public:
		NW_Texture* Connect(char* n);
		void LoadTexture(int num,char* filename,uint8 flags);
		void LoadRawTexture(int num,char* filename,uint8 flags);
		void FreeTexture(int num);
		const char* MakeName(char* name1,char* name2,uint8 flag);
};

#endif