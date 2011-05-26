//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidCylinder.h"

// constructors
RigidCylinder::RigidCylinder(void) : RigidBody3(), Cylinder() 
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidCylinder::RigidCylinder(real x, real y, real z, real height, real radius) : RigidBody3(), Cylinder(vec3(x, y, z), height, radius)
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidCylinder::RigidCylinder(const vec3& position, real height, real radius) : RigidBody3(), Cylinder(position, height, radius)
{
	UpdateMass();
	UpdateInertiaTensor();
}

// methods
void RigidCylinder::Render(void) const
{
	Cylinder::Render();
}

void RigidCylinder::UpdateMass(void)
{
	inverseMass = 1.0 / (C_2PI * radius * radius * height); // 1 / (pi r^2 h)
}

void RigidCylinder::UpdateInertiaTensor(void)
{
	real factor = 1.0f / (12.0f * inverseMass);

	real rr = radius * radius;
	real hh = height * height * 4.0f;

	real m11 = factor * (3.0f * rr + hh);
	real m22 = 0.5f * rr / inverseMass;

	inverseInertiaTensor.SetDiagonal(m11, m22, m11);
	inverseInertiaTensor.Inverse();
}

// setter
void RigidCylinder::SetHeight(real height)
{
	Cylinder::SetHeight(height);
	
	UpdateMass();
	UpdateInertiaTensor();
}

void RigidCylinder::SetRadius(real radius)
{
	Cylinder::SetRadius(radius);
	
	UpdateMass();
	UpdateInertiaTensor();
}