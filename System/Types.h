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

#ifdef OS_WINDOWS
	#define VC_EXTRALEAN 
	#define WIN32_LEAN_AND_MEAN
#endif

// structs
struct Alignments
{
	static const short unsigned int Left   = 0;
	static const short unsigned int Top    = 1;
	static const short unsigned int Center = 2;
	static const short unsigned int Bottom = 3;
	static const short unsigned int Right  = 4;
};

// typedefs
#ifdef OS_WINDOWS
	typedef __int64          int64;
	typedef unsigned __int64 uint64;
#else
	// typedef UInt64 uint64;
#endif

#ifdef DOUBLE_PRECISSION
	typedef double real;
#else
	typedef float real;
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

typedef void (*func)(void);

// templates
#define Singleton(name) public:                                               \
							                                                  \
							static name& GetInstance(void)                    \
							{                                                 \
							    static name Singleton;                        \
							    return Singleton;                             \
							};                                                \
							                                                  \
						private:                                              \
							                                                  \
							name(void);                                       \
							name(name const&) {};                             \
							name& operator = (name const&) { return *this; }; \
							~name(void)

#define SimpleSingleton(name) public:                                               \
							                                                        \
							      static name& GetInstance(void)                    \
							      {                                                 \
								      static name Singleton;                        \
								      return Singleton;                             \
							      };                                                \
							                                                        \
						      private:                                              \
							                                                        \
							      name(void) {};                                    \
								  name(name const&) {};                             \
							      name& operator = (name const&) { return *this; }; \
							      ~name(void) {}