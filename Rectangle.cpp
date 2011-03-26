//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Rectangle.h"

// constructors
Rectangle::Rectangle(void) : Object2()
{
	SetDimensions(0, 0);
}

Rectangle::Rectangle(const vec2& position, const vec2& dimensions) : Object2(position)
{
	SetDimensions(position);
}

Rectangle::Rectangle(real x, real y, real width, real height) : Object2(x, y)
{
	SetDimensions(width, height);
}

// methods
void Rectangle::Render(void) const
{	
	glBegin(GL_TRIANGLE_STRIP);
	
		glNormal3f(0, 0, 1);
		
		glVertex2fv( (d[0] * trans).v );
		glVertex2fv( (d[1] * trans).v );
		
		glVertex2fv( (d[3] * trans).v );
		glVertex2fv( (d[2] * trans).v );
	
	glEnd();
	
	glPushAttrib(GL_CURRENT_BIT);
	Color::WithBlack().Bind();
	
		glBegin(GL_LINE_LOOP);
	
			glVertex2fv( (d[0] * trans).v );
			glVertex2fv( (d[1] * trans).v );
		
			glVertex2fv( (d[2] * trans).v );
			glVertex2fv( (d[3] * trans).v );
	
		glEnd();
	
	glPopAttrib();
}

// setter
void Rectangle::SetDimensions(const vec2& dimensions)
{
	dim.x = inf(dimensions.x, 0);
	dim.y = inf(dimensions.y, 0);
	
	vec2 h = dim * 0.5;
	
	d[0] = vec2( h.x,-h.y);
	d[1] = vec2( h.x, h.y);
	d[2] = vec2(-h.x, h.y);
	d[3] = vec2(-h.x,-h.y);
}

void Rectangle::SetDimensions(real width, real height)
{
	dim.x = inf(width, 0);
	dim.y = inf(height, 0);
	
	vec2 h = dim * 0.5;
	
	d[0] = vec2( h.x,-h.y);
	d[1] = vec2( h.x, h.y);
	d[2] = vec2(-h.x, h.y);
	d[3] = vec2(-h.x,-h.y);
}

// getter
vec2 Rectangle::GetDimensions(void) const
{
	return dim;
}

vec2 Rectangle::GetCenter(void) const
{
	return dim * 0.5;
}

real Rectangle::GetRatio(void) const
{
	return dim.x / dim.y;
}