//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Gravity.h"

// constructors
Gravity::Gravity(void)
{
	g = vec3(0.0f,-9.81f, 0.0f);
}

Gravity::Gravity(const vec3& gravity)
{
	SetGravity(gravity);
}

// methods
void Gravity::ApplyForce(RigidBody3* rigidBody)
{
	rigidBody->ApplyForceAtCenter(g / rigidBody->GetInverseMass());
}

// setter
void Gravity::SetGravity(const vec3& gravity)
{
	g = gravity;
}

// getter
vec3 Gravity::GetGravity(void) const
{
	return g;
}