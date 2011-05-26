//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Camera.h"

// constructors
Camera::Camera(void)
{
	pos = vec3(0.0f, 0.0f, 0.0f);
	up = Vector3::Up();

	SetPerspectiveProjection(rad(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	LookAt(0.0f, 0.0f, 0.0f);
}

// methods
void Camera::Enable(void)
{
	vec2 window = Window.GetDimensions();
	
	glViewport(viewport.x * window.x, viewport.y * window.y, viewport.width * window.x, viewport.height * window.y);

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

void Camera::SetPerspectiveProjection(real fov, real aspect, real min, real max)
{
	frustum.fov = limit(fov, 0, 270);
	frustum.aspect = aspect;
	frustum.min = min;
	frustum.max = max;

	projectionMatrix.SetPerspectiveProjection(frustum.fov, frustum.aspect, frustum.min, frustum.max);
}

void Camera::SetOrthographicProjection(real fov, real aspect, real min, real max)
{
	frustum.fov = limit(fov, 0, 270);
	frustum.aspect = aspect;
	frustum.min = min;
	frustum.max = max;

	projectionMatrix.SetOrthographicProjection(frustum.fov, frustum.aspect, frustum.min, frustum.max);
}

void Camera::SetViewport(real x, real y, real width, real height)
{
	viewport.x = x;
	viewport.y = y;
	viewport.width = width;
	viewport.height = height;
	
	if(projection == Perspective)
	{
		SetPerspectiveProjection(frustum.fov, (width / height) * Window.GetRatio(), frustum.min, frustum.max);
	}
	else
	{
		SetOrthographicProjection(frustum.fov, (width / height) * Window.GetRatio(), frustum.min, frustum.max);
	}
}

// getter
Vector3 Camera::GetPosition(void) const
{
	return pos;
}

void Camera::FirstPersonControl(void)
{
	if(Keyboard.KeyHold('w'))
	{

	}
}
/*
    real fov = 2.0f * arctan ((top - bottom) * 0.5f / near)
	real aspect = width / height;

	real near = 0.0f;
	real far = 1000.0f;

	real top = tanr(rad(fov) * 0.5f) * near;
	real bottom = -top;

	real left = aspect * bottom;
	real right = aspect * top;
*/