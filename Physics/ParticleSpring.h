//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _PARTICLESPRING_H
#define _PARTICLESPRING_H

#include "Spring.h"
#include "RigidBody3.h"

class ParticleSpring : public Spring
{
	public:
		
		// constructors
		ParticleSpring(void);
		ParticleSpring(real l, real k, real b, RigidBody3* anchor1, RigidBody3* anchor2);

		// methods
		void ApplyForce(void);

		// getter
		real GetCurrentLength(void) const;

	protected:

		// variables
		RigidBody3* anchors[2];
};

#endif