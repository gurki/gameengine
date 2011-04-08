//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Matrix4x4.h"

// constructors
Matrix4x4::Matrix4x4(void)
{
	*this = Identity();
}

Matrix4x4::Matrix4x4(const real* v)
{
	this->m11 = v[0];
	this->m12 = v[1];
	this->m13 = v[2];
	this->m14 = v[3];

	this->m21 = v[4];
	this->m22 = v[5];
	this->m23 = v[6];
	this->m24 = v[7];

	this->m31 = v[8];
	this->m32 = v[9];
	this->m33 = v[10];
	this->m34 = v[11];
	
	this->m41 = v[12];
	this->m42 = v[13];
	this->m43 = v[14];
	this->m44 = v[15];
}

Matrix4x4::Matrix4x4(real m11, real m12, real m13, real m14,
			         real m21, real m22, real m23, real m24,
			         real m31, real m32, real m33, real m34,
					 real m41, real m42, real m43, real m44)
{
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m14 = m14;

	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m24 = m24;

	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
	this->m34 = m34;
	
	this->m41 = m41;
	this->m42 = m42;
	this->m43 = m43;
	this->m44 = m44;
}

// boolean operations
bool Matrix4x4::operator == (const Matrix4x4& m) const
{
	for(uint i = 0; i < 16; i++)
	{
		if(v[i] != m.v[i])
		{
			return false;
		}
	}

	return true;
}

bool Matrix4x4::operator != (const Matrix4x4& m) const
{
	for(uint i = 0; i < 16; i++)
	{
		if(v[i] == m.v[i])
		{
			return false;
		}
	}

	return true;
}

// matrix arithmetics
Matrix4x4 Matrix4x4::operator + (const Matrix4x4& m) const
{
	Matrix4x4 r;

	for(uint i = 0; i < 16; i++)
	{
		r.v[i] = v[i] + m.v[i];
	}

	return r;
}

Matrix4x4 Matrix4x4::operator - (const Matrix4x4& m) const
{
	Matrix4x4 r;

	for(uint i = 0; i < 16; i++)
	{
		r.v[i] = v[i] - m.v[i];
	}

	return r;
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& m) const
{
	Matrix4x4 r;

	r.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41; 	
	r.m13 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42; 	
	r.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43; 	
	r.m14 = m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44;

	r.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41; 	
	r.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42; 	
	r.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43; 	
	r.m24 = m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44;
	
	r.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41; 	
	r.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42; 	
	r.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43; 	
	r.m34 = m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44;
	
	r.m41 = m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41; 	
	r.m42 = m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42; 	
	r.m43 = m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43;	
	r.m44 = m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44;

	return r;
}

Matrix4x4& Matrix4x4::operator += (const Matrix4x4& m)
{
	for(uint i = 0; i < 16; i++)
	{
		v[i] += m.v[i];
	}

	return *this;
}

Matrix4x4& Matrix4x4::operator -= (const Matrix4x4& m)
{
	for(uint i = 0; i < 16; i++)
	{
		v[i] -= m.v[i];
	}

	return *this;
}

Matrix4x4& Matrix4x4::operator *= (const Matrix4x4& m)
{
	Matrix4x4 r;

	r.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31 + m14 * m.m41; 	
	r.m13 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32 + m14 * m.m42; 	
	r.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33 + m14 * m.m43; 	
	r.m14 = m11 * m.m14 + m12 * m.m24 + m13 * m.m34 + m14 * m.m44;

	r.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31 + m24 * m.m41; 	
	r.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32 + m24 * m.m42; 	
	r.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33 + m24 * m.m43; 	
	r.m24 = m21 * m.m14 + m22 * m.m24 + m23 * m.m34 + m24 * m.m44;
	
	r.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31 + m34 * m.m41; 	
	r.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32 + m34 * m.m42; 	
	r.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33 + m34 * m.m43; 	
	r.m34 = m31 * m.m14 + m32 * m.m24 + m33 * m.m34 + m34 * m.m44;
	
	r.m41 = m41 * m.m11 + m42 * m.m21 + m43 * m.m31 + m44 * m.m41; 	
	r.m42 = m41 * m.m12 + m42 * m.m22 + m43 * m.m32 + m44 * m.m42; 	
	r.m43 = m41 * m.m13 + m42 * m.m23 + m43 * m.m33 + m44 * m.m43;	
	r.m44 = m41 * m.m14 + m42 * m.m24 + m43 * m.m34 + m44 * m.m44;

	*this = r;

	return *this;
}

// number arithmetics
Matrix4x4 Matrix4x4::operator * (const real n) const
{
	Matrix4x4 r;

	for(uint i = 0; i < 16; i++)
	{
		r.v[i] = v[i] * n;
	}

	return r;
}

Matrix4x4 Matrix4x4::operator / (const real n) const
{
	Matrix4x4 r;

	for(uint i = 0; i < 16; i++)
	{
		r.v[i] = v[i] / n;
	}

	return r;
}

Matrix4x4 operator * (const real n, const Matrix4x4& m)
{
	Matrix4x4 r;

	for(uint i = 0; i < 16; i++)
	{
		r.v[i] = n * m.v[i];
	}

	return r;
}

Matrix4x4& Matrix4x4::operator *= (const real n)
{
	for(uint i = 0; i < 16; i++)
	{
		v[i] *= n;
	}

	return *this;
}

Matrix4x4& Matrix4x4::operator /= (const real n)
{
	for(uint i = 0; i < 16; i++)
	{
		v[i] /= n;
	}

	return *this;
}

// manipulations
real Matrix4x4::Determinant(void) const
{
	return m14 * m23 * m32 * m41 - m13 * m24 * m32 * m41 - m14 * m22 * m33 * m41 + m12 * m24 * m33 * m41 +
		   m13 * m22 * m34 * m41 - m12 * m23 * m34 * m41 - m14 * m23 * m31 * m42 + m13 * m24 * m31 * m42 +
           m14 * m21 * m33 * m42 - m11 * m24 * m33 * m42 - m13 * m21 * m34 * m42 + m11 * m23 * m34 * m42 +
           m14 * m22 * m31 * m43 - m12 * m24 * m31 * m43 - m14 * m21 * m32 * m43 + m11 * m24 * m32 * m43 +
           m12 * m21 * m34 * m43 - m11 * m22 * m34 * m43 - m13 * m22 * m31 * m44 + m12 * m23 * m31 * m44 +
           m13 * m21 * m32 * m44 - m11 * m23 * m32 * m44 - m12 * m21 * m33 * m44 + m11 * m22 * m33 * m44;
}

Matrix4x4 Matrix4x4::Inversed(void) const
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return Identity();
	}

	det = real(1.0) / det;

	Matrix4x4 m;

    m.m11 = (m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44) * det;
    m.m12 = (m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44) * det;
    m.m13 = (m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44) * det;
    m.m14 = (m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34) * det;
   
    m.m21 = (m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44) * det;
    m.m22 = (m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44) * det;
    m.m23 = (m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44) * det;
    m.m24 = (m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34) * det;
   
    m.m31 = (m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44) * det;
    m.m32 = (m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44) * det;
    m.m33 = (m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44) * det;
    m.m34 = (m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34) * det;
   
    m.m41 = (m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43) * det;
    m.m42 = (m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43) * det;
    m.m43 = (m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43) * det;
    m.m44 = (m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33) * det;
	
	return m;
}

Matrix4x4 Matrix4x4::Transposed(void) const
{
	return Matrix4x4(m11, m21, m31, m41,
		             m12, m22, m32, m42,
					 m13, m23, m33, m43,
					 m14, m24, m34, m44);
}

Matrix4x4& Matrix4x4::Inverse(void)
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return (Matrix4x4&)Identity();
	}

	det = (real)1.0 / det;

	Matrix4x4 m;

    m.m11 = m23 * m34 * m42 - m24 * m33 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 + m22 * m33 * m44;
    m.m12 = m14 * m33 * m42 - m13 * m34 * m42 - m14 * m32 * m43 + m12 * m34 * m43 + m13 * m32 * m44 - m12 * m33 * m44;
    m.m13 = m13 * m24 * m42 - m14 * m23 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 + m12 * m23 * m44;
    m.m14 = m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34;
   
    m.m21 = m24 * m33 * m41 - m23 * m34 * m41 - m24 * m31 * m43 + m21 * m34 * m43 + m23 * m31 * m44 - m21 * m33 * m44;
    m.m22 = m13 * m34 * m41 - m14 * m33 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 + m11 * m33 * m44;
    m.m23 = m14 * m23 * m41 - m13 * m24 * m41 - m14 * m21 * m43 + m11 * m24 * m43 + m13 * m21 * m44 - m11 * m23 * m44;
    m.m24 = m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34;
   
    m.m31 = m22 * m34 * m41 - m24 * m32 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 + m21 * m32 * m44;
    m.m32 = m14 * m32 * m41 - m12 * m34 * m41 - m14 * m31 * m42 + m11 * m34 * m42 + m12 * m31 * m44 - m11 * m32 * m44;
    m.m33 = m12 * m24 * m41 - m14 * m22 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 + m11 * m22 * m44;
    m.m34 = m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34;
   
    m.m41 = m23 * m32 * m41 - m22 * m33 * m41 - m23 * m31 * m42 + m21 * m33 * m42 + m22 * m31 * m43 - m21 * m32 * m43;
    m.m42 = m12 * m33 * m41 - m13 * m32 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 + m11 * m32 * m43;
    m.m43 = m13 * m22 * m41 - m12 * m23 * m41 - m13 * m21 * m42 + m11 * m23 * m42 + m12 * m21 * m43 - m11 * m22 * m43;
    m.m44 = m12 * m23 * m31 - m13 * m22 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 + m11 * m22 * m33;

	*this = m;

	return *this;
}

Matrix4x4& Matrix4x4::Transpose(void)
{
	*this = Matrix4x4(m11, m21, m31, m41,
		              m12, m22, m32, m42,
					  m13, m23, m33, m43,
					  m14, m24, m34, m44);

	return *this;
}

// static members
const Matrix4x4& Matrix4x4::Zero(void)
{
	static const Matrix4x4 m(0, 0, 0, 0, 
		                     0, 0, 0, 0, 
						     0, 0, 0, 0,
							 0, 0, 0, 0);

	return m;
}

const Matrix4x4& Matrix4x4::Identity(void)
{
	static const Matrix4x4 m(1, 0, 0, 0, 
		                     0, 1, 0, 0, 
						     0, 0, 1, 0,
							 0, 0, 0, 1);

	return m;
}

// iostream
ostream& operator << (ostream& out, const Matrix4x4& m)
{
	out << "{";
	out << "{" << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.m14 << "}, ";
	out << "{" << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.m24 << "}, ";
	out << "{" << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.m34 << "}, ";
	out << "{" << m.m41 << ", " << m.m42 << ", " << m.m43 << ", " << m.m44 << "}} ";

	return out;
}

istream& operator >> (istream& in, Matrix4x4& m)
{
	real v[16];

	for(uint i = 0; i < 16; i++)
	{
		in >> v[i];
	}

	m = Matrix4x4(v);

	return in;
}


