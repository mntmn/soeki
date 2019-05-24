
#include <AppKit.h>
#include <stdio.h>

struct TriangleDef
{
	int32	a[5];
	int32	b[5];
	int32	c[5];
};

class AlphasMagic
{
	public:
		AlphasMagic(int w);
		int RightSection();
		int LeftSection();
		void Triangle(TriangleDef* tri,int16 z_pos);
		void MakeTable();
		void Clear();
		
		uint32* array;
		uint32* array_tex1;
		
		int16 Zmap[640*480+64];
		
		BBitmap* TextureBitmap;
		BTranslationUtils* TextureTrans;
	private:
		int draww;
		float left_array[3*6];
		float right_array[3*6];
		int left_section, right_section;
		int left_section_height, right_section_height;
		float dudx, dvdx, dzdx;
		float left_u, delta_left_u, left_v, delta_left_v, left_z, delta_left_z;
		float left_x, delta_left_x, right_x, delta_right_x;
};