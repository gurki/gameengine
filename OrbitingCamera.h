//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _ORBITINGCAMERA_H
#define _ORBITINGCAMERA_H

#include "Camera.h"

class OrbitingCamera : public Camera
{
	public:

		// methods
		void Orbit(real azimuth, real inclination);

		// setter
		void SetTarget(const vec3& target);

	protected:

		// variables
		vec3 target;
};

#endif