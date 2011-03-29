//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Object2.h"

// constructors
Object2::Object2(void)
{
	SetPosition(0, 0);
	SetRotation(0);
}

Object2::Object2(real x, real y)
{
	SetPosition(x, y);
	SetRotation(0);
}

Object2::Object2(const vec2& position)
{
	SetPosition(position);
	SetRotation(0);
}
		
// methods
void Object2::Render(void) const
{
	glBegin(GL_POINTS);
		
		glVertex2fv(pos.v);
		
	glEnd();
}
		
// setter
void Object2::SetPosition(real x, real y)
{
	this->pos = vec2(x, y);
	this->trans.SetTranslation(this->pos);
}

void Object2::SetPosition(const vec2& position)
{
	this->pos = position;
	this->trans.SetTranslation(this->pos);
}

void Object2::SetRotation(real radians)
{
	this->rot = radians;
	this->trans.SetRotation(this->rot);
}

void Object2::SetTransformation(const trans2& t)
{
	trans = t;
}
		
// getter
vec2 Object2::GetPosition(void) const
{
	return pos;
}

real Object2::GetRotation(void) const
{
	return rot;
}

trans2 Object2::GetTransformation(void) const
{
	return trans;
}