//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Camera.h"
#include "OpenGL.h"

Camera::Camera(void) : PivotObject3()
{

}

Camera::Camera(const vec3& position, const quat& rotation, const vec3& pivot) : PivotObject3(position, rotation, pivot)
{

}

void Camera::SetOrthographic(void)
{
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();

	glOrtho(-1, 1, -1, 1, 0, 100);
	glViewport(0, 0, 1024, 786);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
}

void Camera::SetProjective(void)
{
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();

	glOrtho(-1, 1, -1, 1, 0, 100);
	glViewport(0, 0, 1024, 786);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();	
}