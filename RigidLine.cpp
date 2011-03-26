//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "RigidLine.h"

// constructors
RigidLine::RigidLine(void) : RigidBody2(), Line() 
{

}

RigidLine::RigidLine(real x, real y, real length) : RigidBody2(), Line(x, y, length)
{

}

RigidLine::RigidLine(const vec2& position, real length) : RigidBody2(), Line(position, length)
{

}

// methods
void RigidLine::Render(void) const
{
	Line::Render();
}