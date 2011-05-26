//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _MOUSE_H
#define _MOUSE_H

#include "Types.h"
#include "OpenGL.h"
#include "Window.h"
#include "Vector2.h"

#define Mouse CMouse::GetInstance()

class CMouse
{
	public:

		// methods
		void Update(void);
		void Center(void);

		void HideCursor(void) const;
		void ShowCursor(void) const;

		// setter
		void SetPosition(int x, int y);

		// getter
		vec2 GetPosition(void) const;
		vec2 GetPositionDelta(void) const;

		bool HasMoved(void) const;
	
		bool ButtonUp(const int button) const;
		bool ButtonDown(const int button) const;
		bool ButtonHold(const int button) const;

		// structs
		struct Buttons
		{
			static const int Left      = 0;
			static const int Middle    = 1;
			static const int Right     = 2;
			static const int WheelUp   = 3;
			static const int WheelDown = 4;
		}
		static Buttons;

	private:

		// attributes
		vec2 position;
		vec2 lastPosition;
		
		static bool buttonUp[4];
		static bool buttonDown[4];
		static bool buttonHold[4];

		// methods (private)
		void UpdatePosition(int x, int y);

		// callbacks
		static void EntryFunction(int state);
		static void MotionFunction(int x, int y);
	    static void PassiveMotionFunction(int x, int y);
		static void MouseFunction(int button, int state, int  x, int y);

	Singleton(CMouse);
};

#endif