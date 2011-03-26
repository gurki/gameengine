//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Particle.h"

// constructors
Particle::Particle(void)
{
	pos = vec3::Zero();
	vel = vec3::Zero();

	f = vec3::Zero();
	invm = 1.0;
}

// manipulations
void Particle::AddForce(const Vector3& force)
{
	f += force;
}

void Particle::ClearForces(void)
{
	f = vec3::Zero();
}

// setter
void Particle::SetPosition(const Vector3& position)
{
	pos = position;
}

void Particle::SetVelocity(const Vector3& velocity)
{
	vel = velocity;
}

void Particle::SetMass(real mass)
{
	if(mass != 0.0)
	{
		invm = (real)1.0 / mass;
	}
}

void Particle::SetInverseMass(real invmass)
{
	invm = invmass;
}

// getter
const Vector3& Particle::GetPosition(void) const
{
	return pos;
}

const Vector3& Particle::GetVelocity(void) const
{
	return vel;
}
		
const Vector3& Particle::GetForce(void) const
{
	return f;
}

const real Particle::GetMass(void) const
{
	if(invm == 0.0) 
	{
		return 0.0;
	}

	return (real)1.0 / invm;
}

const real Particle::GetInverseMass(void) const
{
	return invm;
}