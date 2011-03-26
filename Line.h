//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object2.h"
#include "Color.h"

class Line : public virtual Object2
{
	public:	
		
		// constructors
		Line(void);
		Line(real x, real y, real length);
		Line(const vec2& position, real length);
		
		// methods
		void Render(void) const;
		 
		// setter
		virtual void SetLength(real length);
		
		// getter
		real GetLength(void) const;
		
	protected:
	
		real length;
		
		vec2 d[2];
};