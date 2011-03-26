//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidBody2.h"

RigidBody2::RigidBody2(void) : Object2()
{
	vel = vec2::Zero();
	f   = vec2::Zero();
	
	anv = 0.0;
	t   = 0.0;
	
	invm = 1.0;
	invi = 1.0;
}

void RigidBody2::ApplyForce(vec2 force, vec2 point)
{
	f += force;
	t += f.Dot(vec2(point.y,-point.x));
}

void RigidBody2::ApplyTorque(real torque)
{
	t += torque;
}

void RigidBody2::Render(void) const
{
	Object2::Render();
}

void RigidBody2::Clear(void)
{
	f = vec2::Zero();
	t = 0.0;
}

void RigidBody2::Update(real dt)
{
	pos = 0.5 * f * invm * dt * dt + vel * dt + pos;
	vel = f * invm * dt + vel;
	
	rot = 0.5 * t * invi * dt * dt + anv * dt + rot;
	anv = t * invi * dt + anv;
	
	trans.SetTranslation(pos);
	trans.SetRotation(rot);
}

