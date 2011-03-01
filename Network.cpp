//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Network.h"

#include <iostream>

using namespace std;

bool CNetwork::Initialize(void)
{
	#ifdef OS_WINDOWS
		WSADATA WSAData;

		if(WSAStartup(MAKEWORD(2, 2), &WSAData) != NO_ERROR)
		{
			cout << "Failed to initialize sockets" << endl;
			return false;
		}
	#endif

	if(gethostname(name, sizeof(name)) != 0)
	{
		cout << "Failed to get host name" << endl;
		return false;
	}

	hostent* host = gethostbyname(name); 

	if(host == 0)
	{
		cout << "Failed to get host by name" << endl;
		return false;
	}

	struct in_addr hostaddr;   
	memcpy(&hostaddr, host->h_addr, sizeof(struct in_addr));

	address = IPAddress(hostaddr.S_un.S_addr);

	return true;
}

void CNetwork::Shutdown(void)
{
	#ifdef OS_WINDOWS
		WSACleanup();
	#endif
}

const char* CNetwork::GetHostName(void) const
{
	return name;
}

IPAddress CNetwork::GetHostAddress(void) const
{
	return address;
}

