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
		Grid3(const vec3& position, const quat& rotation, const vec2& dimensions, const vec2& resolution);

		void SetDimensions(real x, real y);
		void SetDimensions(const vec2& dimensions);

		void SetResolution(real x, real y);
		void SetResolution(const vec2& resolution);

		void Render(void);

	protected:

		vec2 dim;
		vec2 res;
};

#endif