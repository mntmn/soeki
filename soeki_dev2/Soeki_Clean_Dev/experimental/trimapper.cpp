
/*
	Try #2
	Java source by Alpha
	Port to C++ by minute.man / Atomatrix
	At the Party '99 in Aars
	Damn I'm tired
*/	



//Temporäre Vertices:
//float v1=new float[6]; //x,y,z,tex_x,tex_y,brightness (unbenutzt)

#include "trimap.h"

void AlphasMagic::Clear()
{
	for (int i=0;i<640*480;i++) *(array+i)=0x000000;
};

void AlphasMagic::MakeTable()
{
	// Not needed in this implementation
};

AlphasMagic::AlphasMagic(int w)
{
	draww=w;
};

int AlphasMagic::RightSection()
{
    int height = (int)(right_array[ (right_section-1) *6+1] - right_array[right_section*6+1]); // y
    if(height == 0)
        return 0;
    // Calculate the deltas along this section
    delta_right_x = (right_array[ (right_section-1) *6] - right_array[ right_section*6 ]) / (float)height;
    right_x = right_array[ right_section *6];

    right_section_height = height;
    return height;                  // return the height of this section
}

int AlphasMagic::LeftSection()
{
    int height = (int)(left_array[(left_section-1)*6+1] - left_array[(left_section)*6+1]); // y
    if(height == 0)
        return 0;

    float fheight=1/(float)height;
    // Calculate the deltas along this section

    delta_left_x = (left_array[(left_section-1)*6] - left_array[(left_section)*6]) * fheight;
    left_x = left_array[(left_section)*6];
    delta_left_u = (left_array[(left_section-1)*6+3] - left_array[(left_section)*6+3]) * fheight;
    left_u = left_array[(left_section)*6+3];
    delta_left_v = (left_array[(left_section-1)*6+4] - left_array[(left_section)*6+4]) * fheight;
    left_v = left_array[(left_section)*6+4];
    delta_left_z = (left_array[(left_section-1)*6+5] - left_array[(left_section)*6+5]) * fheight;
    left_z = left_array[(left_section)*6+5];

    left_section_height = height;
    return height;                  // return the height of this section
};

inline void Kopi (float* from,float* to)
{
	for (int i=0; i<6; i++) to[i]=from[i];
};

void AlphasMagic::Triangle(TriangleDef* tri,int16 z_pos)
{
    float tempv;
    float* tv=&tempv;
    float v1[6],v2[6],v3[6];
    
    v1[0]=tri->a[0]>>16;
    v2[0]=tri->b[0]>>16;
    v3[0]=tri->c[0]>>16;
    v1[1]=tri->a[1];
    v2[1]=tri->b[1];
    v3[1]=tri->c[1];
    
    for(int c=3;c<6;c++)
    {
        v1[c]=tri->a[c-1]>>16;
        v2[c]=tri->b[c-1]>>16;
        v3[c]=tri->c[c-1]>>16;
    }
    
    // Sort the triangle so that v1 points to the topmost, v2 to the
    // middle and v3 to the bottom vertex.

    if(v1[1] > v2[1]) { Kopi(v1,tv); Kopi(v2,v1); Kopi(tv,v2); }
    if(v1[1] > v3[1]) { Kopi(v1,tv); Kopi(v3,v1); Kopi(tv,v3); }
    if(v2[1] > v3[1]) { Kopi(v2,tv); Kopi(v3,v2); Kopi(tv,v3); }

    // We start out by calculating the length of the longest scanline.

    int height = (int)(v3[1] - v1[1]);
    if(height == 0)
        return;
    float temp = (v2[1] - v1[1]) / height;
    float longest = (float)floor(temp * (v3[0] - v1[0]) + (v1[0] - v2[0]));
    if(longest == 0)
        return;

    // Now that we have the length of the longest scanline we can use that
    // to tell us which is left and which is the right side of the triangle.

    if(longest < 0)
    {
        // If longest is neg. we have the middle vertex on the right side.
        // Store the pointers for the right and left edge of the triangle.
        Kopi(v3,right_array);
        Kopi(v2,right_array+6);
        Kopi(v1,right_array+12);
        right_section  = 2;
        Kopi(v3,left_array);
        Kopi(v1,left_array+6);
        left_section   = 1;

        // Calculate initial left and right parameters
        if(LeftSection() <= 0)
            return;
        if(RightSection() <= 0)
        {
            // The first right section had zero height. Use the next section.
            right_section--;
            if(RightSection() <= 0)
                return;
        }

        // Ugly compensation so that the dudx,dvdx divides won't overflow
        // if the longest scanline is very short.
        if(longest > -1)
            longest = -1;
    }
    else
    {
        // If longest is pos. we have the middle vertex on the left side.
        // Store the pointers for the left and right edge of the triangle.
        Kopi(v3,left_array);
        Kopi(v2,left_array+6);
        Kopi(v1,left_array+12);
        left_section   = 2;
        Kopi(v3,right_array);
        Kopi(v1,right_array+6);
        right_section  = 1;

        // Calculate initial right and left parameters
        if(RightSection() <= 0)
            return;
        if(LeftSection() <= 0)
        {
            // The first left section had zero height. Use the next section.
            left_section--;
            if(LeftSection() <= 0)
                return;
        }

        // Ugly compensation so that the dudx,dvdx divides won't overflow
        // if the longest scanline is very short.
        if(longest < 1)
            longest = 1;
    }

    // Now we calculate the constant deltas for u and v (dudx, dvdx)

    float tlongest=1/longest;
    float dudx = (temp*(v3[3] - v1[3])+(v1[3] - v2[3]))*tlongest;
    float dvdx = (temp*(v3[4] - v1[4])+(v1[4] - v2[4]))*tlongest;
    float dzdx = (temp*(v3[5] - v1[5])+(v1[5] - v2[5]))*tlongest;

    int destptr = (int)v1[1] * draww;

    // Here starts the outer loop (for each scanline)

	//int bright=(int)v3[5]/2;

	int du = (int)(dudx  *(float)256);
    int dv = (int)(dvdx  *(float)256);

	int y=0;

    for(;;)
    {
    	if ((v1[1]+y) >479) return;
    	
    	
        int x1 = (int)left_x;
        int width = (int)right_x - x1;

		int orig_u=(int)(left_u*(float)256);
		int orig_v=(int)(left_v*(float)256);

		if ((v1[1]+y) >= 0)
		{
	        if(width > 0)
	        {
	            int dest = destptr + x1;
	
	            int u  = orig_u;
	            int v  = orig_v;
	            float z  = (left_z);
	
				int xc=x1;
	
	            while(width>0 && xc<640)
	            {
	            	if (dest>=0)
	            	{
	            		int pix=*(array_tex1+((v&0xff00) + (u>>8))) &0xffffff; //RGB ohne Alpha
						int pix2=((pix&0xff00ff)*(int)z)>>7; //r und b
						pix=((pix&0xff00)*(int)z)>>7;    //g allein
						*(array+dest)=(pix&0xff00)|(pix2&0xff00ff);
	            	}
	            	
	            	dest++;
	            	xc++;    
	                u += du;
	                v += dv;
	            	z += dzdx;
	            	width--;
	            };
	        };
		};

        destptr += draww;
        y++;

        // Interpolate along the left edge of the triangle
        if(--left_section_height <= 0)  // At the bottom of this section?
        {
            if(--left_section <= 0)     // All sections done?
                return;
            if(LeftSection() <= 0)      // Nope, do the last section
                return;
        }
        else
        {
            left_x += delta_left_x;
            left_u += delta_left_u;
            left_v += delta_left_v;
            left_z += delta_left_z;
        }

        // Interpolate along the right edge of the triangle
        if(--right_section_height <= 0) // At the bottom of this section?
        {
            if(--right_section <= 0)    // All sections done?
                return;
            if(RightSection() <= 0)     // Nope, do the last section
                return;
        }
        else
        {
            right_x += delta_right_x;
        }
    }
}