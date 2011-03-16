//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Matrix3x4.h"


// constructors
Matrix3x4::Matrix3x4(void)
{
	*this = Identity();
}

Matrix3x4::Matrix3x4(const real* v)
{
	for(uint i = 0; i < 12; i++)
	{
		this->v[i] = v[i];
	}
}

Matrix3x4::Matrix3x4(real m11, real m12, real m13, real m14,
			         real m21, real m22, real m23, real m24,
			         real m31, real m32, real m33, real m34)
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
}

Matrix3x4::Matrix3x4(const Matrix3x3& mat)
{
	this->m11 = mat.m11;
	this->m12 = mat.m12;
	this->m13 = mat.m13;
	this->m14 = 0.0;

	this->m21 = mat.m21;
	this->m22 = mat.m22;
	this->m23 = mat.m23;
	this->m24 = 0.0;

	this->m31 = mat.m31;
	this->m32 = mat.m32;
	this->m33 = mat.m33;
	this->m34 = 0.0;
}

// boolean operations
bool Matrix3x4::operator == (const Matrix3x4& m) const
{
	for(uint i = 0; i < 12; i++)
	{
		if(v[i] != m.v[i])
		{
			return false;
		}
	}

	return true;
}

bool Matrix3x4::operator != (const Matrix3x4& m) const
{
	for(uint i = 0; i < 12; i++)
	{
		if(v[i] == m.v[i])
		{
			return false;
		}
	}

	return true;
}

// matrix arithmetics
Matrix3x4 Matrix3x4::operator + (const Matrix3x4& m) const
{
	Matrix3x4 r;

	for(uint i = 0; i < 12; i++)
	{
		r.v[i] = v[i] + m.v[i];
	}

	return r;
}

Matrix3x4 Matrix3x4::operator - (const Matrix3x4& m) const
{
	Matrix3x4 r;

	for(uint i = 0; i < 12; i++)
	{
		r.v[i] = v[i] - m.v[i];
	}

	return r;
}

Matrix3x4 Matrix3x4::operator * (const Matrix3x4& m) const
{
	Matrix3x4 r;

	r.m11 = m.m11 * m11 + m.m21 * m12 + m.m31 * m13;
	r.m21 = m.m11 * m21 + m.m21 * m22 + m.m31 * m23;
	r.m31 = m.m11 * m31 + m.m21 * m32 + m.m31 * m33;

	r.m12 = m.m12 * m11 + m.m22 * m12 + m.m32 * m13;
	r.m22 = m.m12 * m21 + m.m22 * m22 + m.m32 * m23;
	r.m32 = m.m12 * m31 + m.m22 * m32 + m.m32 * m33;

	r.m13 = m.m13 * m11 + m.m23 * m12 + m.m33 * m13;
	r.m23 = m.m13 * m21 + m.m23 * m22 + m.m33 * m23;
	r.m33 = m.m13 * m31 + m.m23 * m32 + m.m33 * m33;
	
	r.m14 = m.m14 * m11 + m.m24 * m12 + m.m34 * m13 + m14;
	r.m24 = m.m14 * m21 + m.m24 * m22 + m.m34 * m23 + m24;
	r.m34 = m.m14 * m31 + m.m24 * m32 + m.m34 * m33 + m34;

	return r;
}

Matrix3x4& Matrix3x4::operator += (const Matrix3x4& m)
{
	for(uint i = 0; i < 12; i++)
	{
		v[i] += m.v[i];
	}

	return *this;
}

Matrix3x4& Matrix3x4::operator -= (const Matrix3x4& m)
{
	for(uint i = 0; i < 12; i++)
	{
		v[i] -= m.v[i];
	}

	return *this;
}

Matrix3x4& Matrix3x4::operator *= (const Matrix3x4& m)
{
	Matrix3x4 r;

	r.m11 = m.m11 * m11 + m.m21 * m12 + m.m31 * m13;
	r.m21 = m.m11 * m21 + m.m21 * m22 + m.m31 * m23;
	r.m31 = m.m11 * m31 + m.m21 * m32 + m.m31 * m33;

	r.m12 = m.m12 * m11 + m.m22 * m12 + m.m32 * m13;
	r.m22 = m.m12 * m21 + m.m22 * m22 + m.m32 * m23;
	r.m32 = m.m12 * m31 + m.m22 * m32 + m.m32 * m33;

	r.m13 = m.m13 * m11 + m.m23 * m12 + m.m33 * m13;
	r.m23 = m.m13 * m21 + m.m23 * m22 + m.m33 * m23;
	r.m33 = m.m13 * m31 + m.m23 * m32 + m.m33 * m33;
	
	r.m14 = m.m14 * m11 + m.m24 * m12 + m.m34 * m13 + m14;
	r.m24 = m.m14 * m21 + m.m24 * m22 + m.m34 * m23 + m24;
	r.m34 = m.m14 * m31 + m.m24 * m32 + m.m34 * m33 + m34;

	*this = r;

	return *this;
}

// number arithmetics
Matrix3x4 Matrix3x4::operator * (const real n) const
{
	Matrix3x4 r;

	for(uint i = 0; i < 12; i++)
	{
		r.v[i] = v[i] * n;
	}

	return r;
}

Matrix3x4 Matrix3x4::operator / (const real n) const
{
	Matrix3x4 r;

	for(uint i = 0; i < 12; i++)
	{
		r.v[i] = v[i] / n;
	}

	return r;
}

Matrix3x4 operator * (const real n, const Matrix3x4& m)
{
	Matrix3x4 r;

	for(uint i = 0; i < 12; i++)
	{
		r.v[i] = n * m.v[i];
	}

	return r;
}

Matrix3x4& Matrix3x4::operator *= (const real n)
{
	for(uint i = 0; i < 12; i++)
	{
		v[i] *= n;
	}

	return *this;
}

Matrix3x4& Matrix3x4::operator /= (const real n)
{
	for(uint i = 0; i < 12; i++)
	{
		v[i] /= n;
	}

	return *this;
}

// vector arithmetics
Vector3 Matrix3x4::operator * (const Vector3& v) const
{
	Vector3 r;

	r.x = m14 + m13 * v.z + m12 * v.y * m11 * v.x;
	r.y = m24 + m23 * v.z + m22 * v.y + m21 * v.x;
	r.z = m34 + m33 * v.z + m32 * v.y + m31 * v.x;

	return r;
}

Vector3 operator * (const Vector3& v, const Matrix3x4& m)
{
	Vector3 r;

	r.x = m.m14 + m.m13 * v.z + m.m12 * v.y * m.m11 * v.x;
	r.y = m.m24 + m.m23 * v.z + m.m22 * v.y + m.m21 * v.x;
	r.z = m.m34 + m.m33 * v.z + m.m32 * v.y + m.m31 * v.x;

	return r;
}

// manipulations
real Matrix3x4::Determinant(void) const
{
	return m31 * m22 * m13 +
		   m21 * m32 * m13 +
		   m31 * m12 * m23 -
		   m11 * m32 * m23 -
		   m21 * m12 * m33 -
		   m11 * m22 * m33;
}

Matrix3x4 Matrix3x4::Inversed(void) const
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return (Matrix3x4&)Identity();
	}

	det = real(1.0) / det;

	Matrix3x4 m;

	m.m11 = (m22 * m33 - m32 * m23) * det;
	m.m21 = (m31 * m23 - m21 * m33) * det;
	m.m31 = (m21 * m32 - m31 * m22) * det;

	m.m12 = (m32 * m13 - m12 * m33) * det;
	m.m22 = (m11 * m33 - m31 * m13) * det;
	m.m32 = (m31 * m12 - m11 * m32) * det;

	m.m13 = (m12 * m23 - m22 * m13) * det;
	m.m23 = (m21 * m13 - m11 * m23) * det;
	m.m33 = (m11 * m22 - m21 * m12) * det;

	m.m14 = (m32 * m23 * m14 - m22 * m33 * m14 - m32 * m13 * m24 + m12 * m33 * m24 + m22 * m13 * m34 - m12 * m23 * m34) * det;
	m.m24 = (m31 * m23 * m14 - m21 * m33 * m14 - m31 * m13 * m24 + m11 * m33 * m24 + m21 * m13 * m34 - m11 * m23 * m34) * det;
	m.m34 = (m31 * m22 * m14 - m21 * m32 * m14 - m31 * m12 * m24 + m11 * m32 * m24 + m21 * m12 * m34 - m11 * m22 * m34) * det;
	
	return m;
}

Matrix3x4& Matrix3x4::Inverse(void)
{
	real det = Determinant();

	if(det == 0.0) 
	{
		return (Matrix3x4&)Identity();
	}

	det = (real)1.0 / det;

	Matrix3x4 m;

	m.m11 = (m22 * m33 - m32 * m23) * det;
	m.m21 = (m31 * m23 - m21 * m33) * det;
	m.m31 = (m21 * m32 - m31 * m22) * det;

	m.m12 = (m32 * m13 - m12 * m33) * det;
	m.m22 = (m11 * m33 - m31 * m13) * det;
	m.m32 = (m31 * m12 - m11 * m32) * det;

	m.m13 = (m12 * m23 - m22 * m13) * det;
	m.m23 = (m21 * m13 - m11 * m23) * det;
	m.m33 = (m11 * m22 - m21 * m12) * det;

	m.m14 = (m32 * m23 * m14 - m22 * m33 * m14 - m32 * m13 * m24 + m12 * m33 * m24 + m22 * m13 * m34 - m12 * m23 * m34) * det;
	m.m24 = (m31 * m23 * m14 - m21 * m33 * m14 - m31 * m13 * m24 + m11 * m33 * m24 + m21 * m13 * m34 - m11 * m23 * m34) * det;
	m.m34 = (m31 * m22 * m14 - m21 * m32 * m14 - m31 * m12 * m24 + m11 * m32 * m24 + m21 * m12 * m34 - m11 * m22 * m34) * det;

	*this = m;

	return *this;
}

// conversions
Matrix3x4 Matrix3x4::WithRotation(const Quaternion& q)
{
	Matrix3x4 r;

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

Matrix3x4 Matrix3x4::WithTranslation(const Vector3& v)
{
	Matrix3x4 r;

	r.m14 = v.x;
	r.m24 = v.y;
	r.m34 = v.z;

	return r;
}

Matrix3x4 Matrix3x4::WithTransformation(const Quaternion& q, const Vector3& v)
{
	Matrix3x4 r;

	r.m11 = 1 - 2 * (q.y * q.y - q.z * q.z);
	r.m12 =     2 * (q.x * q.y + q.z * q.w);
	r.m13 =     2 * (q.x * q.z - q.y * q.w);

	r.m21 =     2 * (q.x * q.y - q.z * q.w);
	r.m22 = 1 - 2 * (q.x * q.x + q.z * q.z);
	r.m23 =     2 * (q.y * q.z + q.x * q.w);

	r.m31 =     2 * (q.x * q.z + q.y * q.w);
	r.m32 =     2 * (q.y * q.z - q.x * q.w);
	r.m33 = 1 - 2 * (q.x * q.x + q.y * q.y);

	r.m14 = v.x;
	r.m24 = v.y;
	r.m34 = v.z;

	return r;
}

// static members
const Matrix3x4& Matrix3x4::Zero(void)
{
	static const Matrix3x4 m(0, 0, 0, 0, 
		                     0, 0, 0, 0, 
						     0, 0, 0, 0);

	return m;
}

const Matrix3x4& Matrix3x4::Identity(void)
{
	static const Matrix3x4 m(1, 0, 0, 0, 
		                     0, 1, 0, 0, 
						     0, 0, 1, 0);

	return m;
}

// iostream
ostream& operator << (ostream& out, const Matrix3x4& m)
{
	out << "{";
	out << "{" << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.m14 << "}, ";
	out << "{" << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.m24 << "}, ";
	out << "{" << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.m34 << "}, ";
	out << "{0, 0, 0, 1}}";

	return out;
}

istream& operator >> (istream& in, Matrix3x4& m)
{
	real v[12];

	for(uint i = 0; i < 12; i++)
	{
		in >> v[i];
	}

	m = Matrix3x4(v);

	return in;
}


