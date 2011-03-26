//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidTriangle.h"

// constructors
RigidTriangle::RigidTriangle(void) : RigidBody2(), Triangle() 
{

}

RigidTriangle::RigidTriangle(real x, real y, real size) : RigidBody2(), Triangle(x, y, size)
{

}

RigidTriangle::RigidTriangle(const vec2& position, real size) : RigidBody2(), Triangle(position, size)
{

}

// methods
void RigidTriangle::Render(void) const
{
	Triangle::Render();
}