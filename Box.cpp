//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Box.h"
#include "Color.h"
Box::Box(void) : Object3()
{
	SetDimensions(1, 1, 1);
}

Box::Box(const vec3& position, const vec3& dimensions) : Object3(position)
{
	SetDimensions(dimensions);
}

void Box::Render(void) const
{
	real x0 = - dim.x / 2.0;
	real x1 = - x0;

	real y0 = - dim.y / 2.0;
	real y1 = - y0;

	real z0 = - dim.z / 2.0;
	real z1 = - z0;

	glPushMatrix();
	glMultMatrixf(world.v);

	glBegin(GL_TRIANGLE_STRIP);
		
	// front
		glNormal3f(0.0, 0.0,-1.0);
		glVertex3f(x0, y1, z0); // upper left
		glVertex3f(x0, y0, z0); // lower left
		glVertex3f(x1, y1, z0); // upper right
		glVertex3f(x1, y0, z0); // lower right
		
	// right
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(x1, y1, z0); // upper left
		glVertex3f(x1, y0, z0); // lower left
		glVertex3f(x1, y1, z1); // upper right
		glVertex3f(x1, y0, z1); // lower right

	// back
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(x1, y1, z1); // upper left
		glVertex3f(x1, y0, z1); // lower left
		glVertex3f(x0, y1, z1); // upper right
		glVertex3f(x0, y0, z1); // lower right

	// left
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(x0, y1, z1); // upper left
		glVertex3f(x0, y0, z1); // lower left
		glVertex3f(x0, y1, z0); // upper right
		glVertex3f(x0, y0, z0); // lower right

	glEnd();

	// top
	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(x0, y1, z0);
		glVertex3f(x1, y1, z0);
		glVertex3f(x0, y1, z1);
		glVertex3f(x1, y1, z1);

	glEnd();

	// bottom
	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0,-1.0, 0.0);
		glVertex3f(x1, y0, z1);
		glVertex3f(x0, y0, z1);
		glVertex3f(x1, y0, z0);
		glVertex3f(x0, y0, z0);

	glEnd();

	glPopMatrix();
}

// setter
void Box::SetDimensions(real width, real height, real depth)
{
	dim.x = inf(width, 0);
	dim.y = inf(height, 0);
	dim.z = inf(depth, 0);
}

void Box::SetDimensions(const vec3& dimensions)
{
	dim.x = inf(dimensions.x, 0);
	dim.y = inf(dimensions.y, 0);
	dim.z = inf(dimensions.z, 0);
}
		
// getter
vec3 Box::GetDimensions(void) const
{
	return dim;
}