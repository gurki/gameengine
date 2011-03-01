//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _ADDRESS_H
#define _ADDRESS_H

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
#endif

#ifdef OS_WINDOWS
	typedef int socklen_t;
#endif

#ifndef OS_WINDOWS
	
#endif

class IPAddress
{
	public:

		IPAddress(void);
		IPAddress(uint address);
		IPAddress(char* address);
		IPAddress(uchar a, uchar b, uchar c, uchar d);

		bool operator == (const IPAddress& add) const;
		bool operator != (const IPAddress& add) const;

		uchar GetA(void) const;
		uchar GetB(void) const;
		uchar GetC(void) const;
		uchar GetD(void) const;

		uint GetAddress(void) const;
	
		string GetString(void) const;

	private:

		in_addr address;
};

struct NetworkAddress
{
	IPAddress address;
	ushort port;
};

#endif