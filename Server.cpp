//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Server.h"
#include "Timer.h"

Server::Server(void) : Socket()
{

}

void Server::Update(void)
{
	Player client;
	char data[1024];

	while(this->Receive(client.add, data, sizeof(data)) > 0)
	{
		// add client if just connected
		bool newclient = true;

		for(uint i = 0; i < clients.size(); i++)
		{
			if(clients[i].add == client.add) 
			{
				newclient = false;
				client = clients[i];
				break;
			}
		}
		
		if(newclient)
		{
			clients.push_back(client);
		}

		// process data
		Package pack;
		memcpy(&pack, data, sizeof(pack));

		real mov = Clock.GetTimeDelta() * 5.0f;

		if(pack.w) client.obj.MoveRelative(vec3::Forward() * mov);
		if(pack.a) client.obj.MoveRelative(-vec3::Right() * mov);
		if(pack.s) client.obj.MoveRelative(vec3::Right() * mov);
		if(pack.d) client.obj.MoveRelative(-vec3::Forward() * mov);

		client.obj.Rotate(pack.dx, 0, 0);
	}

	for(uint i = 0; i < clients.size(); i++)
	{
		Send(clients[i].add, &clients[i].obj, sizeof(clients[i].obj));
	}
}