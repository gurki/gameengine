//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

Camera cam1;

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam1.SetViewport(0.0f, 0.0f, 1.0f, 1.0f);
	cam1.SetPosition(5.0f, 5.0f, 5.0f);
	cam1.LookAt(0.0f, 0.0f, 0.0f);

	// start game
	GameEngine.Start();

	system("PAUSE");
	return 0;
}

void CGameEngine::Render(void) const
{
	cam1.Enable();
    
    glBegin(GL_QUADS);
    
    glVertex3f(-1, -1, 0);
    glVertex3f( 1, -1, 0);
    glVertex3f( 1,  1, 0);
    glVertex3f(-1,  1, 0);
    
    glEnd();
}

void CGameEngine::Idle(void) const
{

}

void CGameEngine::Input(void) const
{
	static bool wireframe = false;

	if(Keyboard.KeyUp('p')) 
	{
		GameEngine.TogglePause();
	}

	if(Keyboard.KeyUp('f')) 
	{
		Window.ToggleFullScreen();
	}
	
	if(Keyboard.KeyUp('w'))
	{
		if(wireframe == false)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			wireframe = true;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			wireframe = false;
		}
	}
	
}