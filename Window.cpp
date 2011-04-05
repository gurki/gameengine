//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Window.h"
#include "Camera.h"

// constructors
CWindow::CWindow(void) : Rectangle()
{
	dim = Screen.GetDimensions() * 0.64;
	pos = Screen.GetCenter() - dim * 0.5;
	title = "Gurki Media Productions";

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(dim.x, dim.y);
	glutInitWindowPosition(pos.x, pos.y);
	glutCreateWindow(title.c_str());
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glutReshapeFunc(Reshape);
}

// methods
void CWindow::Initialize(void) {}

void CWindow::ToggleFullScreen(void)
{
	if(fullscreen == false)
	{
		SetDimensions(Screen.GetDimensions());
		glutFullScreen();

		fullscreen = true;
	}
	else
	{
		SetDimensions(Screen.GetDimensions() * 0.64);
		Center();

		fullscreen = false;
	}
}

void CWindow::Center(void)
{
	SetPosition(Screen.GetCenter() - dim * 0.5);
}

// setter
void CWindow::SetPosition(const vec2& position)
{
	pos = position;

	glutPositionWindow(pos.x, pos.y);
}

void CWindow::SetPosition(real x, real y)
{
	pos = vec2(x, y);

	glutPositionWindow(pos.x, pos.y);
}

void CWindow::SetDimensions(const vec2& dimensions)
{
	dim = dimensions;

	glutReshapeWindow(dim.x, dim.y);
}

void CWindow::SetDimensions(real width, real height)
{
	dim = vec2(width, height);

	glutReshapeWindow(dim.x, dim.y);
}

void CWindow::SetTitle(const char* title)
{
	this->title = title;

	glutSetWindowTitle(title);
}

// getter
const char* CWindow::GetTitle(void) const
{
	return title.c_str();
}

// private methods
void CWindow::Reshape(int width, int height)
{
	if(height == 0) 
	{
		height = 1;
	}

	Window.SetDimensions(width, height);

	if(Camera::GetActiveCamera() != 0)
	{
		Camera::GetActiveCamera()->UpdateViewport();
	}
}