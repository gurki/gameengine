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

Box::Box(const vec3& position, real width, real height, real depth) : Object3(position)
{
	SetDimensions(width, height, depth);
}

void Box::Render(void) const
{
	material.Bind();

	glPushMatrix();
	glMultMatrixf(modelMatrix.v);

	glBegin(GL_TRIANGLE_STRIP);
		
	// front
		glNormal3f(0.0, 0.0,-1.0);
		glVertex3f(-dim.x, dim.y,-dim.z); // upper left
		glVertex3f(-dim.x,-dim.y,-dim.z); // lower left
		glVertex3f( dim.x, dim.y,-dim.z); // upper right
		glVertex3f( dim.x,-dim.y,-dim.z); // lower right
		
	// right
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f( dim.x, dim.y,-dim.z); // upper left
		glVertex3f( dim.x,-dim.y,-dim.z); // lower left
		glVertex3f( dim.x, dim.y, dim.z); // upper right
		glVertex3f( dim.x,-dim.y, dim.z); // lower right

	// back
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f( dim.x, dim.y, dim.z); // upper left
		glVertex3f( dim.x,-dim.y, dim.z); // lower left
		glVertex3f(-dim.x, dim.y, dim.z); // upper right
		glVertex3f(-dim.x,-dim.y, dim.z); // lower right

	// left
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-dim.x, dim.y, dim.z); // upper left
		glVertex3f(-dim.x,-dim.y, dim.z); // lower left
		glVertex3f(-dim.x, dim.y,-dim.z); // upper right
		glVertex3f(-dim.x,-dim.y,-dim.z); // lower right

	glEnd();

	// top
	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-dim.x, dim.y,-dim.z);
		glVertex3f( dim.x, dim.y,-dim.z);
		glVertex3f(-dim.x, dim.y, dim.z);
		glVertex3f( dim.x, dim.y, dim.z);

	glEnd();

	// bottom
	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0,-1.0, 0.0);
		glVertex3f( dim.x,-dim.y, dim.z);
		glVertex3f(-dim.x,-dim.y, dim.z);
		glVertex3f( dim.x,-dim.y,-dim.z);
		glVertex3f(-dim.x,-dim.y,-dim.z);

	glEnd();

	glPopMatrix();
}

// setter
void Box::SetDimensions(real width, real height, real depth)
{
	width  *= 0.5f;
	height *= 0.5f;
	depth  *= 0.5f;
	
	dim.x = inf(width, 0);
	dim.y = inf(height, 0);
	dim.z = inf(depth, 0);
}
		
// getter
vec3 Box::GetDimensions(void) const
{
	return dim * 2.0f;
}

real Box::GetBoundingSphereRadius(void) const
{
	return dim.Magnitude();
}