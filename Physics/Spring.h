//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _SPRING_H
#define _SPRING_H

#include "ForceGenerator.h"
#include "MathLib.h"

class Spring : public ForceGenerator
{
	public:

		// constructors
		Spring(void);
		Spring(real l, real k, real b);

		// setter
		void SetDamping(real b);
		void SetStiffness(real k);
		void SetRestLength(real l);

		// getter
		real GetDamping(void) const;
		real GetStiffness(void) const;
		real GetRestLength(void) const;

		virtual real GetCurrentLength(void) const = 0;

	protected:

		// variables
		real k;
		real b;
		real l;
};

#endif