//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Circle.h"

// constructor
Circle::Circle(void) : Object2()
{
	SetRadius(1);
}

Circle::Circle(real x, real y, real radius) : Object2(x, y)
{
	SetRadius(radius);
}

Circle::Circle(const vec2& position, real radius) : Object2(position)
{
	SetRadius(radius);
}

// methods
void Circle::Render(void) const
{
	real a;
	vec2 d;
	
	real precission = limit(0.2 * radius, 25, 250);
		
	glBegin(GL_TRIANGLE_FAN);
	
		glNormal3f(0, 0, 1);
		
		glVertex2fv( (d * trans).v );
		
		a = 0;
	 
		for(uint i = 0; i <= precission; i++)
		{
			a = (i / precission) * C_2PI;
			d = radius * vec2( cos(a), sin(a) ) * trans;
			
			glVertex2fv(d.v);
		}
	
	glEnd();
	
	glPushAttrib(GL_CURRENT_BIT);
	Color::WithBlack().Bind();
	
	glBegin(GL_LINE_LOOP);
	
		a = 0;
	 
		for(uint i = 0; i < precission; i++)
		{
			a = (i / precission) * C_2PI;
			d = radius * vec2(cos(a), sin(a)) * trans;
			
			glVertex2fv(d.v);
		}
	
	glEnd();
}

// setter
void Circle::SetRadius(real radius)
{
	this->radius = inf(radius, 0);
}

// getter
real Circle::GetRadius(void) const
{
	return radius;
}
