//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody3.h"
#include "Cylinder.h"

class RigidCylinder : public RigidBody3, public Cylinder
{
	public:
		
		// construcotrs
		RigidCylinder(void);
		RigidCylinder(real x, real y, real z, real height, real radius);
		RigidCylinder(const vec3& position, real height, real radius);
	
		// methods
		void Render(void) const;	

		void UpdateMass(void);
		void UpdateInertiaTensor(void);

		// setter
		void SetHeight(real height);
		void SetRadius(real radius);
};
