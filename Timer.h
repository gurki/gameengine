//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"

#ifdef OS_WINDOWS
	#include <windows.h>
#endif

#define Time CTimer::GetInstance()

class CTimer
{
	public:

		void Initialize(void);
		void Start(void);
		void Update(void);

		real GetRunTime(void) const;
		real GetTimeDelta(void) const;

		real GetFrameRate(void) const;

		void SetTimescale(real scale);

	private:
		
		#ifdef OS_WINDOWS
		    uint64 start;
			uint64 frequency;
		#endif

		real fps;
		real delta;
		real scale;

	public:

		static CTimer& GetInstance(void)
		{
			static CTimer Singleton;
			return Singleton;
		};

	private:

		CTimer(void);
		CTimer(CTimer const&) {};
		CTimer& operator = (CTimer const&) { return *this; };
		~CTimer(void) {};
};