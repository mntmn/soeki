/*
	NetWor Master Functions And Data
	© 1999 L.Hartmann/Atomatrix Entertainment
*/

	struct Store
	{
		public:
			APTR Chunky;
			APTR BMap[2];
			int mapx;
			int mapy;
		private:
			Screen* NWScreen;
			Window* NWWindow;
			BitMap* Bitmap[2];
			DBufInfo* DBInfo;
			PLANEPTR OldBitmap[8];
			PLANEPTR OldBitmap2[8];
		public:
			void SetUp();
			void LoadPalette(char PalName[]);
			void UseBitmap(int bmnum);
			void LoadChape(int chapenum,char fname[],int w,int h);
			void CleanUp();
			void NWToFront();
			ULONG MouseX();
			ULONG MouseY();
			void ChunkyLine(int x1,int y1, int x2, int y2, char colour); // Public Source: Bresenham Line
			void LandScape();
	};
	
	void Store::LoadPalette(char PalName[])
	{
		BPTR PalHandle=0;
		int Res=0;
		char* PlName=PalName;
		unsigned char PalBuf[1000];
		unsigned long PalBufL[1000];

		// Datei wird geöffnet und als Bytes in den Buffer geladen
		PalHandle = Open (PlName,MODE_OLDFILE);
		Res = Read (PalHandle, PalBuf, 828);
		Close (PalHandle);

		// Wenn was schiefging, raus hier!
		if (!PalHandle)
		{
			printf ("Networ: Error during loading of palette !!");
			this->CleanUp();
			exit(1002);
		};

		// 0x30 = Anfang der Farbdaten in der Palettedatei
		// Hardcoding, weiß ich, noch zu faul um zu seeken... ;P
		int i=0x30;
		int j=0;

		// Erzeugen einer tollen Tabelle für Intuition
		while (i<=(0x30+3*0xff))
		{
			j=i-0x2f;
			PalBufL[j]=(unsigned long)PalBuf[i]<<24;
			i++;

			// Vorsicht! Nicht vergessen, i zu erhöhen (sonz Banane)
		};
		PalBufL[0]=0x00ff0000;          // 256 Farben, bei 0 anfangen
		PalBufL[3*0xff+2]=0;            // End of table

		// Und wir sind feddich
		LoadRGB32 (&(this->NWScreen->ViewPort),PalBufL);
	};
	
	void Store::LoadChape(int chapenum,char fname[],int w,int h)
	{
		char* name=fname;
		BPTR TheFile=0;
		int res=0;

		TheFile=Open(name,MODE_OLDFILE);

		Chapes[chapenum].w=w-1;
		Chapes[chapenum].h=h-1;
		Chapes[chapenum].xhandle=0;
		Chapes[chapenum].yhandle=0;
		Chapes[chapenum].chunk=AllocMem(w*h,MEMF_FAST | MEMF_CLEAR);
		
		res=Read(TheFile,Chapes[chapenum].chunk,w*h);
		Close (TheFile);
		printf ("\n%d bytes loaded to: %x",res,Chapes[chapenum].chunk);
		
		 if (!res)
		{
			printf("Error loading chape ",*name);
			this->CleanUp();
			exit(1005);
		};
	};
	
	void Store::SetUp()
	{
		NewScreen NWNewScreen=
		{
			0,0,320,256,8,
			2,1,
			0x39100,
			PUBLICSCREEN,
			NULL,
			NULL,
			NULL,
			NULL
		};
		this->NWScreen=OpenScreen(&NWNewScreen);
		
		NewWindow NWNewWindow=
		{
			0,0,320,256,
			2,1,CLOSEWINDOW,
			WINDOWCLOSE | BORDERLESS,
			NULL,NULL,NULL,
			this->NWScreen,NULL,
			0,0,320,256,
			CUSTOMSCREEN
		};
		this->NWWindow=OpenWindow(&NWNewWindow);
		
		this->BMap[0]=AllocMem(320*256,MEMF_CHIP|MEMF_CLEAR);
		this->BMap[1]=AllocMem(320*256,MEMF_CHIP|MEMF_CLEAR);
		
		this->Bitmap[0]=AllocBitMap(320,256,8,BMF_CLEAR|BMF_DISPLAYABLE,NULL);
		this->Bitmap[1]=AllocBitMap(320,256,8,BMF_CLEAR|BMF_DISPLAYABLE,NULL);
		this->DBInfo=AllocDBufInfo(&(this->NWScreen->ViewPort));

		int i=0;
		while (i<8)
		{
			this->OldBitmap[i]=this->Bitmap[0]->Planes[i];
			this->Bitmap[0]->Planes[i]=(PLANEPTR)(this->BMap[0])+10240*i;
			i++;
		};
		i=0;
		while (i<8)
		{
			this->OldBitmap2[i]=this->Bitmap[1]->Planes[i];
			this->Bitmap[1]->Planes[i]=(PLANEPTR)(this->BMap[1])+10240*i;
			i++;
		};

		this->Chunky=AllocMem(320*256,MEMF_FAST|MEMF_CLEAR);
		
		i=0;
		while (i<3000)
		{
			Chapes[i].w=0;
			Chapes[i].h=0;
			Chapes[i].xhandle=0;
			Chapes[i].yhandle=0;
			Chapes[i].chunk=0;
			i++;
		};
		
		BPTR TheFile=0;
		int res=0;
		TheFile=Open("Text:HiSOFT_C/projects/NetWor/Height.dat",MODE_OLDFILE);
		res=Read(TheFile,Blox,100*100);
		Close (TheFile);
		
		Blox[50][50]=200;
		
		/*int x=0;
		for (int y=0;y<99;y++)
		{
			for(x=0;x<99;x++)
			{
				Blox[x][y]=8;
			};
		};*/
		
		this->mapx=0;
		this->mapy=0;
	};
	
	void Store::CleanUp()
	{
		int i=0;
		int cnt=0;
		// Chape-mem freigeben
		while (i<3000)
		{
			if (Chapes[i].chunk)
			{
				FreeMem(Chapes[i].chunk,(Chapes[i].w+1)*(Chapes[i].h+1));
				cnt++
			};
			i++;
		};
		printf("\n%d chapes cleaned up.",cnt);
		
		i=0;
		while (i<8)
		{
			this->Bitmap[0]->Planes[i]=OldBitmap[i];
			i++;
		};
		i=0;
		while (i<8)
		{
			this->Bitmap[1]->Planes[i]=OldBitmap2[i];
			i++;
		};
		
		printf("\nBitplane pointers restored.");
		
		FreeMem (this->BMap[0],320*256);
		FreeMem (this->BMap[1],320*256);
		FreeBitMap (this->Bitmap[0]);
		FreeBitMap (this->Bitmap[1]);
		FreeMem (this->Chunky,320*256);
		FreeDBufInfo (this->DBInfo);
		CloseWindow (this->NWWindow);
		CloseScreen (this->NWScreen);
	};
	
	void Store::UseBitmap(int bmnum)
	{
		ChangeVPBitMap(&(this->NWScreen->ViewPort),this->Bitmap[bmnum],this->DBInfo);
	};
	
	void Store::NWToFront()
	{
		ScreenToFront(this->NWScreen);
	};
	
	ULONG Store::MouseX()
	{
		return (ULONG)this->NWScreen->MouseX;
	};
	
	ULONG Store::MouseY()
	{
		return (ULONG)this->NWScreen->MouseY;
	};
	
	void Store::ChunkyLine(int x1,int y1,int x2,int y2, char colour)
	{
		unsigned char* dest=(unsigned char*)this->Chunky;
		int xDiff,yDiff,
		xDirection,
		minLength,
		startLength,
		runLength,
		endLength,
		errorTerm,
		fractionalAdvance,
		turnOver_reset;

		if (x1>=320) x1=319;
		if (x1<0) x1=0;
		if (y1>=256) y1=255;
		if (y1<0) y1=0;
		if (x2>=320) x2=319;
		if (x2<0) x2=0;
		if (y2>=256) y2=255;
		if (y2<0) y2=0;
		int i,j;

		if(y1>y2)
		{
			yDiff=y1;
			y1=y2;
			y2=yDiff;
			xDiff=x1;
			x1=x2;
			x2=xDiff;
		};

		dest+=x1+y1*320;

		xDiff=x2-x1;
		yDiff=y2-y1;

		if(xDiff<0)
		{
			xDiff=-xDiff;
			xDirection=-1;
		}
		else
			xDirection=1;
			if(!xDiff)
			{
				for(i=0;i<=yDiff;i++)
				{
					*dest=colour;
					dest+=320;
				};
				return;
			};
			if(!yDiff)
			{
				for(i=0;i<=xDiff;i++)
				{
					*dest=colour;
					dest+=xDirection;
				};
				return;
			};
			if(xDiff==yDiff)
			{
				for(i=0;i<=yDiff;i++)
				{
					*dest=colour;
					dest+=320+xDirection;
				}
				return;
			};
		if(xDiff > yDiff)
		{
			minLength=xDiff/yDiff;
			fractionalAdvance=(xDiff%yDiff)<<1;
			turnOver_reset=yDiff<<1;
			errorTerm=(fractionalAdvance>>1)-turnOver_reset;
			startLength=endLength=(minLength>>1)+1;

			if(minLength&1)
				errorTerm+=yDiff;
			else
			{
				if(!fractionalAdvance)
				startLength--;
			};

			for(i=0;i<startLength;i++)
			{
				*dest=colour;
				dest+=xDirection;
			};

			dest+=320;

			for(j=1;j<yDiff;j++)
			{
				runLength=minLength;
				errorTerm+=fractionalAdvance;
				if(errorTerm > 0)
				{
					errorTerm-=turnOver_reset;
					runLength++;
				};
				for(i=0;i<runLength;i++)
				{
					*dest=colour;
					dest+=xDirection;
				}
				dest+=320;
			};
			for(i=0;i<endLength;i++)
			{
				*dest=colour;
				dest+=xDirection;
			};
		}
		else
		{
			minLength=yDiff/xDiff;
			fractionalAdvance=(yDiff%xDiff)<<1;
			turnOver_reset=xDiff<<1;
			errorTerm=(fractionalAdvance>>1)-turnOver_reset;

			startLength=endLength=(minLength>>1)+1;

			if(minLength&1)
				errorTerm+=xDiff;
			else 
			{
				if(!fractionalAdvance)
				startLength--;
			};

			for(i=0;i<startLength;i++)
			{
				*dest=colour;
				dest+=320;
			};
			dest+=xDirection;

			for(j=1;j<xDiff;j++)
			{
				runLength=minLength;
				errorTerm+=fractionalAdvance;
				if(errorTerm > 0 )
				{
					errorTerm-=turnOver_reset;
					runLength++;
				};

				for(i=0;i<runLength;i++)
				{
					*dest=colour;
					dest+=320;
				}
				dest+=xDirection;
			};

			for(i=0;i<endLength;i++)
			{
				*dest=colour;
				dest+=320;
			};
		};
	};

#define hshift 8
#define tshift 8

	void Store::LandScape()
	{
		int mapx=this->mapx;
		int mapy=this->mapy;
		int x,y;
		int ysub,ysub2,ysub3,ysub4;
		int lsub,lsub2,lsub3,lsub4;

		
		//	a--b
		//	|	|
		//	|	|
		//	c--d
		
		for (y=0;y<11;y++)
		{
			for (x=0;x<11;x++)
			{
				ysub=(int)Blox[mapx+x][mapy+y]>>1;
				ysub2=(int)Blox[mapx+x+1][mapy+y]>>1;
				ysub3=(int)Blox[mapx+x][mapy+y+1]>>1;
				ysub4=(int)Blox[mapx+x+1][mapy+y+1]>>1;
				lsub=(int)Light[mapx+x][mapy+y];
				lsub2=(int)Light[mapx+x+1][mapy+y];
				lsub3=(int)Light[mapx+x][mapy+y+1];
				lsub4=(int)Light[mapx+x+1][mapy+y+1];

				tri0.pax=x<<13;
				tri0.pay=(y<<13)-(ysub<<8);
				tri0.paz=lsub<<hshift;
				tri0.pbx=(x+1)<<13;
				tri0.pby=(y<<13)-(ysub2<<8);
				tri0.pbz=lsub2<<hshift;
				tri0.pcx=x<<13;
				tri0.pcy=((y+1)<<13+256)-(ysub3<<8);
				tri0.pcz=lsub3<<hshift;
			
				tri0.rtax=2<<tshift;
				tri0.rtay=2<<tshift;
				tri0.rtbx=125<<tshift;
				tri0.rtby=2<<tshift;
				tri0.rtcx=2<<tshift;
				tri0.rtcy=125<<tshift;

				TEXTRIINIT(&tri0);
				TEXTRI();

				tri0.pax=(x+1)<<13;
				tri0.pay=(y<<13)-(ysub2<<8);
				tri0.paz=lsub2<<hshift;
				tri0.pbx=(x+1)<<13;
				tri0.pby=((y+1)<<13+256)-(ysub4<<8);
				tri0.pbz=lsub4<<hshift;
				tri0.pcx=x<<13;
				tri0.pcy=((y+1)<<13+256)-(ysub3<<8);
				tri0.pcz=lsub3<<hshift;
			
				tri0.rtax=125<<tshift;
				tri0.rtay=2<<tshift;
				tri0.rtbx=125<<tshift;
				tri0.rtby=125<<tshift;
				tri0.rtcx=2<<tshift;
				tri0.rtcy=125<<tshift;
				TEXTRIINIT(&tri0);
				TEXTRI();
				// Horizontal
				this->ChunkyLine(x<<5,(y<<5)-ysub,(x<<5)+32,(y<<5)-ysub2,3);				// a-b
				this->ChunkyLine(x<<5,(y<<5)+32-ysub3,(x<<5)+32,(y<<5)+32-ysub4,3);	// c-d
				// Vertikal
				this->ChunkyLine(x<<5,(y<<5)-ysub,x<<5,(y<<5)+32-ysub3,3);				// a-c
				this->ChunkyLine((x<<5)+32,(y<<5)-ysub2,(x<<5)+32,(y<<5)+32-ysub4,3);	// b-d
			};
		};
	};
