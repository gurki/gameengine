//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody2.h"
#include "Circle.h"

class RigidCircle : public RigidBody2, public Circle
{
	public:
		
		// construcotrs
		RigidCircle(void);
		RigidCircle(real x, real y, real radius);
		RigidCircle(const vec2& position, real radius);
	
		// functions
		void Render(void) const;		
};
