//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _TRANSFORM3_H
#define _TRANSFROM3_H

#include "MathLib.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Quaternion.h"

class Transform3 : public Matrix4x4
{
	public:
		
		// constructors
		Transform3(void);
		Transform3(const vec3& translation, const quat& rotation);
		
		// methods
		vec3 TransformFromGlobalToLocal(const vec3& v) const;
		vec3 TransformFromLocalToGlobal(const vec3& v) const;
		
		vec3 RotateFromLocalToGlobal(const vec3& v) const;
		mat3 RotateFromLocalToGlobal(const mat3& v) const;

		vec3 ProjectPerspectiveFromLocalToGlobal(const vec3& v) const;
		vec3 ProjectOrthographicFromLocalToGlobal(const vec3& v) const;
	
		// setter
		Transform3& SetRotation(const quat& rotation);
		Transform3& SetRotationAboutAxis(const vec3& axis, real radians);
		Transform3& SetRotationWithOrthogonalAxis(const vec3& right, const vec3& up, const vec3& forward);

		Transform3& SetTranslation(const vec3& translation);

		Transform3& SetPerspectiveProjection(real fov, real aspect, real near, real far);
		Transform3& SetPerspectiveProjection(real left, real right, real bottom, real top, real near, real far);
		Transform3& SetOrthographicProjection(real fov, real aspect, real near, real far);
		Transform3& SetOrthographicProjection(real left, real right, real bottom, real top, real near, real far);

		Transform3& SetLookAt(const vec3& eye, const vec3& center, const vec3& up);

		// getter
		mat3 GetRotation(void) const;
		vec3 GetTranslation(void) const;
};

typedef Transform3 trans3;

#endif