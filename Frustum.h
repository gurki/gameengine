//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _FRUSTUM_H
#define	_FRUSTUM_H

#include "Types.h"
#include "Object3.h"

class Frustum : public Object3
{
	public:
	
		Frustum(void);
		Frustum(real left, real right, real top, real bottom, real near, real far);
	
	private:
	
		real left;
		real right;

		real top;
		real bottom;

		real near;
		real far;
};

#endif