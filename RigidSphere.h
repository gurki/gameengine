//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody3.h"
#include "Sphere.h"

class RigidSphere : public RigidBody3, public Sphere
{
	public:
		
		// construcotrs
		RigidSphere(void);
		RigidSphere(real x, real y, real z, real radius);
		RigidSphere(const vec3& position, real radius);
	
		// methods
		void Render(void) const;	

		void UpdateMass(void);
		void UpdateInertiaTensor(void);

		// setter
		void SetRadius(real radius);
};