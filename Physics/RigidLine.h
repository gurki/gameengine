//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody2.h"
#include "Line.h"

class RigidLine : public RigidBody2, public Line
{
	public:
		
		// construcotrs
		RigidLine(void);
		RigidLine(real x, real y, real length);
		RigidLine(const vec2& position, real length);
	
		// methods
		void Render(void) const;		
};