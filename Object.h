//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _OBJECT_H
#define _OBJECT_H

#include "Types.h"
#include "Vector3.h"
#include "Quaternion.h"

class Object
{
	public:

		Object(void);

	// protected:

		vec3 pos;
		vec3 vel;

		vec3 f;
		real invm;
	
		quat rot;
		quat ang;

		vec3 t;
		real invi;
};

#endif