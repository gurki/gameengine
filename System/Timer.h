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
#else
	#include <sys/time.h>
#endif

#define Time CTimer::GetInstance()

class CTimer
{
	public:

		// methods
		void Initialize(void);
		void Start(void);
		void Update(void);

		// getter
		real GetRunTime(void) const;
		real GetTimeDelta(void) const;
		real GetFrameRate(void) const;

		// setter
		void SetTimescale(real scale);

		// stopwatch
		void StartTimer(void);
		real GetTimerRunTime(void);

	private:
		
		#ifdef OS_WINDOWS
		    LARGE_INTEGER start;
			LARGE_INTEGER timerStart;
			LARGE_INTEGER frequency;

			real inverseFrequency;
		#else
			timeval start;
			timeval timerStart;
		#endif

		real fps;
		real delta;
		real scale;

	SimpleSingleton(CTimer);
};