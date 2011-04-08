//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "Terrain.h"
#include "OrbitingCamera.h"

OrbitingCamera cam;
Grid3 grid;

bool bounding = false;

Terrain terrain(10, 10, 10);

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetPosition(-5, 10, 15);
	cam.LookAt(0, 0, 0);

	grid.SetDimensions(10, 10);

	terrain.SetTileSize(0.1f, 0.1f);

	Mouse.HideCursor();

	// start game
	GameEngine.Start();

	return 0;
}

void CGameEngine::Render(void) const
{
	cam.SetActive();
	// grid.Render();

	terrain.Render();
	
	if(bounding)
	{
		terrain.RenderBoundingBox();
	}
}

void CGameEngine::Idle(void) const
{

}

void CGameEngine::Input(void) const
{
	// terrain
	static real lastTime = Time.GetRunTime();
	static real dt = 0.0f;
	
	dt = Time.GetRunTime() - lastTime;

	if(dt > 0.075f)
	{
		if(Keyboard.KeyIsPressed('e')) terrain.Erode(1);
		if(Keyboard.KeyIsPressed('s')) terrain.Smooth(1);

		lastTime = Time.GetRunTime();
	}

	if(Keyboard.KeyWasPressed('b'))
	{
		if(bounding == false)
		{
			bounding = true;
		}
		else
		{
			bounding = false;
		}
	}
	if(Keyboard.KeyWasPressed('a')) terrain.SetHeight(10.0f);
	if(Keyboard.KeyWasPressed('r')) terrain.GenerateRandomTerrain();

	// game
	if(Keyboard.KeyWasPressed('p')) GameEngine.TogglePause();
	if(Keyboard.KeyWasPressed('f')) Window.ToggleFullScreen();
	
	static bool wireframe = false;

	if(Keyboard.KeyWasPressed('w'))
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
	
	// camera
	real s = Time.GetTimeDelta();

	if(Mouse.HasMoved() && Mouse.ButtonIsPressed(GLUT_LEFT_BUTTON))
	{
		cam.Orbit(Mouse.PositionDelta().x * s, -Mouse.PositionDelta().y * s);

		Mouse.Center();
	}


	static real d = cam.GetPosition().Magnitude();

	if(Mouse.HasMoved() && Mouse.ButtonIsPressed(GLUT_RIGHT_BUTTON))
	{
		d -= Mouse.PositionDelta().y * s;
		d = abs(d);

		cam.SetDistanceToTarget(d);

		Mouse.Center();
	}
}