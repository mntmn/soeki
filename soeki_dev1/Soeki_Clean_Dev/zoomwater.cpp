/* 
 
  Some comments by pi: 
  - es muß immer ein ordentlich gefülltes 
  array für repaint vorhanden sein, sonst gibt's 
  Probleme (Abstürze) 
  - Typumwandlung bei einer Schleife ist nicht immer 
		sinnvoll 
 
 Ich muß noch Perspektive reinbringen! 
 
 Für Bewegung: Muß Bild immer neu umgerechnet werden -> gleich noch Tabs optimieren! 
 Und Blur brauch nicht über ganzes 256x256 erfolgen, da Radius ja different ist 
 
*/ 
 
class AlphasWater
{ 
	public:

		int appletw; 
		int appleth; 
		uint32* array; 
		uint32* water0; 
		uint32* water1; 
		uint32* watertemp; 
		int32* sintab; 
 
		uint32* phong; 
 
 		uint32* HMap;
 
		uint32* array_mt; 
		int arrayptr; 
		int fxh; 
		int fxw;
		int x;
		int y;

		int s0,s1,s2,s0a,s1a,s2a,s3,s4,s5; 
 
		float temp;

	void init();
	void create_ptab();
	void plasma();
	int Clamp(int x);
	void do_water();
	void run(int mx,int my);
};
 
		void AlphasWater::init() 
		{
				appleth = 256;
				appletw = 256;
				fxw = appleth; 
				fxh = appletw; 
				array = malloc(fxw * fxh * 4); 
				int counter=0; 
				int arrayptr=0; 
				for(int x=0;x<fxw;x++) 
				   for(int y=0;y<fxh;y++) 
						   array[arrayptr++]=0xff000000; 
				array_mt = malloc(fxw * fxh *4); 
 
				for(int x=0;x<65536;x++) 
				  array_mt[x]=0xff000000;  //leeres Feld zum Screenlöschen erstellen 
 
				water0 = malloc(fxw * fxh * 4); 
				water1 = malloc(fxw * fxh * 4); 
				phong = malloc(fxw * fxh *4);
				HMap=malloc(65536*4);
 
				sintab = malloc(4*16384); 
				for(int y=0;y<16384;y++) 
				  sintab[y]=(int32)(sin(y*3.141592653589793238/90)*16); 
				  
				create_ptab(); 
				plasma();
				for(int mx=0;mx<65536;mx++) HMap[mx]=HMap[mx]<<3;
		} 
 
/* 
 In die Zoomtab werden die 4 Anteile der benachbarten Pixel gespeichert. 
 Theoretisch könnte man gleich einen Schritt weitergehen und auch größere Sprünge als nur um 1 Pixel erlauben. 
 Die Anteile werden so umgerechnet, das es zusammen 255 ergibt. Somit kann man dann die Werte direkt nehmen, 
 multiplizieren, addieren und um 8 Bits nach rechts schieben, feddich. 
 
*/ 
 
void AlphasWater::create_ptab() 
{ 
 for(int x=0;x<256;x++) 
   for(int y=0;y<256;y++) 
   { 
		 double rx=(double)(x-128); 
		 double ry=(double)(y-128); 
		 double r=8000/(sqrt(rx*rx+ry*ry)+20); 
		 int pixval=(int)(r*0.9); 
		 if(pixval>255)pixval=255; 
		 int pixval2=(int)(r*r)>>8; 
		 if(pixval2>255)pixval2=255; 
		 *(phong+x+(y<<8))=0xff000000|(pixval2<<16)|(pixval2<<8)|pixval; 
   } 
} 

void AlphasWater::plasma()
{
  int p,i,j,k,k2,p2;

  HMap[0]=128;
  for ( p=256; p>1; p=p2 )
  {
    p2=p>>1;
    k=p*8+20; k2=k>>1;
    for ( i=0; i<256; i+=p )
    {
      for ( j=0; j<256; j+=p )
      {
	int a,b,c,d;

	a=HMap[(i<<8)+j];
	b=HMap[(((i+p)&255)<<8)+j];
	c=HMap[(i<<8)+((j+p)&255)];
	d=HMap[(((i+p)&255)<<8)+((j+p)&255)];

	int r=(int)(((float)rand()/(float)RAND_MAX)*256);

	HMap[(i<<8)+((j+p2)&255)]=Clamp(((a+c)>>1)+(r%k-k2));
	HMap[(((i+p2)&255)<<8)+((j+p2)&255)]=Clamp(((a+b+c+d)>>2)+(r%k-k2));
	HMap[(((i+p2)&255)<<8)+j]=Clamp(((a+b)>>1)+(r%k-k2));
      }
    }
  }

  //
  // Smoothing
  //
  for ( k=0; k<3; k++ )
    for ( i=0; i<256*256; i+=256 )
      for ( j=0; j<256; j++ )
      {
           HMap[i+j]=(HMap[((i+256)&0xFF00)+j]+HMap[i+((j+1)&0xFF)]+
		   HMap[((i-256)&0xFF00)+j]+HMap[i+((j-1)&0xFF)])>>2;
      }
}

int AlphasWater::Clamp(int x)
{
  return (x<0 ? 0 : (x>255 ? 255 : x)); // Reduces a value to 0..255 (used in height field computation)
}

void AlphasWater::run(int mx,int my) 
{ 
	double pi=3.14159265358979; 
	double pif=pi/200; 

	s0=s1=s2=s0a=s1a=s2a=0;

	mx=(mx+257)&0xffff;
	my=(my+256)&0xffff;

	for(x=0;x<255;x++)
	{
		s0a=(s0a+158)&524287;
		s1a=(s1a+758)&524287;
		s2a=(s2a+318)&524287;
		s0=s0a;
		s1=s1a;
		s2=s2a;
		s3=s0;s4=s1;s5=s2;

		for(y=0;y<255;y++)
		{
			int dx,dy,ad;
			ad=x+(y<<8);
			dx=(HMap[(ad+1+mx)&0xffff]-HMap[(ad+mx)&0xffff]);
			dy=(HMap[(ad+256+my)&0xffff]-HMap[(ad+my)&0xffff]);
			array[ad]=phong[(160+((160+dy)<<8)+dx)&0xffff];
		}
	}
	
	s0a-=158*252; //Hier aufpassen - Wert �ndert sich, wenn andere Zeilenzahl als 256
	s1a-=758*255;
	s2a-=318*254;
 
	//einen Tropfen irgendwohin 
	//water0[drop]=255; 
} 