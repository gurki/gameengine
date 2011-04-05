//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "Terrain.h"

Camera cam;
Grid3 grid;

Terrain terrain(10, 10);

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetPosition(-5, 10, 15);
	cam.LookAt(0, 0, 0);

	grid.SetDimensions(10, 10);

	terrain.SetHeight(10.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// start game
	GameEngine.Start();

	return 0;
}

void CGameEngine::Render(void) const
{
	cam.SetActive();
	// grid.Render();

	terrain.Render();
}

void CGameEngine::Idle(void) const
{

}

void CGameEngine::Input(void) const
{
	// terrain
	if(Keyboard.KeyWasPressed('1')) terrain.ApplyFilter(Filter::Gaussian1());
	if(Keyboard.KeyWasPressed('2')) terrain.ApplyFilter(Filter::Gaussian2());
	if(Keyboard.KeyWasPressed('3')) terrain.ApplyFilter(Filter::Gaussian3());
	if(Keyboard.KeyWasPressed('4')) terrain.ApplyFilter(Filter::Gaussian4());
	if(Keyboard.KeyWasPressed('5')) terrain.ApplyFilter(Filter::Lowpass());

	if(Keyboard.KeyWasPressed('h')) terrain.GenerateRandomHeights();

	// game
	if(Keyboard.KeyWasPressed('p')) GameEngine.TogglePause();
	if(Keyboard.KeyWasPressed('f')) Window.ToggleFullScreen();
}