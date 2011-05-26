//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidRectangle.h"

// constructors
RigidRectangle::RigidRectangle(void) : RigidBody2(), Rectangle() 
{

}

RigidRectangle::RigidRectangle(real x, real y, real width, real height) : RigidBody2(), Rectangle(x, y, width, height)
{

}

RigidRectangle::RigidRectangle(const vec2& position, const vec2& dimensions) : RigidBody2(), Rectangle(position, dimensions)
{

}

// methods
void RigidRectangle::Render(void) const
{
	Rectangle::Render();
}