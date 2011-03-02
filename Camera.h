//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

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
		Camera(const vec3& position, const quat& rotation);
		
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

		static const Camera* GetActiveCamera(void);
		
	private:

		static Camera* active;
		
		uint projection;

		rect view;

		real ratio;
		real fovy;
		real near;
		real far;
};

#endif