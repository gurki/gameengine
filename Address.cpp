//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Address.h"

Address::Address(void)
{
	address = (127 << 24) | (0 << 16) | (0 << 8) | 1;
	port = 31415;
}

Address::Address(uint address, ushort port)
{
	this->address = address;
	this->port = port;
}

Address::Address(char* string, ushort port)
{
	this->address = ntohl(inet_addr(string));
	this->port = port;
}

Address::Address(uchar a, uchar b, uchar c, uchar d, ushort port)
{
	this->address = (a << 24) | (b << 16) | (c << 8) | d;
	this->port = port;
}

bool Address::operator == (const Address& add) const
{
	return address == add.GetAddress() && port == add.GetPort();
}

bool Address::operator != (const Address& add) const
{
	return address != add.GetAddress() || port == add.GetPort();
}

uchar Address::GetA(void) const
{
	return address >> 24;
}

uchar Address::GetB(void) const
{
	return address >> 16;
}

uchar Address::GetC(void) const
{
	return address >> 8;
}

uchar Address::GetD(void) const
{
	return address;
}

uint Address::GetAddress(void) const
{
	return address;
}

ushort Address::GetPort(void) const
{
	return port;
}

string Address::GetIPString(void) const
{
	char ip[24] = {};

	#ifdef OS_WINDOWS
		sprintf_s(ip, 24, "%i.%i.%i.%i", GetA(), GetB(), GetC(), GetD());
	#else
		snprintf(ip, 24, "%i.%i.%i.%i", GetA(), GetB(), GetC(), GetD());
	#endif
	
	return string(ip);
}
