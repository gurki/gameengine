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

void Camera::UpdateView(void)
{
	modelMatrix.SetRotation(ori);
	modelMatrix.SetTranslation(pos);

	glMultMatrixf(modelMatrix.Inversed().v);
}

void Camera::SetActive(void)
{
	active = (Camera*)this;

	UpdateViewport();
	UpdateView();
}

void Camera::UpdateViewport(void)
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

void Camera::LookAt(const vec3& point)
{
	vec3 d = point - pos;
	d.Normalise();

	real s = atan2r(d.x, d.z) + C_PI;
	real t = asinr(d.y);

	ori = Quaternion::WithEulerAngles(s, t, 0);
}

void Camera::LookAt(real x, real y, real z)
{
	vec3 point(x, y, z);

	vec3 d = point - pos;
	d.Normalise();

	real s = atan2r(d.x, d.z) + C_PI;
	real t = asinr(d.y);

	ori = Quaternion::WithEulerAngles(s, t, 0);
}

rect Camera::GetView(void)
{
	return view;
}

Camera* Camera::GetActiveCamera(void)
{
	return active;
}