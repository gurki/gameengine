//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

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
	
		// vector arithmetics
		vec3 operator * (const vec3& v) const;
		friend vec3 operator * (const vec3& v, const Transform3& t);
	
		// methods
		vec3 TransformFromWorldToLocal(const vec3& v) const;
		vec3 TransformFromLocalToWorld(const vec3& v) const;
		
		vec3 RotateFromLocalToWorld(const vec3& v) const;
		mat3 RotateFromLocalToWorld(const mat3& v) const;
	
		// setter
		Transform3& SetRotation(const quat& rotation);
		Transform3& SetRotationAboutAxis(const vec3& axis, real radians);
		Transform3& SetTranslation(const vec3& translation);

		// getter
		mat3 GetRotation(void) const;
		vec3 GetTranslation(void) const;
		
		// static getter
		static Transform3 With90DegreeRotationAboutX(void);
		static Transform3 With90DegreeRotationAboutY(void);
		static Transform3 With90DegreeRotationAboutZ(void);

		static Transform3 With180DegreeRotationAboutX(void);
		static Transform3 With180DegreeRotationAboutY(void);
		static Transform3 With180DegreeRotationAboutZ(void);
};

typedef Transform3 trans3;
