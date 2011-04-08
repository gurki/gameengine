//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "OrbitingCamera.h"
#include "Sphere.h"

// methods
void OrbitingCamera::UpdateView(void)
{
	gluLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, 0.0f, 1.0f, 0.0f);
}

void OrbitingCamera::Orbit(real latitude, real longitude)
{
	vec3 d = pos - target;
	
	quat rot = quat::WithEulerAngles(latitude, longitude, 0.0f);

	d = d * rot;

	pos = target + d;
}

// setter
void OrbitingCamera::SetTarget(const vec3& targetPosition)
{
	target = targetPosition;
}

void OrbitingCamera::SetDistanceToTarget(real distance)
{
	vec3 d = pos - target;

	d.Normalise();

	pos = target + distance * d;
}

void OrbitingCamera::SetOrbit(real latitude, real longitude)
{
	pos = target + (target - pos).Magnitude() * Sphere::GetPointOnSurface(latitude, longitude);
}