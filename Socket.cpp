//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Socket.h"

#include <assert.h>
#include <iostream>

using namespace std;

Socket::Socket(void)
{
	handle = 0;
}

Socket::~Socket(void)
{
	Close();
}

bool Socket::Open(unsigned short port)
{
	assert(handle == 0);

	handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
	if(handle <= 0)
	{
		cout << "Failed to create Socket" << endl;
		Close();
		return false;
	}
	
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	if(bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		cout << "Failed to bind socket" << endl;
		Close();
		return false;
	}
	
	#ifdef OS_WINDOWS
		DWORD nonBlocking = 1;
		
		if(ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
		{
			cout << "Failed to set non-blocking socket" << endl;
			Close();
			return false;
		}
	#else
		int nonBlocking = 1;
		
		if(fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
		{
			cout << "Failed to set non-blocking socket" << endl;
			Close();
			return false;
		}
	#endif

	return true;
}

void Socket::Close(void)	
{
	if(handle != 0)
	{
		#ifdef OS_WINDOWS
			closesocket(handle);
		#else
			close(handle);
		#endif

		handle = 0;
	}
}

bool Socket::IsOpen(void) const
{
	return handle != 0;
}

bool Socket::Send(const Address& destination, const void* data, int size)
{
	assert(data);
	assert(size > 0);

	if(handle == 0)
	{
		return false;
	}
			
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons(destination.GetPort());

	int sent_bytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

	return sent_bytes == size;
}

int Socket::Receive(Address& sender, void* data, int size)
{
	assert(data);
	assert(size > 0);
		
	if(handle == 0)
	{
		return false;
	}
				
	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int received_bytes = recvfrom(handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength );

	if(received_bytes <= 0)
	{
		return 0;
	}

	uint address = ntohl(from.sin_addr.s_addr);
	ushort port = ntohs(from.sin_port);

	sender = Address(address, port);

	return received_bytes;
}