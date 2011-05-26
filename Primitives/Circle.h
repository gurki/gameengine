//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object2.h"
#include "MathLib.h"
#include "Color.h"

class Circle : public virtual Object2
{
	public:

		// constructors
		Circle(void);
		Circle(real x, real y, real radius);
		Circle(const vec2& position, real radius);
		
		// methods
		void Render(void) const;
		
		// setter
		virtual void SetRadius(real radius);
		
		// getter
		real GetRadius(void) const;
		
	protected:
	
		// variables
		real radius;
};