//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "MathLib.h"
#include "Vector3.h"

#include <iostream>

using namespace std;

class Quaternion
{
	public:

		Quaternion(void);
		Quaternion(const real* v);
		Quaternion(real x, real y, real z, real w);

		Quaternion(const vec3& axis, real angle);
		Quaternion(real yaw, real pitch, real roll);

		Quaternion(const vec3& from, const vec3& to);
		Quaternion(const vec3& to);
		
		void operator = (const Quaternion& quat);

		bool operator == (const Quaternion& quat)const;
		bool operator != (const Quaternion& quat) const;

		Quaternion operator * (const Quaternion& quat) const;
		vec3 operator * (const vec3& vec) const;

		friend vec3 operator * (const vec3& vec, const Quaternion& quat);

		void operator *= (const Quaternion& quat);

		void Normalise(void);
		Quaternion Normalised(void) const;

		void Conjugate(void);
		Quaternion Conjugated(void) const;

		void SetFromAxisAngle(const vec3& axis, real angle);
		void SetFromEulerAngles(real yaw, real pitch, real roll); 
		void SetFromDirections(const vec3& from, const vec3& to);
		void SetFromDirection(const vec3& to);

		vec3 GetDirection(void) const;

		vec3 GetAxis(void) const;
		real GetAngle(void) const;

		real GetYaw(void) const;
		real GetPitch(void) const;
		real GetRoll(void) const;

		void GetAxisAngle(vec3& axis, real& angle) const;
		void GetEulerAngles(real& yaw, real& pitch, real& roll) const;

		friend ostream& operator << (ostream& out, const Quaternion& quat);
		friend istream& operator >> (istream& in, Quaternion& quat);

		union 
		{
			real v[4];
			struct{ real x, y, z, w; };
		};

		static const Quaternion Zero(void);
		static const Quaternion Identity(void);
};

typedef Quaternion quat;

#endif