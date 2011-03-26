//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Object3.h"

class Box3 : public Object3
{
	public:

		Box3(void);
		Box3(const vec3& position, const vec3& dimensions);

		void Render(void);

	protected:

		vec3 dim;
};

#pragma once