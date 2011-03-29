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

	frustum_ratio = 16.0 / 9.0;
	frustum_fovy = 45.0;
	frustum_near = 0.1;
	frustum_far = 1000;
}

Camera::Camera(const vec3& position) : Object3(position)
{
	projection = CAMERA_PERSPECTIVE;

	view = rect(0, 0, 1, 1);

	frustum_ratio = 16.0 / 9.0;
	frustum_fovy = 45.0;
	frustum_near = 0.1;
	frustum_far = 1000;
}

Camera::Camera(real x, real y, real z) : Object3(x, y, z)
{
	projection = CAMERA_PERSPECTIVE;

	view = rect(0, 0, 1, 1);

	frustum_ratio = 16.0 / 9.0;
	frustum_fovy = 45.0;
	frustum_near = 0.1;
	frustum_far = 1000;
}

void Camera::UpdateView(void) const
{
	AxisAngle a = ori.GetAxisAngle();

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
		glOrtho(0, d.x, 0, d.y, frustum_near, frustum_far);
		glViewport(p.x, p.y, d.x, d.y);
	}
	else 
	{
		gluPerspective(frustum_fovy, frustum_ratio, frustum_near, frustum_far);
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
	frustum_near = 0.0;

	UpdateViewport();
}

void Camera::SetFieldOfView(real fovy)
{
	this->frustum_fovy = inf(fovy, 1);
	
	UpdateViewport();
}

void Camera::SetAspectRatio(real ratio)
{
	this->frustum_ratio = ratio;

	UpdateViewport();
}

void Camera::SetNearFar(real near, real far)
{
	this->frustum_far = inf(far, 0);
	this->frustum_near = limit(near, 0, far);
	
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

void Camera::Move(const vec3& vec)
{
	pos += vec;
}

void Camera::Move(real x, real y, real z)
{
	pos += vec3(x, y, z);
}

void Camera::MoveRelative(const vec3& vec)
{
	pos += ori * vec;
}

void Camera::MoveRelative(real x, real y, real z)
{
	pos += ori * vec3(x, y, z);
}

void Camera::LookAt(const vec3& point)
{
	vec3 d = point - pos;

	real s = deg(atan2r(d.x, d.z)) + 180;
	real t = deg(asinr(d.y / d.Magnitude()));

	ori = Quaternion::WithEulerAngles(s, t, 0);
}

void Camera::LookAt(real x, real y, real z)
{
	vec3 point(x, y, z);

	vec3 d = point - pos;

	real s = deg(atan2r(d.x, d.z)) + 180;
	real t = deg(asinr(d.y / d.Magnitude()));

	ori = Quaternion::WithEulerAngles(s, t, 0);
}

void Camera::Rotate(const vec3& axis, real angle)
{
	ori *= Quaternion::WithAxisAngle(axis, angle);
}

void Camera::Rotate(real yaw, real pitch, real roll)
{
	ori *= Quaternion::WithEulerAngles(yaw, pitch, roll);
}

rect Camera::GetView(void)
{
	return view;
}

Camera* Camera::GetActiveCamera(void)
{
	return active;
}