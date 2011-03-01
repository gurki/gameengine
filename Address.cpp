//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Address.h"

#include <stdio.h>

IPAddress::IPAddress(void)
{
	this->address.S_un.S_addr = (127 << 24) | (0 << 16) | (0 << 8) | 1;
}

IPAddress::IPAddress(uint address)
{
	this->address.S_un.S_addr = address;
}

IPAddress::IPAddress(char* string)
{
	this->address.S_un.S_addr = inet_addr(string);
}

IPAddress::IPAddress(uchar a, uchar b, uchar c, uchar d)
{
	this->address.S_un.S_addr = (a << 24) | (b << 16) | (c << 8) | d;
}

bool IPAddress::operator == (const IPAddress& add) const
{
	return address.S_un.S_addr == add.GetAddress();
}

bool IPAddress::operator != (const IPAddress& add) const
{
	return address.S_un.S_addr != add.GetAddress();
}

uchar IPAddress::GetA(void) const
{
	return address.S_un.S_un_b.s_b1;
}

uchar IPAddress::GetB(void) const
{
	return address.S_un.S_un_b.s_b2;
}

uchar IPAddress::GetC(void) const
{
	return address.S_un.S_un_b.s_b3;
}

uchar IPAddress::GetD(void) const
{
	return address.S_un.S_un_b.s_b4;
}

uint IPAddress::GetAddress(void) const
{
	return address.S_un.S_addr;
}

string IPAddress::GetString(void) const
{
	char ip[24] = {};

	sprintf(ip, "%i.%i.%i.%i", GetA(), GetB(), GetC(), GetD());
	
	return string(ip);
}