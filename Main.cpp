//***************************************************************************//
// //
// Gurki Media Productions //
// (C) Tobias Gurdan //
// //
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

#define r (10)
#define n (r * r)

Camera cam1;
Grid3 grid;
Box3 box;
Particle p[n];

inline void Gravity(Particle& p)
{
	p.AddForce( vec3(0.0, -9.81 * p.GetMass(), 0.0) );
}

inline void Spring(Particle& p1, Particle& p2, real k, real b)
{
	vec3 d = p2.GetPosition() - p1.GetPosition();

	vec3 f1 = - k * d - b * p1.GetVelocity();
	vec3 f2 = k * d - b * p2.GetVelocity();

	p1.AddForce(f1);
	p2.AddForce(f2);
}

inline void Spring(Particle& p, vec3& v, real k, real b)
{
	vec3 d = p.GetPosition() - v;
	vec3 f = - k * d - b * p.GetVelocity();

	p.AddForce(f);
}

inline void Rope(Particle& p1, Particle& p2, real s)
{
	vec3 d = p2.GetPosition() - p1.GetPosition();
	real l = d.SquaredMagnitude();

	vec3 v1 = vec3::Zero();
	vec3 v2 = vec3::Zero();
	vec3 e = vec3::Zero();

	if(l > s * s)
	{
		v1 = d * (d.Dot(p1.GetVelocity()) / l);
		v2 = d * (d.Dot(p2.GetVelocity()) / l);

		e = d * 0.25 * (s * s - l) / (s * s);
	}

	// p1.SetVelocity(p1.GetVelocity() - v1);
	p1.SetPosition(p1.GetPosition() - e);

	// p2.SetVelocity(p2.GetVelocity() - v2);
	p2.SetPosition(p2.GetPosition() + e);
}

inline void Rope(Particle& p, vec3 f, real s)
{
	vec3 d = f - p.GetPosition();
	real l = d.SquaredMagnitude();

	vec3 v = vec3::Zero();
	vec3 e = vec3::Zero();

	if(l > s * s)
	{
		v = d * (d.Dot(p.GetVelocity()) / l);
		e = d * 0.25 * (s * s - l) / (s * s);
	}

	p.SetVelocity(p.GetVelocity() - v);
	p.SetPosition(p.GetPosition() - e);
}

int main(int argc, char** argv)
{
	GameEngine.Initialize(argc, argv);

	cam1.SetPosition(-5.0, 20.0, 20.0);
	cam1.LookAt(0, 0, 0);
	cam1.SetAspectRatio(Window.GetRatio());

	for(uint i = 0; i < n; i++)
	{
		p[i].SetPosition( vec3(0, 5, 0) );
	}

	grid.SetDimensions(10, 10);

	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);

	Clock.SetTimescale(2);

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
	
	glBegin(GL_POINTS);

	// boxes
	for(uint i = 0; i < n; i++)
	{
		real ratio = (real)i / (real)n;

		Color::WithHLS(ratio, 0.5, 1.0).Bind();

		glVertex3fv(p[i].GetPosition().v);
	}

	glEnd();

	// grid
	Color::WithWhite().Bind();
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

	while(absr(t) > ts)
	{
		for(uint i = 0; i < n; i++)
		{
			if(i >= r)
			{
				Gravity(p[i]);

				Rope(p[i], p[i-r].GetPosition(), 0.5);
			}

			if( (i + 1) % r != 0)
			{
				Rope(p[i], p[i + 1], 0.5);
			}
		}

		for(uint i = 0; i < n; i++)
		{
			p[i].AddForce( - 5 * p[i].GetVelocity() );
			Integrator.VelocityVerlet2(p[i], sign(dt) * ts);
		}

		for(uint i = 0; i < n; i++)
		{
			p[i].ClearForces();
		}

		t -= sign(dt) * ts;
	}

	p[0].SetVelocity( vec3::Zero() );

	if(Keyboard.KeyIsPressed('w')) { p[0].SetVelocity( 20 * vec3::Forward() ); }
	if(Keyboard.KeyIsPressed('s')) { p[0].SetVelocity( 20 * vec3::Backward() ); }
	if(Keyboard.KeyIsPressed('a')) { p[0].SetVelocity( 20 * vec3::Left() ); }
	if(Keyboard.KeyIsPressed('d')) { p[0].SetVelocity( 20 * vec3::Right() ); }
}

void CGameEngine::Input(void) const
{
	static real s = 1.0;

	if(Keyboard.KeyIsPressed('e')) { s = sup(s + 0.001, 2); Clock.SetTimescale(s); cout << s << endl; }
	if(Keyboard.KeyIsPressed('q')) { s = inf(s - 0.001,-2); Clock.SetTimescale(s); cout << s << endl; }

	if(Keyboard.KeyWasPressed('p')) GameEngine.Pause();
	if(Keyboard.KeyWasPressed('u')) GameEngine.Unpause();

	if(Keyboard.KeyWasPressed('f')) Window.SetFullScreen();
	if(Keyboard.KeyWasPressed('r')) Window.Reset();
}