//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Window.h"
#include "Camera.h"

CWindow::CWindow(void)
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

void CWindow::Initialize(void) {}

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

void CWindow::SetFullScreen(void)
{
	SetDimensions(Screen.GetDimensions());
	glutFullScreen();
}

void CWindow::Reset(void)
{
	SetDimensions(Screen.GetDimensions() * 0.64);
	Center();
}

void CWindow::Center(void)
{
	SetPosition(Screen.GetCenter() - dim * 0.5);
}

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

const char* CWindow::GetTitle(void) const
{
	return title.c_str();
}