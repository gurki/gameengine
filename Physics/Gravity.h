//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _GRAVITY_H
#define _GRAVITY_H

#include "GlobalForceGenerator.h"
#include "Vector3.h"

class Gravity : public GlobalForceGenerator
{
	public:

		// constructors
		Gravity(void);
		Gravity(const vec3& gravity);

		// methods
		void ApplyForce(RigidBody3* rigidBody);

		// setter
		void SetGravity(const vec3& gravity);
		
		// getter
		vec3 GetGravity(void) const;
		
	protected:

		// variables
		vec3 g;
};

#endif