//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "OpenGL.h"
#include "Vector2.h"
#include "Color.h"
#include "Window.h"
#include "Timer.h"

#include "Types.h"

enum GAME_MODES
{
	GAME_MODE_2D,
	GAME_MODE_3D
};

//***************************************************************************//
//                            The GameEngine Class                           //
//***************************************************************************//

#define GameEngine CGameEngine::GetInstance()

class CGameEngine
{
	public:

		// GAMEENGINE HANDLING

		void Initialize(int argc, char** argv);
		
		void Start(void);
		void End(void);
		void Unpause(void);
		void Pause(void);

		// GAMEENGINE GETTERS

		bool IsPaused(void);

		virtual void Idle(void) const;
		virtual void Render(void) const;
		virtual void Input(void) const;

	private:

		void ClearInput(void);
		
		static void IdleFunction(void);
		static void InputFunction(void);
		static void RenderFunction(void);

		bool m_running;
		bool m_paused;

	// GAMEENGINE SINGLETON

	public:

		static CGameEngine& GetInstance(void)
		{
			static CGameEngine Singleton;
			return Singleton;
		};

	private:

		CGameEngine(void) {};
		CGameEngine(CGameEngine const&) {};
		CGameEngine& operator = (CGameEngine const&) { return *this; };
		~CGameEngine(void) {};
};

//***************************************************************************//
//                             The Keyboard Class                            //
//***************************************************************************//

#define Keyboard CKeyboard::GetInstance()

class CKeyboard
{
	public:

		// KEYBOARD HANDLÌNG

		void ClearKeys(void);

		// KEYBOARD GETTERS

		bool ShiftIsPressed(void);
		bool CtrlIsPressed(void);
		bool AltIsPressed(void);
		bool KeyIsPressed(unsigned char ucKey);
		bool KeyWasPressed(unsigned char ucKey);

	private:

		// KEYBOARD CALLBACKS

		static void KeyboardFunc(unsigned char key, int x, int y); 
		static void KeyboardUpFunc(unsigned char key, int x, int y);
		static void SpecialFunc(int key, int x, int y); 
		static void SpecialUpFunc(int key, int x, int y);

		void UpdateModifiers(void);
		void SpecialKeyPress(int key, int x, int y, int state);
		void NormalKeyPress(unsigned char key, int x, int y, int state);

		bool m_bShiftIsPressed;
		bool m_bCtrlIsPressed;
		bool m_bAltIsPressed;
		bool m_bKeyIsPressed[256];
		bool m_bKeyWasPressed[256];

		unsigned char m_ucKeyBuffer;

	// KEYBOARD SINGLETON
			
	public:

		static CKeyboard& GetInstance(void)
		{
			static CKeyboard Singleton;
			return Singleton;
		}

	private:

		CKeyboard(void);
		CKeyboard(CKeyboard const&) {};
		CKeyboard& operator = (CKeyboard const&) { return *this; };
		~CKeyboard(void) {};
};

//***************************************************************************//
//                              The Mouse Class                              //
//***************************************************************************//

#define Mouse CMouse::GetInstance()

enum MOUSE_BUTTONS
{
	BUTTON_LEFT,
	BUTTON_MIDDLE,
	BUTTON_RIGHT
};

class CMouse
{
	public:

		// MOUSE HANDLING

		void ClearButtons(void);

		void Center(void);
		void HideCursor(void);
		void ShowCursor(void);

		// MOUSE SETTERS

		void SetPosition(int iPositionX, int iPositionY);

		// MOUSE GETTERS

		vec2 Position(void);
		vec2 PositionDelta(void);
		vec2 ClickEventPosition(void);

		bool HasMoved(void);
		bool CursorIsVisible(void);
		bool ButtonIsPressed(int iButton);
		bool ButtonWasPressed(int iButton);

	private:

		// MOUSE CALLBACKS

		static void EntryFunc(int state);
		static void MotionFunc(int x, int y);
	    static void PassiveMotionFunc(int x, int y);
		static void MouseFunc(int button, int state, int  x, int y);

		void UpdatePosition(int x, int y);
		void Click(int button, int state, int x, int y);

		vec2 m_vPosition;
		vec2 m_vPositionDelta;
		vec2 m_vClickEventPosition;

		bool m_bHasMoved;
		bool m_bCursorIsVisible;
		bool m_bButtonIsPressed[7];
		bool m_bButtonWasPressed[7];

		unsigned int m_uiButtonBuffer;

	// MOUSE SINGLETON

	public:

		static CMouse& GetInstance(void)
		{
			static CMouse Singleton;
			return Singleton;
		}

	private:

		CMouse(void);
		CMouse(CMouse const&) {};
		CMouse& operator = (CMouse const&) { return *this; };
		~CMouse(void) {};
};