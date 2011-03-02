//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _TIMER_H
#define _TIMER_H

#define Clock CTimer::GetInstance()

#include "OpenGL.h"

class CTimer
{
	public:

		void Update(void);

		real GetRunTime(void) const;
		real GetTimeDelta(void) const;

		real GetFrameRate(void) const;

	private:

		real last;
		real frame;

		real fps;

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

#endif