//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidBody3.h"
#include "Color.h"

RigidBody3::RigidBody3(void) : Object3()
{
	// primary
	linearVelocity = vec3::Zero();
	forces = vec3::Zero();
	
	angularVelocity = vec3::Zero();
	torques = vec3::Zero();

	// constant
	inverseMass = 1.0f;
	UpdateInertiaTensor();
	
	// derived
	UpdateWorldMatrix();
}

void RigidBody3::ApplyForceAtCenter(const vec3& force)
{
	forces += force;
}

void RigidBody3::ApplyForceAtBodyPoint(const vec3& force, const vec3& point)
{
	// forces += force;
	torques += force.Cross( world.GetRotation() * point );
}

void RigidBody3::ApplyTorque(const vec3& torque)
{
	torques += torque;
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
	// damping
	real linearDamping = 0.97f;
	real angularDamping = 0.97f;

	// linear movement
	vec3 temp = forces * inverseMass * dt;

	linearVelocity = temp + linearVelocity * linearDamping;
	pos = 0.5f * temp * dt + linearVelocity * dt + pos;
	
	// angular movement
	temp = torques * (world.GetRotation() * inverseInertiaTensor * world.GetRotation().Transposed()) * dt;

	angularVelocity = temp + angularVelocity * angularDamping;
	ori =  0.5 * quat(0, 0.5f * temp + angularVelocity) * ori * dt + ori;

	ori.Normalise();
	
	// update derived data
	UpdateWorldMatrix();
}

// setter
void RigidBody3::SetLinearVelocity(const vec3& velocity)
{
	linearVelocity = velocity;
}

void RigidBody3::SetAngularVelocity(const vec3& velocity)
{
	angularVelocity = velocity;
}

void RigidBody3::UpdateInertiaTensor(void)
{
	real m11 = 0.4f / inverseMass; // 2/5 m r^2 (sphere, r = 1)

	inverseInertiaTensor.SetDiagonal(m11, m11, m11);
	inverseInertiaTensor.Inverse();
}