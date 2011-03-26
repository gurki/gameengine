//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Triangle.h"

// constructors
Triangle::Triangle(void) : Object2() 
{
	SetSize(1);
}

Triangle::Triangle(real x, real y, real size) : Object2(x, y)
{
	SetSize(size);
}

Triangle::Triangle(const vec2& position, real size) : Object2(position)
{
	SetSize(size);
}
		
// methods
void Triangle::Render(void) const
{	
	glBegin(GL_TRIANGLES);
	
		glNormal3f(0, 0, 1);
			
		glVertex2fv( (d[0] * trans).v );
		glVertex2fv( (d[1] * trans).v );
		glVertex2fv( (d[2] * trans).v );
	
	glEnd();
	
	glPushAttrib(GL_CURRENT_BIT);
	Color::WithBlack().Bind();
	
		glBegin(GL_LINE_LOOP);
	
		glVertex2fv( (d[0] * trans).v );
		glVertex2fv( (d[1] * trans).v );
		glVertex2fv( (d[2] * trans).v );
	
	glEnd();
		
	glPopAttrib();
}
		 
// setter
void Triangle::SetSize(real size)
{
	this->size = inf(size, 0);
	
	real s = size * 0.5f;
	real h = C_SQRT3DIV2 * s;
	
	d[0] = vec2(-s,-h);
	d[1] = vec2( s,-h);
	d[2] = vec2( 0, h);
}
		
// getter
real Triangle::GetSize(void) const
{
	return size;
}