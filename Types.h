//***************************************************************************//
//                                                                           //
//                          Gurki Media PCylindeructions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

// platform
#if defined(_WIN32)
	#define OS_WINDOWS
	#define VC_EXTRALEAN 
	#define WIN32_LEAN_AND_MEAN
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

#ifdef OS_WINDOWS
	typedef unsigned __int64 uint64;
#elif
	typedef UInt64 uint64;
#endif

typedef void (*func)(void);
