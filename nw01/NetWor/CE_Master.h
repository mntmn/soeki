/*
	ChapEd Master Functions And Data
	© 1999 L.Hartmann/Atomatrix Entertainment
*/

	struct Library* IFFParseBase;

	struct BitMapHeader
	{
	    UWORD	 bmh_Width;		/* Width in pixels */
	    UWORD	 bmh_Height;		/* Height in pixels */
	    WORD	 bmh_Left;		/* Left position */
	    WORD	 bmh_Top;		/* Top position */
	    UBYTE	 bmh_Depth;		/* Number of planes */
	    UBYTE	 bmh_Masking;		/* Masking type */
	    UBYTE	 bmh_Compression;	/* Compression type */
	    UBYTE	 bmh_Pad;
	    UWORD	 bmh_Transparent;	/* Transparent color */
	    UBYTE	 bmh_XAspect;
	    UBYTE	 bmh_YAspect;
	    WORD	 bmh_PageWidth;
	    WORD	 bmh_PageHeight;
	};

	struct Store
	{
		public:
			APTR Chunky;
			APTR Chunky2;
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
			BOOL Active;
		public:
			void SetUp();
			void LoadPalette(char PalName[]);
			void LoadBitmap(char name[],int bm);
			void Bitmap2Chunky(int bm,APTR chunky);
			void FreeChape(int chapenum);
			void UseBitmap(int bmnum);
			void LoadChape(int chapenum,char fname[],int w,int h);
			void SaveChape(int chapenum,char fname[]);
			void LoadCLUT(char fname[],unsigned char* clut);
			unsigned char CPoint(int x,int y);
			void GrabChape(int chapenum,APTR chunky,int x, int y, int x2, int y2);
			void CleanUp();
			void NWToFront();
			BOOL NWActive();
			ULONG MouseX();
			ULONG MouseY();
			void ChunkyLine(int x1,int y1, int x2, int y2,unsigned char colour, BOOL alpha); // Public Source: Bresenham Line
	};
	
	void Store::FreeChape(int c)
	{
		if (Chapes[c].chunk)
		{
			FreeMem(Chapes[c].chunk,(Chapes[c].w+1)*(Chapes[c].h+1));
			Chapes[c].chunk=0;
			Chapes[c].w=0;
			Chapes[c].h=0;
			Chapes[c].xhandle=0;
			Chapes[c].yhandle=0;
		};
	};
	
	BOOL Store::NWActive()
	{
		Message* msg=0;
		IntuiMessage* imsg=0;
		BOOL act=this->Active;
		msg=GetMsg(this->NWWindow->UserPort);
		while (msg)
		{
			imsg=(IntuiMessage*)msg;
			if (imsg->Class==IDCMP_ACTIVEWINDOW) act=TRUE;
			if (imsg->Class==IDCMP_INACTIVEWINDOW) act=FALSE;
			ReplyMsg((Message*)msg);
			msg=GetMsg(this->NWWindow->UserPort);
		};
		this->Active=act;
		return act;
	};
	
	void Store::LoadCLUT(char fname[],unsigned char* clut)
	{
		BPTR FHandle=0;
		int res=0;
		FHandle=Open(fname,MODE_OLDFILE);
		res=Read(FHandle,clut,2560);
		Close(FHandle);
		if (!res)
		{
			printf("Error while loading CLUT! %d",res);
			exit(1010);
		};
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
			CTable[j-1]=PalBuf[i];
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
	
	void Store::SaveChape(int chapenum,char fname[])
	{
		char* name=fname;
		BPTR TheFile=0;
		
		TheFile=Open(name,MODE_NEWFILE);
		
		char header[]="AMXC";
		
		Write(TheFile,header,4);
		Write(TheFile,&Chapes[chapenum],8);
		Write(TheFile,Chapes[chapenum].chunk,Chapes[chapenum].w*Chapes[chapenum].h);
		Close (TheFile);
		printf ("\nSaved chape %s.\n",fname);
	};
			
	void Store::LoadBitmap(char name[],int bm)
	{
		BitMap* heckler=this->Bitmap[bm];
		unsigned long ID_ILBM=MAKE_ID('I','L','B','M');
		unsigned long ID_BMHD=MAKE_ID('B','M','H','D');
		unsigned long ID_BODY=MAKE_ID('B','O','D','Y');
		if (!GoodID(ID_ILBM) || !GoodID(ID_BMHD))
		{
			printf("Invalid IFF ID!");
			exit(1000);
		};
		BPTR ifffile=Open(name,MODE_OLDFILE);
		IFFHandle* myiff=AllocIFF();
		myiff->iff_Stream=ifffile;
		InitIFFasDOS(myiff);
		
		if (OpenIFF(myiff,IFFF_READ))
		{
			printf("OpenIFF() failed!\n");
			CloseIFF(myiff);
			FreeIFF(myiff);
			Close(ifffile);
			exit(1000);
		};
		
		if (PropChunk(myiff,ID_ILBM,ID_BMHD))
		{
			printf("PropChunk() for BMHD failed!\n");
			CloseIFF(myiff);
			FreeIFF(myiff);
			Close(ifffile);
			exit(1000);
		};
		
		/* if (PropChunk(myiff,ID_ILBM,ID_BODY))
		{
			printf("PropChunk() for BODY failed!\n");
			goto die;
		}; */
		
		ContextNode* top;
		char idbuf[5];
		long err=ParseIFF(myiff,IFFPARSE_RAWSTEP),buf1=0,buf2=0;
		BitMapHeader* bmhd=0;
		UBYTE* cmpr_body=0;
		
		while (err!=IFFERR_EOF)
		{
			if (err==0)
			{
				top=CurrentChunk(myiff);
				printf("\nFound: %s\n",IDtoStr(top->cn_ID,idbuf));
				printf("- Type: %s\n",IDtoStr(top->cn_Type,idbuf));
				printf("- Size: %d\n",top->cn_Size);
				if (top->cn_ID==ID_BMHD)
				{
					bmhd=(BitMapHeader*)AllocMem(top->cn_Size,MEMF_FAST|MEMF_CLEAR);
					buf1=ReadChunkBytes(myiff,bmhd,top->cn_Size);
					buf1=top->cn_Size;
				};
				if (top->cn_ID==ID_BODY)
				{
					cmpr_body=(UBYTE*)AllocMem(top->cn_Size,MEMF_FAST|MEMF_CLEAR);
					buf2=ReadChunkBytes(myiff,cmpr_body,top->cn_Size);
					buf2=top->cn_Size;
				};
			}; 
			err=ParseIFF(myiff,IFFPARSE_RAWSTEP);
		};
	
		if (!buf1||!buf2)
		{
			printf("Fatal Error! You lot! Think ya can fool my program?\n");
			printf("The error(s) YOU caused:\n");
			if(!buf1) printf("You panneman! This file has no ILBM BMHD!\n")
				else FreeMem(bmhd,buf1);
			if(!buf2) printf("You malleman! This file has no ILBM BODY!\n")
				else FreeMem(cmpr_body,buf2);
			printf("Havoc! ARGH! Bye! Don't come back!");
			CloseIFF(myiff);
			FreeIFF(myiff);
			Close(ifffile);
			exit(666);
		};

		ULONG blood_drops=0;

		int width=bmhd->bmh_PageWidth;
		int height=bmhd->bmh_PageHeight;
		int depth=bmhd->bmh_Depth;
		int koch=0,i=0,bones=0;
		long bytecount=0;
		BYTE rbuf=0;
		UBYTE* bufptr=0;

		printf("Image Specs:\n");
		printf("Size: %dx%dx%d\n",width,height,depth);
		printf("Compression: %x\n",bmhd->bmh_Compression);
		
		width/=8;
		
		if (bmhd->bmh_Compression);
		{
			printf("The doctor sez: We must decompress that! Start da bloodsucker! ACK!\n");
			printf("BRRR: ");
			for (blood_drops=0;blood_drops<buf2;blood_drops++)
			{
				bufptr=cmpr_body+blood_drops;
				rbuf=*(bufptr);
				
				// What an ugly compression!
				
				if (rbuf>=0 && rbuf<=127)
				{
					for (i=1;i<rbuf+2;i++)
					{
						blood_drops++;
						*((unsigned char*)(heckler->Planes[koch]+bytecount+bones*width))=*(cmpr_body+blood_drops);
						bytecount++;
					};
				};
				if (rbuf>=-127 && rbuf<=-1)
				{
					blood_drops++;
					for (i=1;i<(-rbuf)+2;i++)
					{
						*((unsigned char*)(heckler->Planes[koch]+bytecount+bones*width))=*(cmpr_body+blood_drops);
						bytecount++;
					};
				};
				if (bytecount>=width)
				{
					koch++;
					bytecount=0;
				};
				if (koch>=depth)
				{
					bones++;
					koch=0;
				};	
			};
			printf("Pooh... we sucked %d drops of blood out of the BODY.\n",blood_drops);
			printf("%d lumps of slime were in it.\n",width);
			printf("Which made %d poddles o'blood and %d bones... D'oh!\n",depth,bones);
		};
		FreeMem(bmhd,buf1);
		FreeMem(cmpr_body,buf2);
		CloseIFF(myiff);
		FreeIFF(myiff);
		Close(ifffile);
	}
	
	void Store::Bitmap2Chunky(int bm, APTR chunky)
	{
		BitMap* bitmap=this->Bitmap[bm];
		unsigned char* chunk=(unsigned char*)chunky;
		unsigned long pixels=0,pixelz=0;
		int planez=0,bitz=0;
		UBYTE pieceofcake=0;
		for (planez=0;planez<8;planez++)
		{
			for (pixels=0;pixels<(320*256)/8;pixels++)
			{
				pieceofcake=*((UBYTE*)bitmap->Planes[planez]+pixels);
				pixelz=pixels<<3;
				if (planez<=0) *(chunk+pixelz+7)+=(UBYTE)(1 & pieceofcake)>>(0-planez)
					else *(chunk+pixelz+7)+=(UBYTE)(1 & pieceofcake)<<(planez-0);
				if (planez<=1) *(chunk+pixelz+6)+=(UBYTE)(2 & pieceofcake)>>(1-planez)
					else *(chunk+pixelz+6)+=(UBYTE)(2 & pieceofcake)<<(planez-1);
				if (planez<=2) *(chunk+pixelz+5)+=(UBYTE)(4 & pieceofcake)>>(2-planez)
					else *(chunk+pixelz+5)+=(UBYTE)(4 & pieceofcake)<<(planez-2);
				if (planez<=3) *(chunk+pixelz+4)+=(UBYTE)(8 & pieceofcake)>>(3-planez)
					else *(chunk+pixelz+4)+=(UBYTE)(8 & pieceofcake)<<(planez-3);
				if (planez<=4) *(chunk+pixelz+3)+=(UBYTE)(16 & pieceofcake)>>(4-planez)
					else *(chunk+pixelz+3)+=(UBYTE)(16 & pieceofcake)<<(planez-4);
				if (planez<=5) *(chunk+pixelz+2)+=(UBYTE)(32 & pieceofcake)>>(5-planez)
					else *(chunk+pixelz+2)+=(UBYTE)(32 & pieceofcake)<<(planez-5);
				if (planez<=6) *(chunk+pixelz+1)+=(UBYTE)(64 & pieceofcake)>>(6-planez)
					else *(chunk+pixelz+1)+=(UBYTE)(64 & pieceofcake)<<(planez-6);
				if (planez<=7) *(chunk+pixelz+0)+=(UBYTE)(128 & pieceofcake)>>(7-planez)
					else *(chunk+pixelz+0)+=(UBYTE)(128 & pieceofcake)<<(planez-7);
				*((UBYTE*)bitmap->Planes[planez]+pixels)=0;
			};
			printf("\np2c: Plane %d done.",planez);
		};
		printf("\n");
	}
	
	void Store::SetUp()
	{
		NewScreen NWNewScreen=
		{
			0,0,320,256,8,
			2,1,
			0x21000,
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
		int rs=ModifyIDCMP(this->NWWindow,IDCMP_ACTIVEWINDOW|IDCMP_INACTIVEWINDOW);
		
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
		this->Chunky2=AllocMem(320*256,MEMF_FAST|MEMF_CLEAR);
		
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
		CloseWindow (this->NWWindow);
		CloseScreen (this->NWScreen);
		FreeMem (this->BMap[0],320*256);
		FreeMem (this->BMap[1],320*256);
		FreeBitMap (this->Bitmap[0]);
		FreeBitMap (this->Bitmap[1]);
		FreeMem (this->Chunky,320*256);
		FreeDBufInfo(this->DBInfo);
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
	
	unsigned char Store::CPoint(int x,int y)
	{
		return *((unsigned char*)this->Chunky+x+y*320);
	};
	
	void Store::GrabChape(int chapenum,APTR chunky,int x, int y, int x2, int y2)
	{
		int swap,xs,ys,bytez=0;
		if (x>x2) {swap=x;x=x2;x2=swap;}
		if (y>y2) {swap=y;y=y2;y2=swap;}
		
		if (Chapes[chapenum].chunk) FreeMem(Chapes[chapenum].chunk,(Chapes[chapenum].w+1)*(Chapes[chapenum].h+1));
		
		Chapes[chapenum].w=x2-x;
		Chapes[chapenum].h=y2-y;
		Chapes[chapenum].xhandle=0;
		Chapes[chapenum].yhandle=0;
		Chapes[chapenum].chunk=AllocMem((x2-x+1)*(y2-y+1),MEMF_FAST|MEMF_CLEAR);
		
		for (ys=y;ys<y2+1;ys++)
		{
			for (xs=x;xs<x2+1;xs++)
			{
				*((UBYTE *)Chapes[chapenum].chunk+bytez)=*((UBYTE*)chunky+xs+ys*320);
				bytez++;
			};
		};
	};
	
	void Store::ChunkyLine(int x1,int y1,int x2,int y2,unsigned char colour,BOOL alpha)
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
		
		unsigned char* clt=CLUT+256*colour;

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
					if (!alpha) *dest=colour
						else *dest=*(clt+*dest);
					dest+=320;
				};
				return;
			};
			if(!yDiff)
			{
				for(i=0;i<=xDiff;i++)
				{
					if (!alpha) *dest=colour
						else *dest=*(clt+*dest);
					dest+=xDirection;
				};
				return;
			};
			if(xDiff==yDiff)
			{
				for(i=0;i<=yDiff;i++)
				{
					if (!alpha) *dest=colour
						else *dest=*(clt+*dest);
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
				if (!alpha) *dest=colour
					else *dest=*(clt+*dest);
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
					if (!alpha) *dest=colour
						else *dest=*(clt+*dest);
					dest+=xDirection;
				}
				dest+=320;
			};
			for(i=0;i<endLength;i++)
			{
				if (!alpha) *dest=colour
					else *dest=*(clt+*dest);
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
				if (!alpha) *dest=colour
					else *dest=*(clt+*dest);
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
					if (!alpha) *dest=colour
						else *dest=*(clt+*dest);
					dest+=320;
				}
				dest+=xDirection;
			};

			for(i=0;i<endLength;i++)
			{
				if (!alpha) *dest=colour
					else *dest=*(clt+*dest);
				dest+=320;
			};
		};
	};
	
