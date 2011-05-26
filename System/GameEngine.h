//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include "Types.h"
#include "Timer.h"

#include "OpenGL.h"
#include "Window.h"
#include "Screen.h"

#include "Mouse.h"
#include "Keyboard.h"

#include "Color.h"
#include "Camera.h"

#include "MathLib.h"
#include "PhysicsEngine.h"
// #include "TextureManager.h"

#define GameEngine CGameEngine::GetInstance()

class CGameEngine
{
	public:

		// methods
		void Initialize(int argc, char** argv);
		
		void Start(void);
		void End(void);
		void TogglePause(void);

		// getter
		bool IsPaused(void);

		// callbacks
		virtual void Idle(void) const;
		virtual void Input(void) const;
		virtual void Render(void) const;

	private:
	
		// attributes
		bool m_running;
		bool m_paused;

		// callbacks
		static void IdleFunction(void);
		static void InputFunction(void);
		static void RenderFunction(void);

	SimpleSingleton(CGameEngine);
};

#endif