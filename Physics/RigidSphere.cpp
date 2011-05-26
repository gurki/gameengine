//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidSphere.h"

// constructors
RigidSphere::RigidSphere(void) : RigidBody3(), Sphere() 
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidSphere::RigidSphere(real x, real y, real z, real radius) : RigidBody3(), Sphere(vec3(x, y, z), radius)
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidSphere::RigidSphere(const vec3& position, real radius) : RigidBody3(), Sphere(position, radius)
{
	UpdateMass();
	UpdateInertiaTensor();
}

// methods
void RigidSphere::Render(void) const
{
	Sphere::Render();
}

void RigidSphere::UpdateMass(void)
{
	inverseMass = 3.0 / (4.0 * C_PI * radius * radius * radius); // 4/3 Pi r^3
}

void RigidSphere::UpdateInertiaTensor(void)
{
	real m11 = (radius * radius * 2.0f) / (5.0f * inverseMass); // 2/5 m r^2

	inverseInertiaTensor.SetDiagonal(m11, m11, m11);
	inverseInertiaTensor.Inverse();
}

// setter
void RigidSphere::SetRadius(real radius)
{
	Sphere::SetRadius(radius);
	
	UpdateMass();
	UpdateInertiaTensor();
}