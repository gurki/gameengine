//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Camera.h"
#include "OpenGL.h"
#include "Window.h"

Camera* Camera::active = 0;

Camera::Camera(void) : Object3()
{
	projection = CAMERA_PERSPECTIVE;

	view = rect(0, 0, 1, 1);

	ratio = 16.0 / 9.0;
	fovy = 45.0;
	near = 0.1;
	far = 1000;
}

Camera::Camera(const vec3& position, const quat& rotation) : Object3(position, rotation)
{
	projection = CAMERA_PERSPECTIVE;

	view = rect(0, 0, 1, 1);

	ratio = 16.0 / 9.0;
	fovy = 45.0;
	near = 0.1;
	far = 1000;
}

void Camera::UpdateView(void) const
{
	AxisAngle a = rot.GetAxisAngle();

	glRotatef(-a.angle, a.axis.x, a.axis.y, a.axis.z);
	glTranslatef(-pos.x, -pos.y, -pos.z);
}

void Camera::SetActive(void) const
{
	active = (Camera*)this;

	UpdateViewport();
	UpdateView();
}

void Camera::UpdateViewport(void) const
{
	vec2 p;
	vec2 d;

	p.x = view.GetPosition().x * Window.GetDimensions().x; 
	p.y = view.GetPosition().y * Window.GetDimensions().y;

	d.x = view.GetDimensions().x * Window.GetDimensions().x;
	d.y = view.GetDimensions().y * Window.GetDimensions().y;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(projection == CAMERA_ORTHOGRAPHIC)
	{
		glOrtho(0, d.x, d.y, 0, near, far);
		glViewport(p.x, p.y, d.x, d.y);
	}
	else 
	{
		gluPerspective(fovy, ratio, near, far);
		glViewport(p.x, p.y, d.x, d.y);
	}

	glMatrixMode(GL_MODELVIEW);
}

void Camera::SetPerspective(void)
{
	projection = CAMERA_PERSPECTIVE;

	UpdateViewport();
}

void Camera::SetOrthographic(void)
{
	projection = CAMERA_ORTHOGRAPHIC;
	near = 0.0;

	UpdateViewport();
}

void Camera::SetFieldOfView(real fovy)
{
	this->fovy = inf(fovy, 1);
	
	UpdateViewport();
}

void Camera::SetAspectRatio(real ratio)
{
	this->ratio = ratio;

	UpdateViewport();
}

void Camera::SetNearFar(real near, real far)
{
	this->far = inf(far, 0);
	this->near = limit(near, 0, far);
	
	UpdateViewport();
}

void Camera::SetAbsoluteViewport(uint x, uint y, uint width, uint height)
{
	vec2 w = Window.GetDimensions();

	view = rect(x / w.x, y / w.y, width / w.x, height / w.y);
	
	UpdateViewport();
}

void Camera::SetRelativeViewport(real x, real y, real width, real height)
{
	view = rect(x, y, width, height);
	
	UpdateViewport();
}

rect Camera::GetView(void)
{
	return view;
}

Camera* Camera::GetActiveCamera(void)
{
	return active;
}