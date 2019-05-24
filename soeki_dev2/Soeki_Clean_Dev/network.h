
#ifndef SOEKI_NETWORK
#define SOEKI_NETWORK

#include <NetworkKit.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "independent/structures.h"
#include "platform/beos/master.h"

class Store_NET
{
	public:
		Store_NET(Store* nwp);
		
		Store* nNW;
		
		//thread_id servtask_id;
		
		bool ConnectTo(char* server_ip, struct NW_Player player);
		void SendPacket(char* token,char* content,uint16 len);
		bool AddUnit(NW_Unit* newunit);
		bool UpdateUnit(uint16 num,NW_Unit* newunit,int slice);
		void Say(char* text);
		
		bool online;
		bool got_client;
		bool is_busy;
		
		//BNetEndpoint* soeki_server;
		//BNetEndpoint* soeki_client;

		struct NW_Player LocalPlayer;
		struct NW_Player RemotePlayer[7];
};

#endif
