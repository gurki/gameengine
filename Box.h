//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"

class Box : public virtual Object3
{
	public:

		// constructors
		Box(void);
		Box(const vec3& position, const vec3& dimensions);

		// methods
		void Render(void) const;
				
		// setter
		virtual void SetDimensions(real width, real height, real depth);
		virtual void SetDimensions(const vec3& dimensions);
		
		// getter
		vec3 GetDimensions(void) const;

	protected:

		// variables
		vec3 dim;
};