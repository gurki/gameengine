//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidBox.h"

// constructors
RigidBox::RigidBox(void) : RigidBody3(), Box() 
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidBox::RigidBox(real x, real y, real z, real width, real height, real depth) : RigidBody3(), Box(vec3(x, y, z), vec3(width, height, depth))
{
	UpdateMass();
	UpdateInertiaTensor();
}

RigidBox::RigidBox(const vec3& position, const vec3& dimensions) : RigidBody3(), Box(position, dimensions)
{
	UpdateMass();
	UpdateInertiaTensor();
}

// methods
void RigidBox::Render(void) const
{
	Box::Render();
}

void RigidBox::UpdateMass(void)
{
	inverseMass = 1.0 / (dim.x * dim.y * dim.z);
}

void RigidBox::UpdateInertiaTensor(void)
{
	real factor = 1.0f / (12.0f * inverseMass);

	real ww = dim.x * dim.x;
	real hh = dim.y * dim.y;
	real dd = dim.z * dim.z;

	real m11 = factor * (hh + dd);
	real m22 = factor * (dd + ww);
	real m33 = factor * (ww + hh);

	inverseInertiaTensor.SetDiagonal(m11, m22, m33);
	inverseInertiaTensor.Inverse();
}

// setter
void RigidBox::SetDimensions(real width, real height, real depth)
{
	Box::SetDimensions(width, height, depth);

	UpdateMass();
	UpdateInertiaTensor();
}

void RigidBox::SetDimensions(const vec3& dimensions)
{
	Box::SetDimensions(dimensions);

	UpdateMass();
	UpdateInertiaTensor();
}