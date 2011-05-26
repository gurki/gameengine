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
	glMultMatrixf(modelMatrix.v);

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


vec3 Sphere::GetPointOnSurface(real u, real v, real w)
{
	vec3 r;
	
	r.x = u;
	r.y = v;
	r.z = w;
	
	r.Normalise();
	
	return r;
}

vec3 Sphere::GetPointOnSurface(real theta, real phi)
{
	vec3 r;
	
	real costheta = cosr(theta);
	
	r.x = costheta * cosr(phi);
	r.y = costheta * sinr(phi);
	r.z = sinr(theta);
	
	return r;
}

real Sphere::GetBoundingSphereRadius(void) const
{
	return radius;
}
