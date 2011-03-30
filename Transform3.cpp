//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Transform3.h"

// constructors
Transform3::Transform3(void) : Matrix4x4()
{

}

Transform3::Transform3(const vec3& translation, const quat& rotation)
{
	SetRotation(rotation);
	SetTranslation(translation);
		
	m41 = 0;
	m42 = 0;
	m43 = 0;
	m44 = 1;
}
	
// vector arithmetics
vec3 Transform3::operator * (const vec3& v) const
{
	vec3 r;
	
	r.x = v.x * m11 + v.y * m12 + v.z * m13 + m14;
	r.y = v.x * m21 + v.y * m22 + v.z * m23 + m24;
	r.z = v.x * m31 + v.y * m32 + v.z * m33 + m34;

	return r;
}

vec3 operator * (const vec3& v, const Transform3& t)
{
	vec3 r;
	
	r.x = v.x * t.m11 + v.y * t.m12 + v.z * t.m13 + t.m14;
	r.y = v.x * t.m21 + v.y * t.m22 + v.z * t.m23 + t.m24;
	r.z = v.x * t.m31 + v.y * t.m32 + v.z * t.m33 + t.m34;

	return r;
}
	
// methods
vec3 Transform3::FromWorldToLocal(const vec3& v) const
{
	vec3 r;

	real temp1 = -m23 * m32 + m22 * m33;
    real temp2 =  m13 * m32 - m12 * m33;
    real temp3 = -m13 * m22 + m12 * m23;
    real temp4 =  m14 * m23 * m32 - m13 * m24 * m32 - m14 * m22 * m33 + m12 * m24 * m33 + m13 * m22 * m34 - m12 * m23 * m34;
   
	r.x = v.x * temp1 + v.y * temp2 + v.z * temp3 + temp4;

    temp1 =  m23 * m31 - m21 * m33;
    temp2 = -m13 * m31 + m11 * m33;
    temp3 =  m13 * m21 - m11 * m23;
    temp4 =  m13 * m24 * m31 - m14 * m23 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 + m11 * m23 * m34;
   
	r.y = v.x * temp1 + v.y * temp2 + v.z * temp3 + temp4;

    temp1 = -m22 * m31 + m21 * m32;
    temp2 =  m12 * m31 - m11 * m32;
    temp3 = -m12 * m21 + m11 * m22;
    temp4 =  m14 * m22 * m31 - m12 * m24 * m31 - m14 * m21 * m32 + m11 * m24 * m32 + m12 * m21 * m34 - m11 * m22 * m34;
	
	r.z = v.x * temp1 + v.y * temp2 + v.z * temp3 + temp4;
	
	return r;
}

vec3 Transform3::FromLocalToWorld(const vec3& v) const
{
	vec3 r;
	
	r.x = v.x * m11 + v.y * m12 + v.z * m13 + m14;
	r.y = v.x * m21 + v.y * m22 + v.z * m23 + m24;
	r.z = v.x * m31 + v.y * m32 + v.z * m33 + m34;
	
	return r;
}

// setter
Transform3& Transform3::SetRotation(const quat& q)
{
    real sqw = q.w * q.w;
    real sqx = q.x * q.x;
    real sqy = q.y * q.y;
    real sqz = q.z * q.z;

    m11 = 1.0f - 2.0f * (sqy + sqz);
    m22 = 1.0f - 2.0f * (sqx + sqz);
    m33 = 1.0f - 2.0f * (sqx + sqy);
    
    real tmp1 = q.x * q.y;
    real tmp2 = q.z * q.w;
    
	m21 = 2.0f * (tmp1 + tmp2);
    m12 = 2.0f * (tmp1 - tmp2);
    
    tmp1 = q.x * q.z;
    tmp2 = q.y * q.w;
    
	m31 = 2.0f * (tmp1 - tmp2);
    m13 = 2.0f * (tmp1 + tmp2);
    
	tmp1 = q.y * q.z;
    tmp2 = q.x * q.w;

    m32 = 2.0f * (tmp1 + tmp2);
    m23 = 2.0f * (tmp1 - tmp2);    
	
	return *this;
}

Transform3& Transform3::SetTranslation(const vec3& translation)
{
	m14 = translation.x;
	m24 = translation.y;
	m34 = translation.z;
	
	return *this;
}

// getter
mat3 Transform3::GetRotation(void) const
{
	mat3 r;

	r.m11 = m11;
	r.m12 = m12;
	r.m13 = m13;

	r.m21 = m21;
	r.m22 = m22;
	r.m23 = m23;

	r.m31 = m31;
	r.m32 = m32;
	r.m33 = m33;

	return r;
}

vec3 Transform3::GetTranslation(void) const
{
	vec3 r;

	r.x = m14;
	r.y = m24;
	r.z = m34;

	return r;
}