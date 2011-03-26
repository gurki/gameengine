//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"

#include <string>

using namespace std;

#ifdef OS_WINDOWS
	#include <winsock2.h>
	#pragma comment (lib, "wsock32.lib")
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	#include <fcntl.h>
	#include <netdb.h>
#endif

#ifdef OS_WINDOWS
	typedef int socklen_t;
#endif

class Address
{
	public:

		Address(void);
		Address(uint address, ushort port);
		Address(char* address, ushort port);
		Address(uchar a, uchar b, uchar c, uchar d, ushort port);

		bool operator == (const Address& add) const;
		bool operator != (const Address& add) const;

		uchar GetA(void) const;
		uchar GetB(void) const;
		uchar GetC(void) const;
		uchar GetD(void) const;

		uint GetAddress(void) const;

		ushort GetPort(void) const;
	
		string GetIPString(void) const;

	private:

		uint address;
		ushort port;
};
