//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Matrix3x3.h"

// constructors
Matrix3x3::Matrix3x3(void)
{
	*this = Identity();
}

Matrix3x3::Matrix3x3(const real* v)
{
	for(uint i = 0; i < 9; i++)
	{
		this->v[i] = v[i];
	}
}

Matrix3x3::Matrix3x3(real m11, real m12, real m13,
			         real m21, real m22, real m23,
			         real m31, real m32, real m33)
{
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;

	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;

	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

// boolean operations
bool Matrix3x3::operator == (const Matrix3x3& m) const
{
	for(uint i = 0; i < 9; i++)
	{
		if(v[i] != m.v[i])
		{
			return false;
		}
	}

	return true;
}

bool Matrix3x3::operator != (const Matrix3x3& m) const
{
	for(uint i = 0; i < 9; i++)
	{
		if(v[i] == m.v[i])
		{
			return false;
		}
	}

	return true;
}

// matrix arithmetics
Matrix3x3 Matrix3x3::operator + (const Matrix3x3& m) const
{
	Matrix3x3 r;

	for(uint i = 0; i < 9; i++)
	{
		r.v[i] = v[i] + m.v[i];
	}

	return r;
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3& m) const
{
	Matrix3x3 r;

	for(uint i = 0; i < 9; i++)
	{
		r.v[i] = v[i] - m.v[i];
	}

	return r;
}

Matrix3x3 Matrix3x3::operator * (const Matrix3x3& m) const
{
	Matrix3x3 r;

	r.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
	r.m12 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
	r.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

	r.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
	r.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
	r.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

	r.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
	r.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
	r.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33;

	return r;
}

Matrix3x3& Matrix3x3::operator += (const Matrix3x3& m)
{
	for(uint i = 0; i < 9; i++)
	{
		v[i] += m.v[i];
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator -= (const Matrix3x3& m)
{
	for(uint i = 0; i < 9; i++)
	{
		v[i] -= m.v[i];
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& m)
{
	Matrix3x3 r;

	r.m11 = m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
	r.m12 = m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
	r.m13 = m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

	r.m21 = m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
	r.m22 = m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
	r.m23 = m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

	r.m31 = m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
	r.m32 = m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
	r.m33 = m31 * m.m13 + m32 * m.m23 + m33 * m.m33;

	*this = r;

	return *this;
}

// number arithmetics
Matrix3x3 Matrix3x3::operator * (const real n) const
{
	Matrix3x3 r;

	for(uint i = 0; i < 9; i++)
	{
		r.v[i] = v[i] * n;
	}

	return r;
}

Matrix3x3 Matrix3x3::operator / (const real n) const
{
	Matrix3x3 r;

	for(uint i = 0; i < 9; i++)
	{
		r.v[i] = v[i] / n;
	}

	return r;
}

Matrix3x3 operator * (const real n, const Matrix3x3& m)
{
	Matrix3x3 r;

	for(uint i = 0; i < 9; i++)
	{
		r.v[i] = n * m.v[i];
	}

	return r;
}

Matrix3x3& Matrix3x3::operator *= (const real n)
{
	for(uint i = 0; i < 9; i++)
	{
		v[i] *= n;
	}

	return *this;
}

Matrix3x3& Matrix3x3::operator /= (const real n)
{
	for(uint i = 0; i < 9; i++)
	{
		v[i] /= n;
	}

	return *this;
}

// vector arithmetics
Vector3 Matrix3x3::operator * (const Vector3& v) const
{
	Vector3 r;
	
	r.x = m11 * v.x + m12 * v.y + m13 * v.z;
	r.y = m21 * v.x + m22 * v.y + m23 * v.z;
	r.z = m31 * v.x + m32 * v.y + m33 * v.z;
	
	return r;
}

Vector3 operator * (const Vector3& v, const Matrix3x3& m)
{
	Vector3 r;

    r.x = m.m11 * v.x + m.m21 * v.y + m.m31 * v.z; 
	r.y = m.m12 * v.x + m.m22 * v.y + m.m32 * v.z;
	r.z = m.m13 * v.x + m.m23 * v.y + m.m33 * v.z;

	return r;
}

// manipulations
real Matrix3x3::Determinant(void) const
{
	return m11 * m22 * m33 +
		   m21 * m32 * m13 +
		   m31 * m12 * m23 -
		   m13 * m22 * m31 -
		   m12 * m21 * m33 -
		   m11 * m23 * m32;
}

Matrix3x3 Matrix3x3::Inversed(void) const
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return Identity();
	}

	det = real(1.0) / det;

	Matrix3x3 m;

	m.m11 = (m22 * m33 - m23 * m32) * det;
	m.m12 = (m13 * m32 - m12 * m33) * det;
	m.m13 = (m12 * m23 - m13 * m22) * det;

	m.m21 = (m23 * m31 - m21 * m33) * det;
	m.m22 = (m11 * m33 - m13 * m31) * det;
	m.m23 = (m13 * m21 - m11 * m23) * det;

	m.m31 = (m21 * m32 - m22 * m31) * det;
	m.m32 = (m12 * m31 - m11 * m32) * det;
	m.m33 = (m11 * m22 - m12 * m21) * det;
	
	return m;
}

Matrix3x3 Matrix3x3::Transposed(void) const
{
	return Matrix3x3(m11, m21, m31,
		             m12, m22, m32,
					 m13, m23, m33);
}

Matrix3x3& Matrix3x3::Inverse(void)
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return (Matrix3x3&)Identity();
	}

	det = (real)1.0 / det;

	Matrix3x3 m;

	m.m11 = (m22 * m33 - m23 * m32) * det;
	m.m12 = (m13 * m32 - m12 * m33) * det;
	m.m13 = (m12 * m23 - m13 * m22) * det;

	m.m21 = (m23 * m31 - m21 * m33) * det;
	m.m22 = (m11 * m33 - m13 * m31) * det;
	m.m23 = (m13 * m21 - m11 * m23) * det;

	m.m31 = (m21 * m32 - m22 * m31) * det;
	m.m32 = (m12 * m31 - m11 * m32) * det;
	m.m33 = (m11 * m22 - m12 * m21) * det;

	*this = m;

	return *this;
}

Matrix3x3& Matrix3x3::Transpose(void)
{
	*this = Matrix3x3(m11, m21, m31,
		              m12, m22, m32,
					  m13, m23, m33);

	return *this;
}

// static members
const Matrix3x3& Matrix3x3::Zero(void)
{
	static const Matrix3x3 m(0, 0, 0, 
		                     0, 0, 0, 
						     0, 0, 0);

	return m;
}

const Matrix3x3& Matrix3x3::Identity(void)
{
	static const Matrix3x3 m(1, 0, 0, 
		                     0, 1, 0, 
						     0, 0, 1);

	return m;
}
/*
// convertions
Matrix3x3 Matrix3x3::WithQuaternion(const Quaternion& q)
{
	Matrix3x3 r;

	r.m11 = 1 - 2 * (q.y * q.y - q.z * q.z);
	r.m12 =     2 * (q.x * q.y + q.z * q.w);
	r.m13 =     2 * (q.x * q.z - q.y * q.w);

	r.m21 =     2 * (q.x * q.y - q.z * q.w);
	r.m22 = 1 - 2 * (q.x * q.x + q.z * q.z);
	r.m23 =     2 * (q.y * q.z + q.x * q.w);

	r.m31 =     2 * (q.x * q.z + q.y * q.w);
	r.m32 =     2 * (q.y * q.z - q.x * q.w);
	r.m33 = 1 - 2 * (q.x * q.x + q.y * q.y);

	return r;
}
*/
// iostream
ostream& operator << (ostream& out, const Matrix3x3& m)
{
	out << "{";
	out << "{" << m.m11 << ", " << m.m12 << ", " << m.m13 << "}, ";
	out << "{" << m.m21 << ", " << m.m22 << ", " << m.m23 << "}, ";
	out << "{" << m.m31 << ", " << m.m32 << ", " << m.m33 << "}} ";

	return out;
}

istream& operator >> (istream& in, Matrix3x3& m)
{
	real v[9];

	for(uint i = 0; i < 9; i++)
	{
		in >> v[i];
	}

	m = Matrix3x3(v);

	return in;
}


