//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "RigidBody3.h"
#include "RigidBox.h"
#include "RigidCylinder.h"
#include "RigidSphere.h"

Camera cam;
Grid3 grid;

#define k 3

RigidBox box;
RigidBox stick;
RigidCylinder rod;

RigidBody3* bodies[k];

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetPosition(-5, 10, 15);
	cam.LookAt(0, 0, 0);

	grid.SetDimensions(10, 10);

	rod.SetRadius(0.5f);
	rod.SetHeight(2.0f);
	rod.SetPosition(3.0f, 0.0f, 0.0f);

	box.SetDimensions(2.0f, 2.0f, 2.0f);
	box.SetPosition(0.0f, 0.0f, 0.0f);

	stick.SetDimensions(0.5f, 2.0f, 0.5f);
	stick.SetPosition(-3.0f, 0.0f, 0.0f);
	
	bodies[0] = &rod;
	bodies[1] = &box;
	bodies[2] = &stick;
	
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

	Color::WithGreen().Desaturate(0.5f).Bind();
	bodies[0]->Render();
	
	Color::WithOrange().Desaturate(0.5f).Bind();
	bodies[1]->Render();
	
	Color::WithYellow().Desaturate(0.5f).Bind();
	bodies[2]->Render();
	
	glutSwapBuffers();

	glEnable(GL_LIGHTING);
}

void CGameEngine::Idle(void) const
{
	real n = 10;
	
	// apply forces
	vec3 point(0.0f, 2.0f, 0.0f);
	
	if(Keyboard.KeyIsPressed('a')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque( vec3::X() * n);
	if(Keyboard.KeyIsPressed('A')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque(-vec3::X() * n);
	
	if(Keyboard.KeyIsPressed('s')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque( vec3::Y() * n);
	if(Keyboard.KeyIsPressed('S')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque(-vec3::Y() * n);

	if(Keyboard.KeyIsPressed('d')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque( vec3::Z() * n);
	if(Keyboard.KeyIsPressed('D')) for(uint i = 0; i < k; i++) bodies[i]->ApplyTorque(-vec3::Z() * n);		
	
	if(Keyboard.KeyIsPressed('q')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint( vec3::X() * n, point);
	if(Keyboard.KeyIsPressed('Q')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint(-vec3::X() * n, point);
	
	if(Keyboard.KeyIsPressed('w')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint( vec3::Y() * n, point);
	if(Keyboard.KeyIsPressed('W')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint(-vec3::Y() * n, point);

	if(Keyboard.KeyIsPressed('e')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint( vec3::Z() * n, point);
	if(Keyboard.KeyIsPressed('E')) for(uint i = 0; i < k; i++) bodies[i]->ApplyForceAtBodyPoint(-vec3::Z() * n, point);		

	// physics
	static const real timestep = 0.01f;
	static real dt = 0;
	
	dt += Time.GetTimeDelta();

	while(dt >= 0)
	{
		for(uint i = 0; i < k; i++) bodies[i]->Update(timestep);

		dt -= timestep;
	}

	for(uint i = 0; i < k; i++) bodies[i]->ClearAccumulators();
}

void CGameEngine::Input(void) const
{
	// pause game
	if(Keyboard.KeyWasPressed('u')) GameEngine.Unpause();
	if(Keyboard.KeyWasPressed('p')) GameEngine.Pause();

	if(Keyboard.KeyWasPressed('r')) 
	{
		for(uint i = 0; i < k; i++) bodies[i]->SetOrientation(0, 0, 0);
		for(uint i = 0; i < k; i++) bodies[i]->SetAngularVelocity(vec3::Zero());
	}
	
	if(Keyboard.KeyWasPressed('f')) for(uint i = 0; i < k; i++) bodies[i]->SetAngularVelocity(vec3::Zero());
}