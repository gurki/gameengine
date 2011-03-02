//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _SERVER_H
#define _SERVER_H

#include "Socket.h"
#include "Types.h"
#include "Vector2.h"
#include "Object3.h"
#include <vector>

using namespace std;

struct Package
{
	bool w;
	bool a;
	bool s;
	bool d;

	real dx;
};

struct Player
{
	Address add;
	Object3 obj;
};

class Server : public Socket
{
	public:

		Server(void);

		void Update(void);

	private:

		vector<Player> clients;		
};

#endif