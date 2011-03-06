//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Timer.h"

CTimer::CTimer(void)
{
	last = GetRunTime();
	frame = last;
	fps = 0;
	scale = 1;
}

void CTimer::Update(void)
{
	real time = GetRunTime();

	frame = time - last;
	last = time;

	static real start = time;
	static uint count = 0;

	if(time - start >= 1.0)
	{
		fps = count;
		start = time;
		count = 0;
	}

	count++;
}

real CTimer::GetRunTime(void) const
{
	return glutGet(GLUT_ELAPSED_TIME) * 0.001;
}

real CTimer::GetTimeDelta(void) const
{
	return frame * scale;
}

real CTimer::GetFrameRate(void) const
{
	return fps;
}

void CTimer::SetTimescale(real scale) 
{
	this->scale = scale;
}