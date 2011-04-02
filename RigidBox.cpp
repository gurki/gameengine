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

RigidBox::RigidBox(real x, real y, real z, real width, real height, real depth) : RigidBody3(), Box(vec3(x, y, z), width, height, depth)
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
	inverseMass = 1.0 / (dim.x * dim.y * dim.z * 8.0f);
}

void RigidBox::UpdateInertiaTensor(void)
{
	real factor = 1.0f / (12.0f * inverseMass);

	real ww = dim.x * dim.x * 4.0f;
	real hh = dim.y * dim.y * 4.0f;
	real dd = dim.z * dim.z * 4.0f;

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