//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "MathLib.h"
#include "Vector3.h"

#include <iostream>

using namespace std;

// axisangle
struct AxisAngle
{
	vec3 axis;
	real angle;
};

// eulerangles
struct EulerAngles
{
	real yaw;
	real pitch;
	real roll;
};

// quaternions
class Quaternion
{
	public:

		// constructors
		Quaternion(void);
		Quaternion(const real* v);
		Quaternion(real w, real x, real y, real z);

		// assign operators
		void operator = (const Quaternion& quat);

		// boolean operators
		bool operator == (const Quaternion& quat) const;
		bool operator != (const Quaternion& quat) const;

		// real operators
		Quaternion operator * (real n) const;
		Quaternion operator / (real n) const;
		friend Quaternion operator * (real n, const Quaternion& quat);

		Quaternion& operator *= (real n);
		Quaternion& operator /= (real n);

		// vector arithmetics
		vec3 operator * (const vec3& vec) const;
		friend vec3 operator * (const vec3& vec, const Quaternion& quat);

		// quaternion arithmetics
		Quaternion operator + (const Quaternion& quat) const;
		Quaternion operator - (const Quaternion& quat) const;
		Quaternion operator * (const Quaternion& quat) const;

		Quaternion& operator += (const Quaternion& quat);
		Quaternion& operator -= (const Quaternion& quat);
		Quaternion& operator *= (const Quaternion& quat);

		// manipulations
		Quaternion Normalised(void) const;
		Quaternion Conjugated(void) const;

		Quaternion& Normalise(void);
		Quaternion& Conjugate(void);

		// static setter
		static Quaternion WithAxisAngle(const vec3& axis, real angle);
		static Quaternion WithEulerAngles(real yaw, real pitch, real roll);

		static Quaternion WithOrientation(const vec3& orientation);
		static Quaternion WithFromToOrientations(const vec3& from, const vec3& to);
		
		static Quaternion WithRotationAboutX(real angle);
		static Quaternion WithRotationAboutY(real angle);
		static Quaternion WithRotationAboutZ(real angle);
		
		// getter
		vec3 GetOrientation(void) const;
		AxisAngle GetAxisAngle(void) const;
		EulerAngles GetEulerAngles(void) const;

		// streams
		friend ostream& operator << (ostream& out, const Quaternion& quat);
		friend istream& operator >> (istream& in, Quaternion& quat);
	
		// static const members
		static const Quaternion Zero(void);
		static const Quaternion Identity(void);

		// member variables
		real w, x, y, z;
};

typedef Quaternion quat;