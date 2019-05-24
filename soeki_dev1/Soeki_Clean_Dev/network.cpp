/*
	Soeki Networking
	Who knows if this will work...
	©2000 L.Hartmann/Atomatrix
*/

#include "network.h"
#include "slices.h"

const char* tokup(char* token)
{
	int dif='A'-'a';
	char tokup[5];
	strcpy(tokup,token);
	tokup[0]+=dif;
	tokup[1]+=dif;
	tokup[2]+=dif;
	tokup[3]+=dif;
	return tokup;
};

int32 server_handler(void* p)
{
	Store_NET* net=(Store_NET*)p;
	Store* nNW=net->nNW;
	
	printf ("NET.server_handler: Cogitus ergo sum.\n");
	
	net->LocalPlayer.connection->Bind(666);
	
	BNetBuffer* packetbuffer;
	uint16 len=0;
	char* token=malloc(5);
	char* nick[8];
	token[4]=0;
	uint16 id=0;
	int clients=0;
	
	while (net->online)
	{
		snooze(5000);
		if (net->LocalPlayer.connection->IsDataPending())
		{
			packetbuffer=new BNetBuffer(1024);
			net->LocalPlayer.connection->Receive(*(packetbuffer),1024);
			packetbuffer->RemoveData(&len,2);

			char* packet=(char*)malloc(len+1);
			packetbuffer->RemoveData(packet,len);
			
			delete packetbuffer;
			
			packet[len]=0;
			memcpy(token,packet,4);
			memcpy(&id,packet+4,2);
			memcpy(&len,packet+6,2);
			char* content=packet+8;
			
			/*char* debugstring=malloc(100);
			sprintf (debugstring,"CLIENT %d SENT TOKEN %s CLEN %d",id,tokup(token),len);
			nNW->OutCon(debugstring);
			free (debugstring);*/
			
			if (!strcmp(token,"helo"))
			{
				/*net->RemotePlayer[id].nickname=(char*)malloc(len+1);
				*(net->RemotePlayer[id].nickname+len)=0;
				memcpy(net->RemotePlayer[id].nickname,content,len);*/
				
				memcpy(&net->RemotePlayer[id],content,len);
				
				clients++;
				printf ("Got client #%d, his name is %s. %d total clients.\n",id,net->RemotePlayer[id].nickname,clients);
				//record[id]=0;
				char conmsg[100];
				sprintf (conmsg,"<I0>%s joined the game.",net->RemotePlayer[id].nickname);
				nNW->OutCon(conmsg);
			};
			
			if (!strcmp(token,"tell"))
			{
				printf ("TELL!\n");
				char conmsg[100];
				sprintf (conmsg,"<I0>%s: %s",net->RemotePlayer[id].nickname,content);
				nNW->OutCon(conmsg);
			};
			
			if (!strcmp(token,"addu"))
			{
				NW_Unit* newunit=malloc(sizeof (NW_Unit));
				memcpy(newunit,content,sizeof (NW_Unit));
				//printf ("SERVER: addunit: Read %d bytes into buffer.\n",res);
				
				int num=nNW->Units_Created;
				
				memcpy(&nNW->Units[num],newunit,sizeof (NW_Unit));
				memcpy(&nNW->DRUnits[num],newunit,sizeof (NW_Unit));
				nNW->Units_Created++;
				
				/*printf ("SERVER: New Unit %d!\n",num);
				printf ("        Type: %d\n",nNW->Units[num].type);
				printf ("        X   : %d\n",nNW->Units[num].x);
				printf ("        Y   : %d\n\n",nNW->Units[num].y);*/
				/*printf ("        RelX: %d\n",nNW->Units[num].relx);
				printf ("        RelY: %d\n",nNW->Units[num].rely);*/
				
				free(newunit);
			};
			
			// Complete Unit Update
			
			if (!strcmp(token,"upu0"))
			{
				NW_Unit* newunit=malloc(sizeof (NW_Unit));
				uint16 num=0;
				memcpy(&num,content,2);
				memcpy(newunit,content+2,sizeof (NW_Unit));
				memcpy(&nNW->DRUnits[num],newunit,sizeof (NW_Unit));
				free(newunit);
			};
			
			// Unit Slice 1 Update
			
			if (!strcmp(token,"upu1"))
			{
				NW_USlice_1 updslice;
				uint16 num=0;
				memcpy(&num,content,2);
				memcpy(&updslice,content+2,sizeof (NW_USlice_1));
				
				nNW->DRUnits[num].x=updslice.x;
				nNW->DRUnits[num].y=updslice.y;
				nNW->DRUnits[num].dx=updslice.dx;
				nNW->DRUnits[num].dy=updslice.dy;
				nNW->DRUnits[num].r=updslice.r;
				nNW->DRUnits[num].relx=updslice.relx;
				nNW->DRUnits[num].rely=updslice.rely;
				nNW->DRUnits[num].state=updslice.state;
				nNW->DRUnits[num].state_data=updslice.state_data;
				nNW->DRUnits[num].state_data2=updslice.state_data2;
				nNW->DRUnits[num].state_counter=updslice.state_counter;
			
				/*debugstring=malloc(100);
				sprintf (debugstring,"CLIENT %d UPDATES UNUM %d RX: %d RY: %d ROT: %d",id,num,updslice.relx,updslice.rely,updslice.r);
				nNW->OutCon(debugstring);
				free (debugstring);*/
			};
			free (packet);
		};
	};
	printf ("Connection broken!\n");
	exit(10);
};

Store_NET::Store_NET(Store* nwp)
{
	nNW=nwp;
};

bool Store_NET::ConnectTo(char* server_ip,NW_Player player)
{
	// RemotePlayer[0] is the host when on a client machine.

	memcpy(&LocalPlayer,&player,sizeof(NW_Player));

	LocalPlayer.connection=new BNetEndpoint(SOCK_DGRAM);
	LocalPlayer.connection->SetProtocol(IPPROTO_UDP);
	LocalPlayer.connection->SetNonBlocking(true);
	
	printf ("LocalPlayer.connection: %s\n",LocalPlayer.connection->ErrorStr());
	
	servtask_id=spawn_thread(server_handler,"Soeki's Ear",10,this);
	online=true;
	got_client=false;
	if (servtask_id)
	{
		resume_thread(servtask_id);
		printf ("Soeki Server thread launched.\n");
	}
	else
	{
		printf ("Oh My God!\n");
		exit(666);
	};
	
	snooze(100000);
	
	RemotePlayer[0].connection=new BNetEndpoint(SOCK_DGRAM);
	RemotePlayer[0].connection->SetProtocol(IPPROTO_UDP);
	RemotePlayer[0].connection->SetNonBlocking(true);
	RemotePlayer[0].connection->Connect(server_ip,666);
	printf ("Connected to %s.\n",server_ip);
	printf ("RemotePlayer[0].connection: %s\n",RemotePlayer[0].connection->ErrorStr());
	
	// The following piece of code adapts dynamically to the body height of the
	// Local player, so we can wrap him up nicely in the packet and send him to
	// Saudi Arabia or whatever.
	
	SendPacket("helo",(char*)&LocalPlayer,sizeof(NW_Player));
	//printf ("soeki_client: Sent nickname: %s\n",soeki_client->ErrorStr());
	return true;
};

void Store_NET::SendPacket(char* token,char* content,uint16 len)
{
	uint16 myid=LocalPlayer.id;

	char* packet=(char*)malloc(10+len);
	packet+=2;
	memcpy(packet,token,4);
	memcpy(packet+4,&myid,2);
	memcpy(packet+6,&len,2);
	memcpy(packet+8,content,len);
	packet-=2;
	len+=8;
	memcpy(packet,&len,2);
	BNetBuffer* packetbuffer=new BNetBuffer();
	packetbuffer->AppendData(packet,10+len);
	int sent=RemotePlayer[0].connection->Send(*(packetbuffer));
	free (packet);
	delete packetbuffer;
};

bool Store_NET::AddUnit(NW_Unit* newunit)
{
	SendPacket("addu",(char*)newunit,sizeof (NW_Unit));
	return true;
};

bool Store_NET::UpdateUnit(uint16 num,NW_Unit* newunit,int slice)
{
	if (!slice)
	{
		char* content=malloc(2+sizeof(NW_Unit));
		memcpy(content,&num,2);
		memcpy(content+2,newunit,sizeof (NW_Unit));
		SendPacket("upu0",content,2+sizeof(NW_Unit));
		free (content);
	}
	else
	{
		NW_USlice_1 updslice;
		
		updslice.x=newunit->x;
		updslice.y=newunit->y;
		updslice.dx=newunit->dx;
		updslice.dy=newunit->dy;
		updslice.r=newunit->r;
		updslice.relx=newunit->relx;
		updslice.rely=newunit->rely;
		updslice.state=newunit->state;
		updslice.state_data=newunit->state_data;
		updslice.state_data2=newunit->state_data2;
		updslice.state_counter=newunit->state_counter;
		
		char* content=malloc(2+sizeof(NW_USlice_1));
		memcpy(content,&num,2);
		memcpy(content+2,&updslice,sizeof (NW_USlice_1));
		SendPacket("upu1",content,2+sizeof(NW_USlice_1));
		free (content);
	};
	return true;
};

void Store_NET::Say(char* text)
{
	SendPacket("tell",text,strlen(text));
};