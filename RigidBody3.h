//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"
#include "Matrix3x3.h"
#include "MathLib.h"

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
		void ApplyForceAtBodyPoint(const vec3& force, const vec3& point);

		void ApplyTorque(const vec3& torque);

		// setter
		void SetLinearVelocity(const vec3& velocity);
		void SetAngularVelocity(const vec3& velocity);

		void SetMass(real mass);

		// getter
		vec3 GetLinearVelocity(void) const;
		vec3 GetAngularVelocity(void) const;

		real GetInverseMass(void) const;
		mat3 GetInverseInertiaTensor(void) const;
		
	protected:

		virtual void UpdateInertiaTensor(void);

		// primary
		vec3 linearVelocity;
		vec3 forces;
		
		vec3 angularVelocity;
		vec3 torques;

		// constant
		real inverseMass;
		mat3 inverseInertiaTensor;
};