//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Camera.h"
#include "OpenGL.h"

// constructors
Camera::Camera(void)
{
	pos = vec3(-5.0f, 10.0f, 15.0f);
	up = Vector3::Up();

	real fov = rad(45.0f);
	real aspect = 16.0f / 9.0f;

	real near = 1.0f;
	real far = 1000.0f;

	real top = tanr(rad(fov) * 0.5f) * near;
    real bottom = -top;

    real left = aspect * bottom;
    real right = aspect * top;

	projectionMatrix.SetPerspectiveProjection(fov, aspect, near, far);
	LookAt(0.0f, 0.0f, 0.0f);
}

// methods
void Camera::Enable(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(projectionMatrix.v);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(viewMatrix.v);
}

void Camera::LookAt(const vec3& target)
{
	viewMatrix.SetLookAt(pos, target, up);
}

void Camera::LookAt(real x, real y, real z)
{
	viewMatrix.SetLookAt(pos, vec3(x, y, z), up);
}

// setter
void Camera::SetPosition(real x, real y, real z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Camera::SetViewport(real x, real y, real width, real height)
{
	glViewport(x, y, width, height);
}

// getter
Vector3 Camera::GetPosition(void) const
{
	return pos;
}

/*
    fov*0.5 = arctan ((top-bottom)*0.5 / near)

    top = tan(fov*0.5) * near
    bottom = -top

    left = aspect * bottom
    right = aspect * top
*/