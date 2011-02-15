//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _GRID3_H
#define _GRID3_H

#include "Object3.h"
#include "Vector2.h"

class Grid3 : public Object3
{
	public:
		
		Grid3(void);
		Grid3(const vec3& position, const quat& rotation, const vec2& dimensions, const vec2& size);

		void Render(void);

	protected:

		vec2 dim;
		vec2 s;
};

#endif