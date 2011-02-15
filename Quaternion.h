//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "Types.h"
#include "Vector3.h"

class Quaternion
{
	public:

		Quaternion(void);
		Quaternion(const real* v);
		Quaternion(real x, real y, real z, real w);
		Quaternion(const vec3& axis, real angle);
		Quaternion(real yaw, real pitch, real roll);
		 
		bool operator == (const Quaternion& quat);
		bool operator != (const Quaternion& quat);

		Quaternion operator * (const Quaternion& quat);
		vec3 operator * (const vec3& vec);

		friend vec3 operator * (const vec3& vec, Quaternion& quat);

		void operator *= (const Quaternion& quat);

		void Normalise(void);
		Quaternion Normalised(void);

		void Conjugate(void);
		Quaternion Conjugated(void);

		void SetFromAxisAngle(const vec3& axis, real angle);
		void SetFromEulerAngles(real yaw, real pitch, real roll); 

		vec3 GetAxis(void);
		real GetAngle(void);
		real GetYaw(void);
		real GetPitch(void);
		real GetRoll(void);

		void GetAxisAngle(vec3& axis, real& angle);
		void GetEulerAngles(real& yaw, real& pitch, real& roll);

		void Print(void);

		union 
		{
			real v[4];
			struct{ real x, y, z, w; };
		};
};

typedef Quaternion quat;

#endif