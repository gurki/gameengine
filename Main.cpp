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
#include "Server.h"
#include <vector>

using namespace std;

Camera cam1;
Grid3 grid;
Socket sock;
Server server;
vector<Box3> boxes;

int main(int argc, char** argv)
{
	GameEngine.Initialize(argc, argv);

	Mouse.HideCursor();

	cam1.SetPosition(-5, 10, 10);
	cam1.LookAt(vec3(0, 0, 0));
	cam1.SetAspectRatio(Window.GetRatio());
	grid.SetDimensions(10, 10);
	
	server.Open(31415);
	sock.Open(31416);
	
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

	Color::GetColor(CHARTREUSE).Bind();
	for(uint i = 0; i < boxes.size(); i++)
	{
		boxes[i].Render();
	}

	Color::GetColor(WHITE).Bind();
	grid.Render();

	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
	server.Update();

	char data[4096];
	Address sender;

	int recv = sock.Receive(sender, data, sizeof(data));

	if(recv > 0)
	{
		uint num;
		memcpy(&num, data, sizeof(num));
				
		for(uint i = 0; i < num; i++)
		{
			Object3 obj;

			if(boxes.size() < num)
			{
				boxes.push_back(Box3());
			}
			
			memcpy(&obj, data + sizeof(num) + i * sizeof(obj), sizeof(obj));
			
			boxes[i].SetPosition(obj.GetPosition());
			boxes[i].SetRotation(obj.GetRotation());
		}
	}
}

void CGameEngine::Input(void) const
{
	Package pack;
	
	if(Keyboard.KeyIsPressed('w')) pack.w = true;
	if(Keyboard.KeyIsPressed('a')) pack.a = true;
	if(Keyboard.KeyIsPressed('s')) pack.s = true;
	if(Keyboard.KeyIsPressed('d')) pack.d = true;

	pack.dx = Mouse.PositionDelta().x * 0.5;
	Mouse.Center();

	Address server("192.168.2.103", 31415);
	sock.Send(server, &pack, sizeof(pack));

	if(Keyboard.KeyWasPressed('f')) Window.SetFullScreen();
	if(Keyboard.KeyWasPressed('r')) Window.Reset();
}
