//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"
#include "Camera.h"
#include "Color.h"

#include "RigidBody2.h"
#include "RigidCircle.h"
#include "RigidTriangle.h"
#include "RigidRectangle.h"
#include "RigidLine.h"

#define w 860
#define h 500

#define n 4

Camera cam[4];

Rectangle background;

RigidCircle cir;
RigidRectangle rec;
RigidTriangle tri;
RigidLine lin;

RigidBody2* obj[n];

int main (int argc, char* argv[])
{
    GameEngine.Initialize(argc, argv);
	
	Window.SetDimensions(w, h);
	
	cam[0].SetOrthographic();
	cam[1].SetOrthographic();
	cam[2].SetOrthographic();
	cam[3].SetOrthographic();
	
    cam[0].SetRelativeViewport(0.0, 0.5, 0.5, 0.5);
	cam[1].SetRelativeViewport(0.5, 0.5, 0.5, 0.5);
	cam[2].SetRelativeViewport(0.5, 0.0, 0.5, 0.5);
	cam[3].SetRelativeViewport(0.0, 0.0, 0.5, 0.5);

	cir.SetPosition(w / 4.0, h / 4.0);
	cir.SetRadius(0.05 * (w + h) / 2.0);

	rec.SetPosition(w / 4.0, h / 4.0);
	rec.SetDimensions(0.05 * (w + h), 0.05 * (w + h));
	
	tri.SetPosition(w / 4.0, h / 4.0);
	tri.SetSize(0.05 * (w + h));
	
	lin.SetPosition(w / 4.0, h / 4.0);
	lin.SetLength(0.1 * (w + h ) / 2.0);
	
	obj[0] = &cir;
	obj[1] = &rec;
	obj[2] = &tri;
	obj[3] = &lin;
	
	background.SetPosition(0, 0);
	background.SetDimensions(w + 1, h + 1);
	
	GameEngine.Start();
	
    return 0;
}

void CGameEngine::Render(void) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// camera 01
		cam[0].SetActive();
	
		Color::WithRedPurple().Bind();
		background.Render();
		Color::WithSilver().Bind();
		cir.Render();
	
	// camera 02
		cam[1].SetActive();
	
		Color::WithBlueGreen().Bind();	
		background.Render();
		
		Color::WithSilver().Bind();
		tri.Render();
	
	// camera 03
		cam[2].SetActive();
	
		Color::WithOrange().Bind();
		background.Render();		

		Color::WithSilver().Bind();
		rec.Render();
		
	// camera 04
		cam[3].SetActive();
	
		Color::WithYellowGreen().Bind();
		background.Render();
		
		Color::WithBlack().Bind();
		lin.Render();

	glutSwapBuffers();
}

void CGameEngine::Idle(void) const
{
// input
	
	if(Keyboard.KeyIsPressed('d')) 
	{
		cir.ApplyTorque(-10);	
		tri.ApplyTorque(-10);
		rec.ApplyTorque(-10);
		lin.ApplyTorque(-10);
	}
		
	if(Keyboard.KeyIsPressed('a')) 
	{
		cir.ApplyTorque( 10);	
		tri.ApplyTorque( 10);
		rec.ApplyTorque( 10);
		lin.ApplyTorque( 10);
	}
	
// physics

	const real ts = 0.01;
	static real t = 0;
	real dt = Timer.GetTimeDelta();

	t += dt;
	
	for(uint i = 0; i < n; i++)
	{
		// obj[i]->ApplyForce(vec2(0,-500));
	}
		
	while(absr(t) > ts)
	{	
		for(uint i = 0; i < n; i++)
		{
			obj[i]->Update(ts);
		}
		
		t -= sign(dt) * ts;	
	}
	
	for(uint i = 0; i < n; i++)
	{
		obj[i]->Clear();
	}
}
