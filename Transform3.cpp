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
	
// methods
vec3 Transform3::TransformFromGlobalToLocal(const vec3& v) const
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

vec3 Transform3::TransformFromLocalToGlobal(const vec3& v) const
{
	vec3 r;
	
	r.x = v.x * m11 + v.y * m12 + v.z * m13 + m14;
	r.y = v.x * m21 + v.y * m22 + v.z * m23 + m24;
	r.z = v.x * m31 + v.y * m32 + v.z * m33 + m34;
	
	return r;
}


vec3 Transform3::RotateFromLocalToGlobal(const vec3& v) const
{
	vec3 r;
	
	r.x = v.x * m11 + v.y * m12 + v.z * m13;
	r.y = v.x * m21 + v.y * m22 + v.z * m23;
	r.z = v.x * m31 + v.y * m32 + v.z * m33;
	
	return r;
}

mat3 Transform3::RotateFromLocalToGlobal(const mat3& v) const
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
	
	return r * v * r.Transposed();
}

vec3 Transform3::ProjectPerspectiveFromLocalToGlobal(const vec3& v) const
{
	vec3 r;

	r.x = m11 * v.x + m13 * v.z;
	r.y = m22 * v.y + m23 * v.z;
	r.z = m33 * v.z + m34;
	
	return r;
}

vec3 Transform3::ProjectOrthographicFromLocalToGlobal(const vec3& v) const
{
	vec3 r;

	r.x = m11 * v.x + m14;
	r.y = m22 * v.y + m24;
	r.z = m33 * v.z + m34;
	
	return r;
}

// setter
Transform3& Transform3::SetRotation(const quat& q)
{
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

Transform3& Transform3::SetRotationAboutAxis(const vec3& axis, real radians)
{
	vec3 n = axis.Normalised();
	real c = cos(radians);
	real s = sin(radians);
	real t = 1.0f - c; 
	
	m11 = t * n.x * n.x + c;
	m12 = t * n.x * n.y - n.z * s;
	m13 = t * n.x * n.z + n.y * s;
	
	m21 = t * n.x * n.y + n.z * s;
	m22 = t * n.y * n.y + c;
	m23 = t * n.y * n.z - n.x * s;
	
	m31 = t * n.x * n.z - n.y * s;
	m32 = t * n.y * n.z + n.x * s;
	m33 = t * n.z * n.z + c;
	
	return *this; 
}

Transform3& Transform3::SetRotationWithOrthogonalAxis(const vec3& right, const vec3& up, const vec3& forward)
{
	m11 = right.x;
	m12 = right.y;
	m13 = right.z;

	m21 = up.x;
	m22 = up.y;
	m23 = up.z;

	m31 = forward.x;
	m32 = forward.y;
	m33 = forward.z;

	return *this;
}

Transform3& Transform3::SetTranslation(const vec3& translation)
{
	m14 = translation.x;
	m24 = translation.y;
	m34 = translation.z;
	
	return *this;
}

Transform3& Transform3::SetPerspectiveProjection(real fov, real aspect, real near, real far)
{
	real temp = 1.0f / tanr(fov * 0.5f);

	m11 = temp / aspect;
	m12 = 0.0f;
	m13 = 0.0f;
	m14 = 0.0f;

	m21 = 0.0f;
	m22 = temp;
	m23 = 0.0f;
	m24 = 0.0f;

	temp = near - far;

	m31 = 0.0f;
	m32 = 0.0f;
	m33 = (near + far) / temp;
	m34 = (2.0f * near * far) / temp;

	m41 = 0.0f;
	m42 = 0.0f;
	m43 =-1.0f;
	m44 = 0.0f;

	return *this;
}

Transform3& Transform3::SetPerspectiveProjection(real left, real right, real bottom, real top, real near, real far)
{
	real temp = right - left;
	real near2 = 2.0f * near;

	m11 = near2 / temp;
	m12 = 0.0f;
	m13 = (right + left) / temp;
	m14 = 0.0f;

	temp = top - bottom;
	
	m21 = 0.0f;
	m22 = near2 / temp;
	m23 = (top + bottom) / temp;
	m24 = 0.0f;

	temp = near - far;

	m31 = 0.0f;
	m32 = 0.0f;
	m33 = (near + far) / temp;
	m34 = (near2 * far) / temp;

	m41 = 0.0f;
	m42 = 0.0f;
	m43 =-1.0f;
	m44 = 0.0f;

	return *this;
}

Transform3& Transform3::SetOrthographicProjection(real left, real right, real bottom, real top, real near, real far)
{
	real temp = right - left;

	m11 = 2 / temp;
	m12 = 0.0f;
	m13 = 0.0f;
	m14 = - (right + left) / temp;

	temp = top - bottom;
	
	m21 = 0.0f;
	m22 = 2 / temp;
	m23 = 0.0f;
	m24 = - (top + bottom) / temp;

	temp = near - far;

	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 2 / temp;
	m34 = - (near + far) / temp;

	m41 = 0.0f;
	m42 = 0.0f;
	m43 = 0.0f;
	m44 = 1.0f;

	return *this;
}

Transform3& Transform3::SetLookAt(const vec3& eye, const vec3& center, const vec3& up)
{
	vec3 f = center - eye;
	f.Normalise();

	vec3 s = f.Cross(up);
	s.Normalise();

	vec3 u = s.Cross(f);
	
	m11 = s.x; 	
	m13 = s.y; 	
	m13 = s.z; 	
	m14 =-s.x * eye.x - s.y * eye.y - s.z * eye.z;

	m21 = u.x; 	
	m23 = u.y; 	
	m23 = u.z; 	
	m24 =-u.x * eye.x - u.y * eye.y - u.z * eye.z;

	m31 =-f.x; 	
	m33 =-f.y; 	
	m33 =-f.z; 	
	m34 = f.x * eye.x + f.y * eye.y + f.z * eye.z;
	
	m41 = 0.0f;
	m42 = 0.0f;
	m43 = 0.0f;
	m44 = 1.0f;
	
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