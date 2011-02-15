//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"
#include "Grid3.h"
#include "Box3.h"

void render(void);
void idle(void);
void input(void);

Box3 box = Box3(vec3(0, 0, 0), quat(0, 0, 0, 0), vec3(1, 1, 1));
Grid3 grid = Grid3(vec3(0, 0, 0), quat(0, 0, 0, 0), vec2(10, 10), vec2(1, 1));

int main(int argc, char* argv[])
{
	char title[11] = "GameEngine";
	
	GameEngine.Initialize(argc, argv, GAME_MODE_3D, title, 1024, 768);
	GameEngine.RegisterCallbacks(render, idle, input);

	vec3 v(1, 0, 0);
	quat q(v, rad(90));

	v.Print();
	q.Print();

	v = (q * v) * q.Conjugated();

	v.Print();

	GameEngine.Start();
	
	#ifdef _WIN32
		system("PAUSE");
	#endif

	return 0;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	

	gluLookAt(0.0, 5.0,-5.0, 
		      0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0);

	Color::GetColor(ORANGE).Bind();
	box.Render();

	Color::GetColor(WHITE).Bind();
	grid.Render();

	glutSwapBuffers();
}

void idle(void)
{

}

void input(void)
{
	vec2i d = Mouse.PositionDelta();

	box.Rotate(d.x, d.y, 0);

	if(Keyboard.KeyIsPressed('w'))
	{
		box.MoveRelative(vec3(0, 0, 0.01));
	}

	if(Keyboard.KeyIsPressed('s'))
	{
		box.MoveRelative(vec3(0, 0,-0.01));
	}

	if(Keyboard.KeyIsPressed('a'))
	{
		box.MoveRelative(vec3(0.01, 0, 0));
	}

	if(Keyboard.KeyIsPressed('d'))
	{
		box.MoveRelative(vec3(-0.01, 0, 0));
	}
}