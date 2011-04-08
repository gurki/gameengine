//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Cylinder.h"
#include "Color.h"
#include "Vector2.h"

#include <fstream>

using namespace std;

Cylinder::Cylinder(void) : Object3()
{
	SetHeight(5.0f);
	SetRadius(0.5f);
}

Cylinder::Cylinder(const vec3& position, real height, real radius) : Object3(position)
{
	SetHeight(height);
	SetRadius(radius);
}

void Cylinder::Render(void) const
{
	static const real n = 20;
	real ratio, n1, n2;

	material.Bind();

	glPushMatrix();
	glMultMatrixf(modelMatrix.v);

	// surface
	glBegin(GL_TRIANGLE_STRIP);

		for(real i = 0; i <= n; i++)
		{
			ratio = C_2PI * (i / n);
			
			n1 = radius * cos(ratio);
			n2 = radius * sin(ratio);

			glNormal3f(n1, 0, n2);
			glVertex3f(n1, height, n2);
			glVertex3f(n1,-height, n2);
		}

	glEnd();

	// top
	glBegin(GL_TRIANGLE_FAN);

		glNormal3f(0, 1, 0);
		glVertex3f(0, height, 0);

		for(real i = 0; i <= n; i++)
		{
			ratio = C_2PI * (i / n);
			
			n1 = radius * cos(ratio);
			n2 = radius * sin(ratio);

			glVertex3f(n1, height, n2);
		}

	glEnd();

	// bottom
	glBegin(GL_TRIANGLE_FAN);

		glNormal3f(0,-1, 0);
		glVertex3f(0,-height, 0);

		for(real i = 0; i <= n; i++)
		{
			ratio = C_2PI * (i / n);
			
			n1 = radius * cos(ratio);
			n2 = radius * sin(ratio);

			glVertex3f(n1,-height, n2);
		}

	glEnd();

	glPopMatrix();
}

// setter
void Cylinder::SetHeight(real height)
{
	height *= 0.5f;
	
	this->height = inf(height, 0);
}

void Cylinder::SetRadius(real radius)
{
	this->radius = inf(radius, 0);
}
		
// getter
real Cylinder::GetHeight(void) const
{
	return height * 2.0f;
}

real Cylinder::GetRadius(void) const
{
	return radius;
}

real Cylinder::GetBoundingSphereRadius(void) const
{
	return sqrt(radius * radius + height * height);
}