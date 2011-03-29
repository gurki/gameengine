//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "RigidBox.h"
#include "RigidCylinder.h"

Camera cam;
Grid3 grid;
RigidBox box, cube;
RigidCylinder rod;

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetPosition(-5, 10, 15);
	cam.LookAt(0, 0, 0);

	grid.SetDimensions(10, 10);

	cube.SetPosition(5, 2, 0);
	cube.SetDimensions(2, 2, 2);

	box.SetPosition(-5, 2, 0);
	box.SetDimensions(3, 2, 1);

	// start game
	GameEngine.Start();
	return 0;
}

void CGameEngine::Render(void) const
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	cam.SetActive();
	grid.Render();

	box.Render();
	cube.Render();
	rod.Render();

	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	// apply forces
	static vec3 torquey(0.0f, 10.0f, 0.0f);
	static vec3 torquex(10.0f, 0.0f, 0.0f);

	if(Keyboard.KeyIsPressed('s'))
	{
		box.ApplyRelativeTorque(torquex);
		cube.ApplyRelativeTorque(torquex);
		rod.ApplyRelativeTorque(torquex);
	}

	if(Keyboard.KeyIsPressed('w'))
	{
		box.ApplyRelativeTorque(-torquex);
		cube.ApplyRelativeTorque(-torquex);
		rod.ApplyRelativeTorque(-torquex);
	}
	
	if(Keyboard.KeyIsPressed('d'))	
	{
		box.ApplyRelativeTorque(torquey);
		cube.ApplyRelativeTorque(torquey);
		rod.ApplyRelativeTorque(torquey);
	}

	if(Keyboard.KeyIsPressed('a'))	
	{
		box.ApplyRelativeTorque(-torquey);
		cube.ApplyRelativeTorque(-torquey);
		rod.ApplyRelativeTorque(-torquey);
	}
	
	// physics
	static const real timestep = 0.01f;
	static real dt = 0;
	
	dt += Time.GetTimeDelta();

	while(dt >= 0)
	{
		box.Update(timestep);
		cube.Update(timestep);
		rod.Update(timestep);

		dt -= timestep;
	}

	box.ClearAccumulators();
	cube.ClearAccumulators();
	rod.ClearAccumulators();
}

void CGameEngine::Input(void) const
{
	// pause game
	if(Keyboard.KeyWasPressed('u')) GameEngine.Unpause();
	if(Keyboard.KeyWasPressed('p')) GameEngine.Pause();
}