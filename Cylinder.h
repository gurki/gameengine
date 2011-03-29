//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"

class Cylinder : public virtual Object3
{
	public:

		// constructors
		Cylinder(void);
		Cylinder(const vec3& position, real height, real radius);

		// methods
		void Render(void) const;
				
		// setter
		virtual void SetHeight(real height);
		virtual void SetRadius(real radius);
		
		// getter
		real GetHeight(void) const;
		real GetRadius(void) const;

	protected:

		// variables
		real height;
		real radius;
};