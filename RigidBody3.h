//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"
#include "Matrix3x3.h"

class RigidBody3 : public virtual Object3
{
	public:
	
		// constructors
		RigidBody3(void);
		
		// methods
		void Render(void) const;

		void Update(real dt);
		void ClearAccumulators(void);

		// apply physics
		void ApplyForceAtCenter(const vec3& force);
		void ApplyRelativeForce(const vec3& force, const vec3& point);

		void ApplyTorque(const vec3& torque);
		void ApplyRelativeTorque(const vec3& torque);
		
	protected:

		virtual void UpdateInertiaTensor(void) = 0;

		// primary
		vec3 linearVelocity;
		vec3 forces;
		
		vec3 angularVelocity;
		vec3 torques;

		// constant
		real inverseMass;
		mat3 inverseInertiaTensor;
		
		// derived
		mat3 inverseWorldInertiaTensor;
};