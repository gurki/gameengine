//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _BOX3_H
#define _BOX3_H

#include "Object3.h"

class Box3 : public Object3
{
	public:

		Box3(void);
		Box3(const vec3& position, const quat& rotation, const vec3& dimensions);

		void Render(void);

	protected:

		vec3 dim;
};

#endif