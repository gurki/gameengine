//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _SCREEN_H
#define _SCREEN_H

#include "OpenGL.h"
#include "Rectangle.h"

#define Screen CScreen::GetInstance()

class CScreen : public CRectangle
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

#endif
