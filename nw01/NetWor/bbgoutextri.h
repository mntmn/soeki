

struct Tridat
    {
       APTR TMPtr,CBPtr,FZBuf,CCTab;
       ULONG TriBright;
       ULONG rtax,rtay,rtbx,rtby,rtcx,rtcy;
		ULONG pax,pay,paz,pbx,pby,pbz,pcx,pcy,pcz;
    };

extern "Asm"
{
	void TEXTRIINIT(register APTR d0); //Adresse der Struct
	void TEXTRI();
};


