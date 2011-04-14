//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "OrbitingCamera.h"
#include "Sphere.h"

// methods
void OrbitingCamera::Orbit(real latitude, real longitude)
{
	vec3 d = pos - target;
	d.y = 0;
	real r = d.Magnitude();
	
	d /= r;
	/*
	real theta = acosr(d.z);
	real phi = atan2r(d.x, d.y); 
	*/
	static real phi = 0;
	static real theta = 0.0f;

	phi += longitude;
	theta += latitude;

	d.x = r * cosr(theta) * cosr(phi);
	d.y = 10; // r * cosr(theta) * sinr(phi);
	d.z = r * sinr(theta);

	pos = target + d;

	LookAt(target.x, target.y, target.z);
}

// setter
void OrbitingCamera::SetTarget(const vec3& target)
{
	this->target = target;

	LookAt(target.x, target.y, target.z);
}