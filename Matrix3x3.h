//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include "Vector3.h"
// #include "Quaternion.h"

#include <iostream>

using namespace std;

class Matrix3x3
{
	public:

		Matrix3x3(void);
		Matrix3x3(const real* v);
		Matrix3x3(real m11, real m12, real m13,
			      real m21, real m22, real m23,
				  real m31, real m32, real m33);

		// boolean operations
		bool operator == (const Matrix3x3& m) const;
		bool operator != (const Matrix3x3& m) const;

		// matrix arithmetics
		Matrix3x3 operator + (const Matrix3x3& m) const;
		Matrix3x3 operator - (const Matrix3x3& m) const;
		Matrix3x3 operator * (const Matrix3x3& m) const;

		Matrix3x3& operator += (const Matrix3x3& m);
		Matrix3x3& operator -= (const Matrix3x3& m);
		Matrix3x3& operator *= (const Matrix3x3& m);

		// number arithmetics
		Matrix3x3 operator * (const real n) const;
		Matrix3x3 operator / (const real n) const;
		friend Matrix3x3 operator * (const real n, const Matrix3x3& m);
		
		Matrix3x3& operator *= (const real n);
		Matrix3x3& operator /= (const real n);

		// vector arithmetics
		Vector3 operator * (const Vector3& v) const;
		friend Vector3 operator * (const Vector3& v, const Matrix3x3& m);

		// manipulations
		real Determinant(void) const;

		Matrix3x3 Inversed(void) const;
		Matrix3x3 Transposed(void) const;

		Matrix3x3& Inverse(void);
		Matrix3x3& Transpose(void);

		// static members
		static const Matrix3x3& Zero(void);
		static const Matrix3x3& Identity(void);
/*
		// convertions
		static Matrix3x3 WithQuaternion(const Quaternion& q);
*/
		// iostream
		friend ostream& operator << (ostream& out, const Matrix3x3& m);
		friend istream& operator >> (istream& in, Matrix3x3& m);

		// data members
		union
		{
			real v[9];

			struct { real m11, m12, m13;
					 real m21, m22, m23;
					 real m31, m32, m33; };
		};
};

typedef Matrix3x3 mat3;