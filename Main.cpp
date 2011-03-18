//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"
#include "Grid3.h"
#include "Box3.h"

#include "Window.h"
#include "Camera.h"
#include "Integrator.h"
#include "Particle.h"
#include "Matrix3x3.h"

using namespace std;

#define n 9

Camera cam1;
Grid3 grid;
Box3 box;
Particle p[n];

int main(int argc, char** argv)
{
	GameEngine.Initialize(argc, argv);
	
	cam1.SetPosition(-5.0, 20.0, 20.0);
	cam1.LookAt(0, 0, 0);
	cam1.SetAspectRatio(Window.GetRatio());
	
	for(uint i = 0; i < n; i++)
	{
		// real d = (i - n/2.0) * 10 / n;
		// p[i].SetPosition( vec3(sin(d) * d, d, cos(d) * d) );
		p[i].SetPosition( vec3((i % 3) - 1.5, 3 - (i % 3), 0) );
	}
	
	grid.SetDimensions(10, 10);

	GameEngine.Start();

	#ifdef OS_WINDOWS 
		system("PAUSE");
	#endif

	return 0;
}

void CGameEngine::Render(void) const
{
	// reset
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	
	cam1.SetActive();

	Color c;
	// boxes
	for(uint i = 0; i < n; i++)
	{
		c.SetHLS((real)i / (real)n, 0.5, 1.0);
		c.Bind();

		box.SetPosition(p[i].GetPosition());
		box.Render();
	}

	// grid
	Color::GetColor(WHITE).Bind();
	grid.Render();

	// swap buffers
	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	const real ts = 0.01;
	static real t = 0;
	real dt = Clock.GetTimeDelta();

	t += dt;

	real k = 10.0;
	real b = 1.0;

	while(absr(t) > ts)
	{
		for(uint i = 0; i < n; i++)
		{
			vec3 pos1 = p[i].GetPosition();
			vec3 pos2 = p[(i+1) % n].GetPosition();
			
			// springs
			vec3 f = - k * (pos1 - pos2) - b * p[i].GetVelocity();
			
			p[i].AddForce(f);
			p[(i+1)%n].AddForce(-f);
			/*
			// gravity
			p[i].AddForce( vec3(0.0, -9.81 * p[i].GetMass(), 0.0) );
			*/
		}
	
		for(uint i = 0; i < n; i++)
		{
			Integrator.RungeKutta4(p[i], sign(dt) * ts);
		}

		for(uint i = 0; i < n; i++)
		{
			p[i].ClearForces();
		}

		for(uint i = 0; i < n; i++)
		{
			vec3 pos1 = p[i].GetPosition();
			vec3 pos2 = p[(i+1) % n].GetPosition();
	
			// rods
			Vector3 d = pos2 - pos1;

			real l = 10.0;
			real s = d.SquaredMagnitude();
			
			vec3 e = d * 0.25 * (s - l) / (s);

			p[i].SetPosition(pos1 + e);
			p[(i+1) % n].SetPosition(pos2 - e);
		}
		/*
		for(uint i = 0; i < n; i++)
		{
			vec3 pos = p[i].GetPosition();

			if(pos.y <= 0.0)
			{
				vec3 vel = p[i].GetVelocity();

				p[i].SetVelocity( vec3(vel.x, -vel.y, vel.z) );
			}
		}
		*/
		t -= sign(dt) * ts;
	}
	
	static real s = 1.0;
	
	if(Keyboard.KeyIsPressed('w')) { p[0].AddForce( 10 * vec3::Forward() ); }
	if(Keyboard.KeyIsPressed('s')) { p[0].AddForce( 10 * vec3::Backward() ); }
	
	if(Keyboard.KeyIsPressed('a')) { p[0].AddForce( 10 * vec3::Left() ); }
	if(Keyboard.KeyIsPressed('d')) { p[0].AddForce( 10 * vec3::Right() ); }
}

void CGameEngine::Input(void) const
{
	// real mov = Clock.GetTimeDelta() * 10;
	// real rot = Clock.GetTimeDelta() * 250;
	
	static real s = 1.0;
	
	if(Keyboard.KeyIsPressed('e')) { s = sup(s + 0.001, 2); Clock.SetTimescale(s); cout << s << endl; }
	if(Keyboard.KeyIsPressed('q')) { s = inf(s - 0.001,-2); Clock.SetTimescale(s); cout << s << endl; }

	if(Keyboard.KeyWasPressed('p')) GameEngine.Pause();
	if(Keyboard.KeyWasPressed('u')) GameEngine.Unpause();

	if(Keyboard.KeyWasPressed('f')) Window.SetFullScreen();
	if(Keyboard.KeyWasPressed('r')) Window.Reset();
}
