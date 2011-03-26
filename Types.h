//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

// platform
#if defined(_WIN32)
	#define OS_WINDOWS
#elif defined(__APPLE__)
	#define OS_MAC
#else
	#define OS_UNIX
#endif

// typedefs
typedef float real;

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

typedef void (*func)(void);
