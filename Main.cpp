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

using namespace std;

Camera cam1;
Grid3 grid;
Box3 box1, box2, box3;

void clibrary(const double angle, double& s, double& c)
{
	s = sin(angle);
	c = cos(angle);
}

void tangcon(const double angle, double& s, double& c)
{
	double z = tan(angle * 0.5);

	s = 2 * z / (1 + z * z);
	c = (1 - z * z) / (1 + z * z);
}

void trigid(const double angle, double& s, double& c)
{
	int sign = (angle - C_PIDIV2 < C_PI ? 1 : -1);

	s = sin(angle);
	c = sqrt(1 - s * s);
}

int main(int argc, char** argv)
{
	/*
	GameEngine.Initialize(argc, argv);
	
	cam1.SetPosition(-5.0, 10.0, 10.0);
	cam1.LookAt(0, 0, 0);
	cam1.SetAspectRatio(Window.GetRatio());
	
	box1.pos = vec3(5.0, 0.5,-1.5);
	box2.pos = vec3(5.0, 0.5, 0.0);
	box3.pos = vec3(5.0, 0.5, 1.5);

	grid.SetDimensions(10, 10);
	*/
	int i = 0;
	double angle = 0;
	
	double s = 0;
	double c = 0;

	const int n = 360 * 100000;

	real t0, t1, t2, t3;
	
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); clibrary(angle, s, c); } t1 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); tangcon(angle, s, c); }  t2 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); trigid(angle, s, c); }   t3 = Clock.GetRunTime() - t0;

	cout << "clib: " << t1 << endl;
	cout << "tang: " << t2 << endl;
	cout << "trig: " << t3 << endl;
	cout << endl;

	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); tangcon(angle, s, c); }  t2 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); trigid(angle, s, c); }   t3 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); clibrary(angle, s, c); } t1 = Clock.GetRunTime() - t0;

	cout << "clib: " << t1 << endl;
	cout << "tang: " << t2 << endl;
	cout << "trig: " << t3 << endl;
	cout << endl;
	
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); trigid(angle, s, c); }   t3 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); clibrary(angle, s, c); } t1 = Clock.GetRunTime() - t0;
	t0 = Clock.GetRunTime(); for(int i = 0; i < n; i++) { angle = rad(i); tangcon(angle, s, c); }  t2 = Clock.GetRunTime() - t0;

	cout << "clib: " << t1 << endl;
	cout << "tang: " << t2 << endl;
	cout << "trig: " << t3 << endl;
	cout << endl;

	// GameEngine.Start();

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

	// boxes
	Color::GetColor(GREEN).Bind();
	box1.Render();

	Color::GetColor(ORANGE).Bind();
	box2.Render();
	
	Color::GetColor(PURPLE).Bind();
	box3.Render();

	// grid
	Color::GetColor(WHITE).Bind();
	grid.Render();

	// swap buffers
	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	real k = 10.0;
	real b = 1.0;

	box1.f = - k * (box1.pos - vec3(0, box1.pos.y, box1.pos.z)) - b * box1.vel;
	box2.f = - k * (box2.pos - vec3(0, box2.pos.y, box2.pos.z)) - b * box2.vel;
	box3.f = - k * (box3.pos - vec3(0, box3.pos.y, box3.pos.z)) - b * box3.vel;

	real dt = Clock.GetTimeDelta();

	Integrator.RK4((Object&)box1, dt);
	Integrator.Euler((Object&)box2, dt);
	Integrator.Newton((Object&)box3, dt);
}

void CGameEngine::Input(void) const
{
	real mov = Clock.GetTimeDelta() * 10;
	real rot = Clock.GetTimeDelta() * 250;
	
	static real s = 1.0;

	if(Keyboard.KeyIsPressed('w')) { s+= 0.001; Clock.SetTimescale(s); }
	if(Keyboard.KeyIsPressed('s')) { s-= 0.001; Clock.SetTimescale(s); }

	if(Keyboard.KeyIsPressed('x')) box3.rot *= quat::WithRotationAboutX(rot);
	if(Keyboard.KeyIsPressed('y')) box3.rot *= quat::WithRotationAboutY(rot);
	if(Keyboard.KeyIsPressed('z')) box3.rot *= quat::WithRotationAboutZ(rot);

	if(Keyboard.KeyWasPressed('f')) Window.SetFullScreen();
	if(Keyboard.KeyWasPressed('r')) Window.Reset();
}
