
	#include <stdio.h>
	
	struct vector
	{
		float x;
		float y;
		float z;
	};
	
	vector vtx1;
	vector vtx2;
	vector p1,p2,p3;
	
	float getplaneheight(float x, float y)
    {
       // Plane (aus 3 Punkten des Vierecks)
       //  p1 *
       //                   * p2
       //       p3*  
       //Vektor von p1 zu p2:
        vtx1.x=p2.x-p1.x;
        vtx1.y=p2.y-p1.y;
        vtx1.z=p2.z-p1.z;
       //Vektor von p1 zu p3:
        vtx2.x=p3.x-p1.x;
        vtx2.y=p3.y-p1.y;
        vtx2.z=p3.z-p1.z;
 		//Kreuzprodukt berechnet die Normale, also A, B und C
        float A = vtx1.y * vtx2.z - vtx1.z * vtx2.y;
        float B = vtx1.z * vtx2.x - vtx1.x * vtx2.z;
        float C = vtx1.x * vtx2.y - vtx1.y * vtx2.x;
        //D ist Abstand der Fläche zum Koordinatenursprung. Wird berechnet aus A, B, C und irgendeinem der Punkte der Fläche
        float D = (p1.x * A + p1.y * B + p1.z * C);
        // A*x + B*y + C*z = D;
		// Für Höhe z nur noch Umformung:
        float z = (D - A*x - B*y) / C;
        return z;
        // für x und y die Koordinaten einsetzen
        // Tip: A, B, C und D können vorberechnet werden
    };
    
    int main()
    {
    	p1.x=1;
    	p1.y=1;
    	p1.z=20;
    	
    	p2.x=31;
    	p2.y=1;
    	p2.z=10;
    	
    	p3.x=1;
    	p3.y=31;
    	p3.z=10;
    
    	float z=getplaneheight(0,0);
    	printf ("0,0: %f\n",z);
    	
    	z=getplaneheight(31,1);
    	printf ("31,0: %f\n",z);
    	
    	z=getplaneheight(1,31);
    	printf ("0,31: %f\n",z);
    	
    	z=getplaneheight(10,10);
    	printf ("10,10: %f\n",z);
    };