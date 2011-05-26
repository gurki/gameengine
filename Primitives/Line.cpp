//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Line.h"

// constructors
Line::Line(void) : Object2() 
{
	SetLength(1);
}

Line::Line(real x, real y, real length) : Object2(x, y)
{
	SetLength(length);
}

Line::Line(const vec2& position, real length) : Object2(position)
{
	SetLength(length);
}
		
// methods
void Line::Render(void) const
{	
	glBegin(GL_LINES);
			
		glVertex2fv( (d[0] * trans).v );
		glVertex2fv( (d[1] * trans).v );
	
	glEnd();
}
		 
// setter
void Line::SetLength(real length)
{
	this->length = inf(length, 0);
	
	real l = this->length / 2.0;
	
	d[0] = vec2(-l, 0);
	d[1] = vec2( l, 0);
}
		
// getter
real Line::GetLength(void) const
{
	return length;
}