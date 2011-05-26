//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

// constructors
void CGameEngine::Initialize(int argc, char** argv)
{
	Time.Initialize();

	glutInit(&argc, argv);

	Window.Initialize();
	// TextureManager.Initialize();

	m_paused = false;
	m_running = false;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glPointSize(5.0f);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// methods
void CGameEngine::Start(void)
{
	if(m_running == false)
	{
		m_running = true;
		
		glutIdleFunc(IdleFunction);
		glutDisplayFunc(RenderFunction);

		glutMainLoop();
	}
}

void CGameEngine::End(void)
{
	exit(EXIT_SUCCESS);
}

void CGameEngine::TogglePause(void)
{
	if(m_paused == true)
	{
		m_paused = false;
	}
	else
	{
		m_paused = true;
	}
}

// gette
bool CGameEngine::IsPaused(void)
{
	return m_paused;
}

// callbacks
void CGameEngine::IdleFunction(void)
{
	Time.Update();
	InputFunction();

	if(GameEngine.IsPaused() == false)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		PhysicsEngine.Update();
		GameEngine.Idle();
		GameEngine.Render();

		glutSwapBuffers();
	}

	Keyboard.Update();
	Mouse.Update();
}

void CGameEngine::InputFunction(void)
{
	if(Keyboard.KeyUp(Keyboard.Keys.Escape)) 
	{
		GameEngine.End();
	}

	GameEngine.Input();
}

void CGameEngine::RenderFunction(void)
{
	if(GameEngine.IsPaused() == false)
	{
		GameEngine.Render();
	}
}