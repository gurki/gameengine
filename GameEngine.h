//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include "OpenGL.h"
#include "Vector2.h"
#include "Color.h"

typedef void (*func)(void);

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

		void Initialize(int argc, char** argv, unsigned int mode = GAME_MODE_3D, char* title = "Gurki Media Productions", unsigned int width = 1024, unsigned int height = 768);
		void RegisterCallbacks(func render = NULL, func idle = NULL, func input = NULL);

		void Start(void);
		void End(void);
		void Unpause(void);
		void Pause(void);

		// GAMEENGINE GETTERS

		bool IsPaused(void);

		unsigned int GetWindowWidth(void);
		unsigned int GetWindowHeight(void);
		unsigned int GetScreenWidth(void);
		unsigned int GetScreenHeight(void);

	private:

		void ClearInput(void);

		unsigned int GetGameMode(void);

		func GetIdlePointer(void);
		func GetInputPointer(void);
		func GetRenderPointer(void);

		static void IdleFunction(void);
		static void InputFunction(void);
		static void RenderFunction(void);

		static void ReshapeFunction(int x, int y);

		func m_idle;
		func m_input;
		func m_render;

		unsigned int m_mode;

		bool m_initialized;
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

		// KEYBOARD HANDL�NG

		void Initialize(void);
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

		CKeyboard(void) {};
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

		void Initialize(void);
		void ClearButtons(void);

		void Center(void);
		void HideCursor(void);
		void ShowCursor(void);

		// MOUSE SETTERS

		void SetPosition(int iPositionX, int iPositionY);

		// MOUSE GETTERS

		vec2i Position(void);
		vec2i PositionDelta(void);
		vec2i ClickEventPosition(void);

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

		vec2i m_vPosition;
		vec2i m_vPositionDelta;
		vec2i m_vClickEventPosition;

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

		CMouse(void) {};
		CMouse(CMouse const&) {};
		CMouse& operator = (CMouse const&) { return *this; };
		~CMouse(void) {};
};

#endif