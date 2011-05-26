//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody2.h"
#include "Rectangle.h"

class RigidRectangle : public RigidBody2, public Rectangle
{
	public:
		
		// construcotrs
		RigidRectangle(void);
		RigidRectangle(real x, real y, real width, real height);
		RigidRectangle(const vec2& position, const vec2& dimensions);
	
		// methods
		void Render(void) const;		
};
