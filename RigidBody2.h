//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object2.h"

class RigidBody2 : public virtual Object2
{
	public:
	
		RigidBody2(void);
		
		void Clear(void);
		void Update(real dt);
		
		void ApplyForce(vec2 force, vec2 point = vec2::Zero());
		void ApplyTorque(real torque);
		
		void Render(void) const;
		
	// protected:

		vec2 vel;
		vec2 f;
		
		real anv;
		real t;
		
		real invm;
		real invi;
};