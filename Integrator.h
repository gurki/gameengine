//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include "Types.h"
#include "Object.h"

#define Integrator CIntegrator::GetInstance()

struct Derivative
{
	vec3 dp;
	vec3 dv;
};

class CIntegrator
{
	public:

		void RK4(Object& obj, real dt);
		void Euler(Object& obj, real dt);
		void Newton(Object& obj, real dt);

	private:

		Derivative f(const Object& initial, real dt, const Derivative& d);

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


#endif