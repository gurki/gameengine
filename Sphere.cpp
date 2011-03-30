//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Sphere.h"
#include "Color.h"
#include "Transform2.h"
#include "Vector2.h"

Sphere::Sphere(void) : Object3()
{
	SetRadius(0.5f);
}

Sphere::Sphere(const vec3& position, real radius) : Object3(position)
{
	SetRadius(radius);
}

void Sphere::Render(void) const
{
	static const uint n(20); // iterations
	static const real alpha(C_2PI / n); // partial angle
	static const trans2 rot(vec2::Zero(), alpha); // rotation by alpha
	static const real d(sin(alpha) * radius * 0.5); // half size of plate 
	const uint k = floor(n * 0.25f);
	static vec2 v[k];
	
	real y0 = -d;
	real x0 = cos(alpha) * radius;
	
	glPushMatrix();
	glMultMatrixf(world.v);

	// y-axis ring
	Color::WithOrange().Bind();
	
	vec2 p = vec2(x0, y0); // point to rotate

	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i <= n; i++)
		{
			p = p * rot;
			
			glNormal3f(p.x, 0, p.y);
			glVertex3f(p.x,-d, p.y);
			glVertex3f(p.x, d, p.y);
		}
	
	glEnd();
	
	// x-axis ring
	Color::WithGreen().Bind();
		
	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.5f; i++)
		{
			p = p * rot;
			
			glNormal3f( 0, p.y, p.x);
			glVertex3f(-d, p.y, p.x);
			glVertex3f( d, p.y, p.x);
		}
	
	glEnd();
	
	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.5f; i++)
		{
			p = p * rot;
			
			glNormal3f( 0,-p.y, p.x);
			glVertex3f(-d,-p.y, p.x);
			glVertex3f( d,-p.y, p.x);
		}
	
	glEnd();
	
	// z-axis ring
	Color::WithPurple().Bind();
		
	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.25f; i++)
		{
			p = p * rot;
			
			glNormal3f(p.y, p.x, 0);
			glVertex3f(p.y, p.x,-d);
			glVertex3f(p.y, p.x, d);
		}
	
	glEnd();
	
	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.25f; i++)
		{
			p = p * rot;
			
			glNormal3f(p.y,-p.x, 0);
			glVertex3f(p.y,-p.x,-d);
			glVertex3f(p.y,-p.x, d);
		}
	
	glEnd();

	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.25f; i++)
		{
			p = p * rot;
			
			glNormal3f(-p.y, p.x, 0);
			glVertex3f(-p.y, p.x,-d);
			glVertex3f(-p.y, p.x, d);
		}
	
	glEnd();
	
	p = vec2(x0, y0);
	
	glBegin(GL_TRIANGLE_STRIP);
	
		for(uint i = 0; i < n * 0.25f; i++)
		{
			p = p * rot;
			
			glNormal3f(-p.y,-p.x, 0);
			glVertex3f(-p.y,-p.x,-d);
			glVertex3f(-p.y,-p.x, d);
		}
	
	glEnd();
		
	glPopMatrix();
}

void Sphere::SetRadius(real radius)
{
	this->radius = inf(radius, 0);
}
		
// getter
real Sphere::GetRadius(void) const
{
	return radius;
}

