//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidBody3.h"

RigidBody3::RigidBody3(void) : Object3()
{
	// primary
	linearVelocity = vec3::Zero();
	forces = vec3::Zero();
	
	angularVelocity = vec3::Zero();
	torques = vec3::Zero();

	// constant
	inverseMass = 1.0f;
	inverseInertiaTensor.SetDiagonal(0.4f, 0.4f, 0.4f);
	inverseInertiaTensor.Inverse();
	
	// derived
	UpdateWorldMatrix();
}

void RigidBody3::ApplyForceAtCenter(const vec3& force)
{
	forces += force;
}

void RigidBody3::ApplyRelativeForce(const vec3& force, const vec3& point)
{
	forces += force;
	torques += force.Cross(ori * point);
}

void RigidBody3::ApplyTorque(const vec3& torque)
{
	torques += torque;
}

void RigidBody3::ApplyRelativeTorque(const vec3& torque)
{
	torques += ori * torque;
}

void RigidBody3::Render(void) const
{
	Object3::Render();
}

void RigidBody3::ClearAccumulators(void)
{
	forces = vec3::Zero();
	torques = vec3::Zero();
}

void RigidBody3::Update(real dt)
{
	// linear movement
	vec3 temp = forces * inverseMass * dt;

	linearVelocity = temp + linearVelocity;
	pos = 0.5f * temp * dt + linearVelocity * dt + pos;
	
	// angular movement
	temp = torques * world.GetRotation() * inverseInertiaTensor * dt;

	angularVelocity = temp + angularVelocity;
	ori =  0.5 * quat(0, 0.5f * temp + angularVelocity) * ori * dt + ori;

	ori.Normalise();
	
	// update derived data
	UpdateWorldMatrix();
}