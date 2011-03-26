//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Socket.h"
#include "Types.h"
#include "Vector2.h"
#include "Object3.h"
#include <vector>

using namespace std;

class Package
{
	public:

		Package(void) : w(false), a(false), s(false), d(false), dx(0) {};

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