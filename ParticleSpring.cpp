//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "ParticleSpring.h"

// construcotrs
ParticleSpring::ParticleSpring(void) : Spring()
{

}
	
ParticleSpring::ParticleSpring(real l, real k, real b, RigidBody3* anchor1, RigidBody3* anchor2) : Spring(l, k, b)
{
	anchors[0] = anchor1;
	anchors[1] = anchor2;
}

// methods
void ParticleSpring::ApplyForce(void)
{
	vec3 d = anchors[1]->GetPosition() - anchors[0]->GetPosition();
	real s = d.Magnitude();

	vec3 v = anchors[1]->GetLinearVelocity() - anchors[0]->GetLinearVelocity();
	
	d /= s;

	vec3 f = d * (k * (l - s) - b * d.Dot(v));

	anchors[0]->ApplyForceAtCenter(-f);
	anchors[1]->ApplyForceAtCenter( f);
}

// getter
real ParticleSpring::GetCurrentLength(void) const
{
	vec3 d = anchors[1]->GetPosition() - anchors[0]->GetPosition();

	return d.Magnitude();
}