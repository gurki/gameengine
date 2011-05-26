//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"

class Sphere : public virtual Object3
{
	public:

		// constructors
		Sphere(void);
		Sphere(const vec3& position, real radius);

		// methods
		void Render(void) const;
				
		// setter
		virtual void SetRadius(real radius);
		
		// getter
		real GetRadius(void) const;
		real GetBoundingSphereRadius(void) const;

		static vec3 GetPointOnSurface(real u, real v, real w);
		static vec3 GetPointOnSurface(real theta, real phi);

	protected:

		// variables
		real radius;
};