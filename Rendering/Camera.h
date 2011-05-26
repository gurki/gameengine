//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _CAMERA_H
#define _CAMERA_H

#include "OpenGL.h"
#include "Window.h"

#include "Transform3.h"
#include "PhysicsEngine.h"

#include "Mouse.h"
#include "Keyboard.h"

enum Projection
{
	Perspective,
	Orthographic
};

struct Frustum
{
	real fov;
	real aspect;

	real min;
	real max;
};

struct Viewport
{
	real x;
	real y;

	real width;
	real height;
};

class Camera
{
	public:
		
		// constructors
		Camera(void);

		// methods
		void Enable(void);

		void LookAt(const vec3& target);
		void LookAt(real x, real y, real z);

		void FirstPersonControl(void);

		// setter
		void SetPosition(real x, real y, real z);
		void SetViewport(real x, real y, real width, real height);
		void SetPerspectiveProjection(real fov, real aspect, real min, real max);
		void SetOrthographicProjection(real fov, real aspect, real min, real max);

		// getter
		Vector3 GetPosition(void) const;

	protected:
		
		// variables
		Vector3 pos;
		Vector3 up;

		Frustum frustum;
		Viewport viewport;
		Projection projection;

		Transform3 viewMatrix;
		Transform3 projectionMatrix;

	private:

		// class variables
		bool cameraSwitch;
};

#endif