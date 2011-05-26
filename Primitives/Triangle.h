//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object2.h"
#include "Color.h"

class Triangle : public virtual Object2
{
	public:	
		
		// constructors
		Triangle(void);
		Triangle(real x, real y, real size);
		Triangle(const vec2& position, real size);
		
		// methods
		void Render(void) const;
		 
		// setter
		virtual void SetSize(real size);
		
		// getter
		real GetSize(void) const;
		
	protected:
	
		real size;
		
		vec2 d[3];
};