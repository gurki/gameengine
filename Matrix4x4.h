//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"

#include <iostream>

using namespace std;

class Matrix4x4
{
	public:

		Matrix4x4(void);
		Matrix4x4(const real* v);
		Matrix4x4(real m11, real m12, real m13, real m14,
			      real m21, real m22, real m23, real m24,
			      real m31, real m32, real m33, real m34,
				  real m41, real m42, real m43, real m44);

		// boolean operations
		bool operator == (const Matrix4x4& m) const;
		bool operator != (const Matrix4x4& m) const;

		// matrix arithmetics
		Matrix4x4 operator + (const Matrix4x4& m) const;
		Matrix4x4 operator - (const Matrix4x4& m) const;
		Matrix4x4 operator * (const Matrix4x4& m) const;

		Matrix4x4& operator += (const Matrix4x4& m);
		Matrix4x4& operator -= (const Matrix4x4& m);
		Matrix4x4& operator *= (const Matrix4x4& m);

		// number arithmetics
		Matrix4x4 operator * (const real n) const;
		Matrix4x4 operator / (const real n) const;
		friend Matrix4x4 operator * (const real n, const Matrix4x4& m);
		
		Matrix4x4& operator *= (const real n);
		Matrix4x4& operator /= (const real n);
		
		// manipulations
		virtual real Determinant(void) const;

		virtual Matrix4x4 Inversed(void) const;
		Matrix4x4 Transposed(void) const;

		virtual Matrix4x4& Inverse(void);
		Matrix4x4& Transpose(void);

		// static members
		static const Matrix4x4& Zero(void);
		static const Matrix4x4& Identity(void);

		// iostream
		friend ostream& operator << (ostream& out, const Matrix4x4& m);
		friend istream& operator >> (istream& in, Matrix4x4& m);

		// data members
		union
		{
			real v[16];

			struct { real m11, m21, m31, m41;
					 real m12, m22, m32, m42;
					 real m13, m23, m33, m43;
					 real m14, m24, m34, m44; };
		};
};

typedef Matrix4x4 mat4;