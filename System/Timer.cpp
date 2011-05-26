//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Timer.h"
#include "OpenGL.h"
#include "Log.h"

void CTimer::Initialize(void) 
{
	#ifdef OS_WINDOWS
		QueryPerformanceCounter(&start);
		QueryPerformanceFrequency(&frequency);

		inverseFrequency = 1.0 / frequency.QuadPart;
	#else
		gettimeofday(&start, NULL);
	#endif

	delta = 0;
	fps = 0;
	scale = 1;
}

void CTimer::Update(void)
{
	real curr = GetRunTime();
	
	// time between updates
	static real last = curr;

	delta = curr - last;
	last = curr;

	// framerate
	static real start = curr;
	static uint count = 0;

	count++;

	if(curr - start >= 1.0)
	{
		fps = count / (curr - start);
		start = curr;
		count = 0;
	}
}

real CTimer::GetRunTime(void) const
{
	#ifdef OS_WINDOWS
		static LARGE_INTEGER current;

		QueryPerformanceCounter(&current);

		return (current.QuadPart - start.QuadPart) * inverseFrequency;
	#else
		static timeval current;

		gettimeofday(&current, NULL);

		return (current.tv_sec * 1000000.0) + current.tv_usec - (start.tv_sec * 1000000.0) - start.tv_usec;
	#endif
}

real CTimer::GetTimeDelta(void) const
{
	return delta * scale;
}

real CTimer::GetFrameRate(void) const
{
	return fps;
}

void CTimer::SetTimescale(real scale) 
{
	this->scale = scale;
}

// stopwatch
void CTimer::StartTimer(void)
{
	#ifdef OS_WINDOWS
		QueryPerformanceCounter(&timerStart);
	#else
		gettimeofday(&timerStart, NULL);
	#endif
}

real CTimer::GetTimerRunTime(void)
{
	#ifdef OS_WINDOWS
		static LARGE_INTEGER current;

		QueryPerformanceCounter(&current);

		return (current.QuadPart - timerStart.QuadPart) * inverseFrequency;
	#else
		static timeval current;

		gettimeofday(&current, NULL);

		return (current.tv_sec * 1000000.0) + current.tv_usec - (start.tv_sec * 1000000.0) - start.tv_usec;		
	#endif
}