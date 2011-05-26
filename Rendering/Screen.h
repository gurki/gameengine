//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "OpenGL.h"
#include "Rectangle.h"

#define Screen CScreen::GetInstance()

class CScreen : public Rectangle
{
	public:

		static CScreen& GetInstance(void)
		{
			static CScreen Singleton;
			return Singleton;
		};

	private:

		CScreen(void);
		CScreen(CScreen const&) {};
		CScreen& operator = (CScreen const&) { return *this; };
		~CScreen(void) {};
};