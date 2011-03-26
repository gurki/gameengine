//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include "Socket.h"

#define Network CNetwork::GetInstance()

class CNetwork
{
	public:

		bool Initialize(void);

		const char* GetHostName(void) const;
		const char* GetHostAddress(void) const;

	private:

		char name[128];
		const char* address;

	public:

		static CNetwork& GetInstance(void)
		{
			static CNetwork Singleton;
			return Singleton;
		};

	private:

		CNetwork(void) {};
		CNetwork(CNetwork const&) {};
		CNetwork& operator = (CNetwork const&) { return *this; };
		~CNetwork(void);
};