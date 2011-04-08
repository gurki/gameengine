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
	elasticity = 0.8f;
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
	torques += force.Cross( modelMatrix.RotateFromLocalToGlobal(point) );
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
	// linear movement
	vec3 temp = forces * inverseMass * dt;

	linearVelocity = temp + linearVelocity;
	pos = 0.5f * temp * dt + linearVelocity * dt + pos;
	
	// angular movement
	temp = torques * modelMatrix.RotateFromLocalToGlobal(inverseInertiaTensor) * dt;

	angularVelocity = temp + angularVelocity;
	ori =  0.5 * quat(0, 0.5f * temp + angularVelocity) * ori * dt + ori;

	ori.Normalise();
	
	// update derived data
	UpdateWorldMatrix();
}

void RigidBody3::UpdateInertiaTensor(void)
{
	real m11 = 0.4f / inverseMass; // 2/5 m r^2 (sphere, r = 1)

	inverseInertiaTensor.SetDiagonal(m11, m11, m11);
	inverseInertiaTensor.Inverse();
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

void RigidBody3::SetMass(real mass)
{
	if(mass == C_INF)
	{
		inverseMass = 0.0f;
	} 
	else 
	{
		inverseMass = 1.0f / mass;
	}

	UpdateInertiaTensor();
}

void RigidBody3::SetElasticity(real elasticity)
{
	this->elasticity = elasticity;
}

// getter
vec3 RigidBody3::GetLinearVelocity(void) const
{
	return linearVelocity;
}

vec3 RigidBody3::GetAngularVelocity(void) const
{
	return angularVelocity;
}

real RigidBody3::GetInverseMass(void) const
{
	return inverseMass;
}

mat3 RigidBody3::GetInverseInertiaTensor(void) const
{
	return inverseInertiaTensor;
}

real RigidBody3::GetBoundingSphereRadius(void) const
{
	return 0.0f;
}

real RigidBody3::GetElasticity(void) const
{
	return elasticity;
}