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
		virtual void UpdateView(void);
		virtual void Orbit(real latitude, real longitude);

		// setter
		void SetTarget(const vec3& targetPosition);
		void SetDistanceToTarget(real distance);
		virtual void SetOrbit(real latitude, real longitude);

	protected:	

		vec3 target;
};

#endif