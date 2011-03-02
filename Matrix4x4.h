//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _MATRIX4X4_H
#define _MATRIX4X4_H

#include "Types.h"
#include "Quaternion.h"

class Matrix4x4
{
	Matrix4x4(void);
	Matrix4x4(const real* v);

	static Matrix4x4 FromObjectToInertialQuaternion(const Quaternion& quat);
	static Matrix4x4 FromInertialToObjectQuaternion(const Quaternion& quat);

	union
	{
		real v[16];
		struct { real m11, m12, m13, m14;
		         real m21, m22, m23, m24;
				 real m31, m32, m33, m34;
				 real m41, m42, m43, m44; };
	};
};

typedef Matrix4x4 mat4;

#endif