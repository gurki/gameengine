//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "PhysicsEngine.h"

Camera cam;
Grid3 grid;

RigidSphere sphere1, sphere2, sphere3;

ParticleSpring spring1, spring2;
Gravity gravity;

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetPosition(-5, 10, 15);
	cam.LookAt(0, 0, 0);

	grid.SetDimensions(10, 10);

	sphere1.SetPosition(-2, 0, 0);
	sphere2.SetPosition(2, 0, 0);
	sphere3.SetPosition(0, 0, 2);
	
	spring1 = ParticleSpring(2.0f, 10.0f, 1.0f, &sphere1, &sphere2);
	spring2 = ParticleSpring(2.0f, 10.0f, 1.0f, &sphere2, &sphere3);

	gravity = Gravity();

	PhysicsEngine.AddRigidBody(&sphere1);
	PhysicsEngine.AddRigidBody(&sphere2);
	PhysicsEngine.AddRigidBody(&sphere3);

	PhysicsEngine.AddForceGenerator(&spring1);
	PhysicsEngine.AddForceGenerator(&spring2);

	// PhysicsEngine.AddGlobalForceGenerator(&gravity);
	
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// start game
	GameEngine.Start();

	return 0;
}

void CGameEngine::Render(void) const
{
	cam.SetActive();

	Color::WithWhite().Bind();
	grid.Render();
	
	PhysicsEngine.RenderRigidBodies();
}

void CGameEngine::Idle(void) const
{

}

void CGameEngine::Input(void) const
{
	// physics
	const uint k = PhysicsEngine.GetNumberOfRigidBodies();

	real n = 10;
	vec3 point = vec3(0, 1, 0);
	
	// apply forces
	if(Keyboard.KeyIsPressed('a')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque( vec3::X() * n);
	if(Keyboard.KeyIsPressed('A')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque(-vec3::X() * n);
	
	if(Keyboard.KeyIsPressed('s')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque( vec3::Y() * n);
	if(Keyboard.KeyIsPressed('S')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque(-vec3::Y() * n);

	if(Keyboard.KeyIsPressed('d')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque( vec3::Z() * n);
	if(Keyboard.KeyIsPressed('D')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyTorque(-vec3::Z() * n);		
	
	if(Keyboard.KeyIsPressed('q')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint( vec3::X() * n, point);
	if(Keyboard.KeyIsPressed('Q')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint(-vec3::X() * n, point);
	
	if(Keyboard.KeyIsPressed('w')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint( vec3::Y() * n, point);
	if(Keyboard.KeyIsPressed('W')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint(-vec3::Y() * n, point);

	if(Keyboard.KeyIsPressed('e')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint( vec3::Z() * n, point);
	if(Keyboard.KeyIsPressed('E')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->ApplyForceAtBodyPoint(-vec3::Z() * n, point);		

	// reset
	if(Keyboard.KeyWasPressed('r')) 
	{
		for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->SetPosition(0, 0, 0);
		for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->SetOrientation(0, 0, 0);
		for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->SetAngularVelocity(vec3::Zero());
	}
	
	if(Keyboard.KeyWasPressed('f')) for(uint i = 0; i < k; i++) PhysicsEngine.GetRigidBody(i)->SetAngularVelocity(vec3::Zero());

	// game
	if(Keyboard.KeyWasPressed('p')) GameEngine.TogglePause();
}