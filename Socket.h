//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _SOCKET_H
#define _SOCKET_H

#include "Address.h"

class Socket
{
	public:

		Socket(void);
		~Socket(void);

		bool Open(unsigned short port);
		void Close(void);

		bool IsOpen(void) const;

		bool Send(const Address& destination, const void* data, int size);
		int Receive(Address& sender, void* data, int size);

	private:

		int handle;
};

#endif