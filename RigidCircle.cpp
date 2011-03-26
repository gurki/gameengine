//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidCircle.h"

// construcotrs
RigidCircle::RigidCircle(void) : RigidBody2(), Circle()
{

}

RigidCircle::RigidCircle(real x, real y, real radius) : RigidBody2(), Circle(x, y, radius)
{

}

RigidCircle::RigidCircle(const vec2& position, real radius) : RigidBody2(), Circle(position, radius)
{

}

// functions
void RigidCircle::Render(void) const
{
	Circle::Render();
}		
