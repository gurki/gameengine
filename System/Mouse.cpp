//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Mouse.h"

bool CMouse::buttonUp[4];
bool CMouse::buttonDown[4];
bool CMouse::buttonHold[4];

// constructors
CMouse::CMouse(void)
{
	glutMouseFunc(CMouse::MouseFunction);
	glutEntryFunc(CMouse::EntryFunction);
	glutMotionFunc(CMouse::MotionFunction);
	glutPassiveMotionFunc(CMouse::PassiveMotionFunction);

	this->Center();
}

CMouse::~CMouse(void) {};
 
// methods
void CMouse::Update(void)
{
	memset(buttonDown, 0, sizeof(buttonDown));
	memset(buttonUp, 0, sizeof(buttonUp));
}

void CMouse::Center(void)
{
	vec2 p = Window.GetCenter();

	this->SetPosition(p.x, p.y);
}

void CMouse::HideCursor(void) const
{
	glutSetCursor(GLUT_CURSOR_NONE);
}

void CMouse::ShowCursor(void) const
{
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

// setter
void CMouse::SetPosition(int x, int y)
{
	lastPosition = position;

	position.x = x;
	position.y = y;

	glutWarpPointer(position.x, position.y);
}

// getter
vec2 CMouse::GetPosition(void) const
{
	return position;
}

vec2 CMouse::GetPositionDelta(void) const
{
	return position - lastPosition;
}

bool CMouse::HasMoved(void) const
{
	return lastPosition != position;
}

bool CMouse::ButtonUp(const int button) const
{
	return buttonUp[button];
}

bool CMouse::ButtonDown(const int button) const
{
	return buttonDown[button];
}

bool CMouse::ButtonHold(const int button) const
{
	return buttonHold[button];
}

// methods (private)
void CMouse::UpdatePosition(int x, int y)
{
	lastPosition = position;

	position.x = x;
	position.y = y;
}

// callbacks
void CMouse::EntryFunction(int state)
{
	if(state == GLUT_LEFT)
	{
		memset(buttonHold, 0, sizeof(buttonHold));
	}
}

void CMouse::MotionFunction(int x, int y) 
{
	CMouse::GetInstance().UpdatePosition(x, y);
}

void CMouse::PassiveMotionFunction(int x, int y)
{
	CMouse::GetInstance().UpdatePosition(x, y);
}

void CMouse::MouseFunction(int button, int state, int  x, int y) 
{
	if(state == GLUT_DOWN)
	{
		buttonDown[button] = true;
		buttonHold[button] = true;
	}
	else if(state == GLUT_UP)
	{
		buttonUp[button] = true;
		buttonHold[button] = false;
	}

	CMouse::GetInstance().UpdatePosition(x, y);
}