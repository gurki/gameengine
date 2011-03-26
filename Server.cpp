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
		
		uint i = 0;

		for(i; i < clients.size(); i++)
		{
			if(clients[i].add == client.add) 
			{
				newclient = false;
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

		if(pack.w) clients[i].obj.MoveRelative(vec3::Forward() * mov);
		if(pack.a) clients[i].obj.MoveRelative(-vec3::Right() * mov);
		if(pack.s) clients[i].obj.MoveRelative(-vec3::Forward() * mov);
		if(pack.d) clients[i].obj.MoveRelative(vec3::Right() * mov);

		clients[i].obj.Rotate(pack.dx, 0, 0);
	}
	
	// send data
	char out[4069];

	uint num = clients.size();
	memcpy(out, &num, sizeof(uint));

	for(uint i = 0; i < clients.size(); i++)
	{
		memcpy(out + sizeof(uint) + i * sizeof(Object3), &clients[i].obj, sizeof(Object3));
	}
		
	for(uint i = 0; i < clients.size(); i++)
	{
		Send(clients[i].add, &out, sizeof(uint) + sizeof(Object3) * clients.size());
	}
}