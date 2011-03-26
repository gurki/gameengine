//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include "Particle.h"

#define Integrator CIntegrator::GetInstance()

struct Derivative
{
	vec3 dp;
	vec3 dv;
};

class CIntegrator
{
	public:

		void RungeKutta4(Particle& obj, real dt);
		void Euler1(Particle& obj, real dt);
		void SymplecticEuler1(Particle& obj, real dt);
		void Newton1(Particle& obj, real dt);
		void Leapfrog2(Particle& obj, real dt);
		void VelocityVerlet2(Particle& obj, real dt);
		void VelocityLessVerlet2(Particle& obj, real dt);

	private:

		Derivative f(const Particle& initial, real dt, const Derivative& d);

	public:

		static CIntegrator& GetInstance(void)
		{
			static CIntegrator Singleton;
			return Singleton;
		};

	private:

		CIntegrator(void) {};
		CIntegrator(CIntegrator const&) {} ;
		CIntegrator& operator = (CIntegrator const&) { return *this; };
		~CIntegrator(void) {};
};