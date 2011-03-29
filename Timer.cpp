//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Timer.h"

CTimer::CTimer(void)
{
	#ifdef OS_WINDOWS
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	#else
		Microseconds((UnsignedWide*)&start);
	#endif

	delta = 0;
	fps = 0;
	scale = 1;
}

void CTimer::Initialize(void) {}

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
		uint64 counter = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&counter);
		return (real)( (counter - start) / double(frequency) );
	#else
	    uint64 counter = 0;
		Microseconds((UnsignedWide*)&counter);
		return (real)( (counter - start) * 0.0000001 );
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