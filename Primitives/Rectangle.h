//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object2.h"
#include "Color.h"

class Rectangle : public virtual Object2
{
	public:

		// constructors
		Rectangle(void);
		Rectangle(real x, real y, real width, real height);
		Rectangle(const vec2& position, const vec2& dimensions);
		
		// methods
		void Render(void) const;
		
		// setter
		virtual void SetDimensions(real width, real height);
		virtual void SetDimensions(const vec2& dimensions);
		
		// getter
		vec2 GetDimensions(void) const;
		vec2 GetCenter(void) const;
		real GetRatio(void) const;

	protected:
	
		// variables
		vec2 dim;
		
		vec2 d[4];
};