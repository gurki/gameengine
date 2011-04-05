//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Sphere.h"
#include "Color.h"
#include "Transform2.h"
#include "Vector2.h"

Sphere::Sphere(void) : Object3()
{
	SetRadius(0.5f);
}

Sphere::Sphere(const vec3& position, real radius) : Object3(position)
{
	SetRadius(radius);
}

void Sphere::Render(void) const
{
	material.Bind();

	glPushMatrix();
	glMultMatrixf(world.v);

	glutSolidSphere(radius, 20, 20);

	glPopMatrix();
}

void Sphere::SetRadius(real radius)
{
	this->radius = inf(radius, 0);
}
		
// getter
real Sphere::GetRadius(void) const
{
	return radius;
}


vec3 Sphere::GetPointOnSurface(real u, real v, real w) const
{
	vec3 r(u, v, w);
	
	r.Normalise() * radius;
	
	return r;
}

vec3 Sphere::GetPointOnSurface(real theta, real phi) const
{
	vec3 r;
	
	real costheta = cosr(theta);
	
	r.x = costheta * cosr(phi);
	r.y = costheta * sinr(phi);
	r.z = sinr(theta);
	
	return r * radius;
}

real Sphere::GetBoundingSphereRadius(void) const
{
	return radius;
}
