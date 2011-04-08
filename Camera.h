//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Object3.h"
#include "Rectangle.h"

#define CAMERA_PERSPECTIVE  1
#define CAMERA_ORTHOGRAPHIC 2

class Camera : public Object3
{
	public:
		
		Camera(void);
		Camera(const vec3& position);
		Camera(real x, real y, real z);
		
		void SetActive(void);
		virtual void UpdateView(void);
		void UpdateViewport(void);
		
		void SetPerspective(void);
		void SetOrthographic(void);

		void SetFieldOfView(real fovy);
		void SetAspectRatio(real ratio);
		void SetNearFar(real near, real far);

		void SetAbsoluteViewport(uint x, uint y, uint width, uint height);
		void SetRelativeViewport(real x, real y, real width, real height);

		virtual void LookAt(const vec3& point);
		virtual void LookAt(real x, real y, real z);
		
		rect GetView(void);
		
		static Camera* GetActiveCamera(void);
		
	private:

		static Camera* active;
		
		uint projection;

		rect view;

		real frustum_ratio;
		real frustum_fovy;
		real frustum_near;
		real frustum_far;
};

#endif