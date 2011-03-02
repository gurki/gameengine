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
#include "Network.h"

Camera cam1;
Box3 box1, box2;
Grid3 grid;
Socket sock;

int main(int argc, char** argv)
{
	GameEngine.Initialize(argc, argv);

	Mouse.HideCursor();

	cam1.SetPosition(-5, 10, 10);
	cam1.SetAspectRatio(Window.GetRatio());
	box1.SetPosition(0.0, 0.5, 0.0);
	box2.SetPosition(0.0, 0.5, 5.0);
	grid.SetDimensions(20, 20);
	
	sock.Open(31415);
	
	cout << Network.GetHostAddress() << endl;
	
	GameEngine.Start();
	
	#ifdef OS_WINDOWS 
		system("PAUSE");
	#endif

	return 0;
}

void CGameEngine::Render(void) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	
	cam1.SetActive();

	Color::GetColor(ORANGE).Bind();
	box1.Render();

	Color::GetColor(AQUAMARINE).Bind();
	box2.Render();

	Color::GetColor(WHITE).Bind();
	grid.Render();

	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	box1.LookAt(box2.GetPosition());
	cam1.LookAt(box2.GetPosition());

	char data[1024];
	Address sender;

	if(sock.Receive(sender, data, sizeof(data)) > 0)
	{
		real time;
		vec3 pos;

		memcpy(&time, data, sizeof(time));
		memcpy(&pos, data + sizeof(time), sizeof(pos));

		cout << "data received \n";
		cout << "dt:  " << round(1000 * (Clock.GetRunTime() - time)) << "ms" << endl;
		cout << "pos: " << pos << endl;
		cout << endl;
	}
}

void CGameEngine::Input(void) const
{
	real dt = Clock.GetTimeDelta();

	real mov = dt * 5.0f;
	real rot = dt * 250.0f;

	if(Keyboard.KeyIsPressed('w')) box2.MoveRelative( 0, 0,-mov);
	if(Keyboard.KeyIsPressed('a')) box2.MoveRelative(-mov, 0, 0);
	if(Keyboard.KeyIsPressed('s')) box2.MoveRelative( 0, 0, mov);
	if(Keyboard.KeyIsPressed('d')) box2.MoveRelative( mov, 0, 0);

	if(Keyboard.KeyIsPressed('o')) box2.Rotate( 0,-rot, 0);
	if(Keyboard.KeyIsPressed('k')) box2.Rotate( rot, 0, 0);
	if(Keyboard.KeyIsPressed('l')) box2.Rotate( 0, rot, 0);
	if(Keyboard.KeyIsPressed('ö')) box2.Rotate(-rot, 0, 0);

	if(Keyboard.KeyWasPressed(32))
	{
		box2.SetPosition(0, 0.5, 5);
		box2.SetRotation(0, 0, 0);
	}

	if(Keyboard.KeyWasPressed('f')) Window.SetFullScreen();	
	if(Keyboard.KeyWasPressed('r'))	Window.Reset();

	if(Keyboard.KeyIsPressed('q')) cam1.Move(0, 0,-mov);
	if(Keyboard.KeyIsPressed('e')) cam1.Move(0, 0, mov);

	if(Mouse.HasMoved())
	{
		box2.Rotate(Mouse.PositionDelta().x * 0.5, 0, 0);
		Mouse.Center();
	}

	if(Mouse.ButtonWasPressed(GLUT_LEFT_BUTTON))
	{
		char data[1024];
		Address receiver("127.0.0.1", 31415);

		real time = Clock.GetRunTime();
		vec3 pos = box2.GetPosition();

		memcpy(data, &time, sizeof(time));
		memcpy(data + sizeof(time), &pos, sizeof(pos));

		if(sock.Send(receiver, data, sizeof(time) + sizeof(pos)))
		{
			cout << "data sent \n";
		}
	}
}
