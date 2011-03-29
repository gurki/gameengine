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
		vec3 FromWorldToLocal(const vec3& v) const;
		vec3 FromLocalToWorld(const vec3& v) const;
	
		// setter
		Transform3& SetRotation(const quat& rotation);
		Transform3& SetTranslation(const vec3& translation);

		// getter
		mat3 GetRotation(void) const;
		vec3 GetTranslation(void) const;
};

typedef Transform3 trans3;
