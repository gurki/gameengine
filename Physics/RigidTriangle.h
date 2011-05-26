//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody2.h"
#include "Triangle.h"

class RigidTriangle : public RigidBody2, public Triangle
{
	public:
		
		// construcotrs
		RigidTriangle(void);
		RigidTriangle(real x, real y, real size);
		RigidTriangle(const vec2& position, real size);
	
		// methods
		void Render(void) const;		
};