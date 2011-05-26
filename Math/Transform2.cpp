//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Transform2.h"

// constructors
Transform2::Transform2(void) : Matrix3x3()
{

}

Transform2::Transform2(const Vector2& translation, real radians)
{
	SetRotation(radians);
	SetTranslation(translation);
		
	m31 = 0;
	m32 = 0;
	m33 = 1;
}
	
// vector arithmetics
Vector2 Transform2::operator * (const Vector2& v) const
{
	Vector2 r;
	
	r.x = m11 * v.x + m12 * v.y + m13;
	r.y = m21 * v.x + m22 * v.y + m23;
	
	return r;
}

Vector2 operator * (const Vector2& v, const Transform2& t)
{
	Vector2 r;
	
	r.x = t.m11 * v.x + t.m12 * v.y + t.m13;
	r.y = t.m21 * v.x + t.m22 * v.y + t.m23;
	
	return r;
}
	
// methods
Vector2 Transform2::FromWorldToLocal(const Vector2& v) const
{
	Vector2 r;
	
	r.x =  m22 * v.x - m12 * v.y + m12 * m23 - m13 * m22;
	r.y = -m21 * v.x + m11 * v.y + m13 * m21 - m11 * m23;
	
	return r;
}

Vector2 Transform2::FromLocalToWorld(const Vector2& v) const
{
	Vector2 r;
	
	r.x = m11 * v.x + m12 * v.y + m13;
	r.y = m21 * v.x + m22 * v.y + m23;
	
	return r;
}

// setter
Transform2& Transform2::SetRotation(real radians)
{
	m11 =  cos(radians);
	m12 = -sin(radians);
	m21 = -m12;
	m22 =  m11;	
	
	return *this;
}

Transform2& Transform2::SetTranslation(const Vector2& translation)
{
	m13 = translation.x;
	m23 = translation.y;
	
	return *this;
}