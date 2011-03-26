//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Quaternion.h"

#include <iostream>

using namespace std;

// Matrix3x4
class Matrix3x4
{
	public:

		// constructors
		Matrix3x4(void);
		Matrix3x4(const real* v);
		Matrix3x4(const Matrix3x3& m);
		Matrix3x4(real m11, real m12, real m13, real m14,
			      real m21, real m22, real m23, real m24,
				  real m31, real m32, real m33, real m34);

		// boolean operations
		bool operator == (const Matrix3x4& m) const;
		bool operator != (const Matrix3x4& m) const;

		// matrix arithmetics
		Matrix3x4 operator + (const Matrix3x4& m) const;
		Matrix3x4 operator - (const Matrix3x4& m) const;
		Matrix3x4 operator * (const Matrix3x4& m) const;

		Matrix3x4& operator += (const Matrix3x4& m);
		Matrix3x4& operator -= (const Matrix3x4& m);
		Matrix3x4& operator *= (const Matrix3x4& m);

		// number arithmetics
		Matrix3x4 operator * (const real n) const;
		Matrix3x4 operator / (const real n) const;
		friend Matrix3x4 operator * (const real n, const Matrix3x4& m);
		
		Matrix3x4& operator *= (const real n);
		Matrix3x4& operator /= (const real n);

		// vector arithmetics
		Vector3 operator * (const Vector3& v) const;
		friend Vector3 operator * (const Vector3& v, const Matrix3x4& m);

		// manipulations
		real Determinant(void) const;

		Matrix3x4& Inverse(void);

		Matrix3x4 Inversed(void) const;

		// conversions
		static Matrix3x4 WithRotation(const Quaternion& q);
		static Matrix3x4 WithTranslation(const Vector3& v);
		static Matrix3x4 WithTransformation(const Quaternion& q, const Vector3& v);

		// static members
		static const Matrix3x4& Zero(void);
		static const Matrix3x4& Identity(void);

		// iostream
		friend ostream& operator << (ostream& out, const Matrix3x4& m);
		friend istream& operator >> (istream& in, Matrix3x4& m);

		// data members
		union
		{
			real v[12];

			struct { real m11, m12, m13, m14;
					 real m21, m22, m23, m24;
					 real m31, m32, m33, m34; };
		};
};

// typedefs
typedef Matrix3x4 mat34;