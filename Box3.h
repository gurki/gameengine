//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _BOX3_H
#define _BOX3_H

#include "Object.h"

class Box3 : public Object
{
	public:

		Box3(void);
		Box3(const vec3& position, const vec3& dimensions);

		void Render(void);

	protected:

		vec3 dim;
};

#endif