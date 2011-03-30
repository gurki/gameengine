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
#include "RigidSphere.h"

Camera cam;
Grid3 grid;
RigidBox box, cube;
RigidCylinder rod;
RigidSphere sphere;

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
	
	sphere.SetRadius(2.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// start game
	GameEngine.Start();
	return 0;
}

void CGameEngine::Render(void) const
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	cam.SetActive();
	Color::WithWhite().Bind();
	grid.Render();

	// box.Render();
	// cube.Render();
	// rod.Render();
	sphere.Render();

	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	real n = Time.GetTimeDelta() * 10000;
	
	// apply forces
	vec3 torquex(n, 0.0f, 0.0f);
	vec3 torquey(0.0f, n, 0.0f);
	vec3 torquez(0.0f, 0.0f, n);

	if(Keyboard.KeyIsPressed('x'))
	{
		box.ApplyRelativeTorque(torquex);
		cube.ApplyRelativeTorque(torquex);
		rod.ApplyRelativeTorque(torquex);
		sphere.ApplyRelativeTorque(torquex);
	}

	if(Keyboard.KeyIsPressed('X'))
	{
		box.ApplyRelativeTorque(-torquex);
		cube.ApplyRelativeTorque(-torquex);
		rod.ApplyRelativeTorque(-torquex);
		sphere.ApplyRelativeTorque(-torquex);
	}
	
	if(Keyboard.KeyIsPressed('y'))	
	{
		box.ApplyRelativeTorque(torquey);
		cube.ApplyRelativeTorque(torquey);
		rod.ApplyRelativeTorque(torquey);
		sphere.ApplyRelativeTorque(torquey);
	}

	if(Keyboard.KeyIsPressed('Y'))	
	{
		box.ApplyRelativeTorque(-torquey);
		cube.ApplyRelativeTorque(-torquey);
		rod.ApplyRelativeTorque(-torquey);
		sphere.ApplyRelativeTorque(-torquey);		
	}
	
	if(Keyboard.KeyIsPressed('z'))	
	{
		box.ApplyRelativeTorque(-torquez);
		cube.ApplyRelativeTorque(-torquez);
		rod.ApplyRelativeTorque(-torquez);
		sphere.ApplyRelativeTorque(-torquez);
	}
	
	if(Keyboard.KeyIsPressed('Z'))	
	{
		box.ApplyRelativeTorque(-torquez);
		cube.ApplyRelativeTorque(-torquez);
		rod.ApplyRelativeTorque(-torquez);
		sphere.ApplyRelativeTorque(-torquez);
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
		sphere.Update(timestep);

		dt -= timestep;
	}

	box.ClearAccumulators();
	cube.ClearAccumulators();
	rod.ClearAccumulators();
	sphere.ClearAccumulators();
	
}

void CGameEngine::Input(void) const
{
	// pause game
	if(Keyboard.KeyWasPressed('u')) GameEngine.Unpause();
	if(Keyboard.KeyWasPressed('p')) GameEngine.Pause();
}