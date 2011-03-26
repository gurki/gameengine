//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include "Vector3.h"

class Particle
{
	public:

		// constructor
		Particle(void);

		// manipulations
		void AddForce(const Vector3& force);
		void ClearForces(void);

		// setter
		void SetPosition(const Vector3& position);
		void SetVelocity(const Vector3& velocity);

		void SetMass(real mass);
		void SetInverseMass(real invmass);

		// getter
		const Vector3& GetPosition(void) const;
		const Vector3& GetVelocity(void) const;
		
		const Vector3& GetForce(void) const;

		const real GetMass(void) const;
		const real GetInverseMass(void) const;

	protected:

		// data members
		vec3 pos;
		vec3 vel;

		vec3 f;
		real invm;
};