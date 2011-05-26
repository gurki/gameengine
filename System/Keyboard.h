//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "Log.h"
#include "Types.h"
#include "OpenGL.h"

#include <stdlib.h>

#define Keyboard CKeyboard::GetInstance()

class CKeyboard
{
	public:

		// methods
		void Update(void);
		
		// getter
		bool KeyUp(uchar key);
		bool KeyHold(uchar key);
		bool KeyDown(uchar key);
		
		// structs
		struct Keys
		{
			static const int F1       = 257;
			static const int F2       = 258;
			static const int F3       = 259;
			static const int F4       = 260;
			static const int F5       = 261;
			static const int F6       = 262;
			static const int F7       = 263;
			static const int F8       = 264;
			static const int F9       = 265;
			static const int F10      = 266;
			static const int F11      = 267;
			static const int F12      = 268;
			
			static const int Left     = 269;
			static const int Up       = 270;
			static const int Right    = 271;
			static const int Down     = 272;
			
			static const int PageUp   = 273;
			static const int PageDown = 274;
			
			static const int Home      = 275;
			static const int End       = 276;
			static const int Insert    = 277;
			/*
			static const int Alt       = 278;
			static const int Shift     = 279;
			static const int Control   = 280;
			*/
			static const int Enter     = 13;
			static const int Escape    = 27;
			static const int Backspace = 8;
			static const int Tab       = 9;
			static const int Space     = 32;
		} 
		static Keys;

	private:

		// attributes 
		
		//	 0...255 ASCII
		// 256...277 Special Keys 
		// 278...288 Modifiers
		
		static bool keyUp[288];
		static bool keyHold[288];
		static bool keyDown[288];
		
		// methods 
		static int KeyFromSpecial(int key);
		static void UpdateModifiers(void);

		// callbacks
		static void KeyboardFunction(unsigned char key, int x, int y); 
		static void KeyboardUpFunction(unsigned char key, int x, int y);
		static void SpecialFunction(int key, int x, int y); 
		static void SpecialUpFunction(int key, int x, int y);

	Singleton(CKeyboard);
};

#endif