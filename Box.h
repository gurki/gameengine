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
		Box(const vec3& position, real width, real height, real depth);

		// methods
		void Render(void) const;
				
		// setter
		virtual void SetDimensions(real width, real height, real depth);
		
		// getter
		vec3 GetDimensions(void) const;

		real GetBoundingSphereRadius(void) const;

	protected:

		// variables
		vec3 dim;
};