//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

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
		
		void SetActive(void) const;
		void UpdateView(void) const;
		void UpdateViewport(void) const;
		
		void SetPerspective(void);
		void SetOrthographic(void);

		void SetFieldOfView(real fovy);
		void SetAspectRatio(real ratio);
		void SetNearFar(real near, real far);

		void SetAbsoluteViewport(uint x, uint y, uint width, uint height);
		void SetRelativeViewport(real x, real y, real width, real height);

		virtual void Move(const vec3& direction);
		virtual void Move(real x, real y, real z);

		virtual void MoveRelative(const vec3& direction);
		virtual void MoveRelative(real x, real y, real z);

		virtual void LookAt(const vec3& point);
		virtual void LookAt(real x, real y, real z);

		virtual void Rotate(const vec3& axis, real angle);
		virtual void Rotate(real yaw, real pitch, real roll);

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