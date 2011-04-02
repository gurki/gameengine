//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "RigidBody3.h"
#include "Box.h"

class RigidBox : public RigidBody3, public Box
{
	public:
		
		// construcotrs
		RigidBox(void);
		RigidBox(real x, real y, real z, real width, real height, real depth);
	
		// methods
		void Render(void) const;	

		void UpdateMass(void);
		void UpdateInertiaTensor(void);

		// setter
		void SetDimensions(real width, real height, real depth);
};
