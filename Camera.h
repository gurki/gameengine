//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Transform3.h"

class Camera
{
	public:
		
		// constructors
		Camera(void);

		// methods
		void Enable(void);

		void LookAt(const vec3& target);
		void LookAt(real x, real y, real z);

		// setter
		void SetPosition(real x, real y, real z);
		void SetViewport(real x, real y, real width, real height);

		// getter
		Vector3 GetPosition(void) const;

	protected:
		
		// variables
		Vector3 pos;
		Vector3 up;

		Transform3 viewMatrix;
		Transform3 projectionMatrix;

	private:

		// class variables
		bool cameraSwitch;
};

#endif