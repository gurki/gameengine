#include "Box3.h"
#include "OpenGL.h"

Box3::Box3(void) : Object3()
{
	dim = vec3(1, 1, 1);
}

Box3::Box3(const vec3& position, const quat& rotation, const vec3& dimensions) : Object3(position, rotation)
{
	dim = dimensions;
}

void Box3::Render(void)
{
/*
	real x0 = - dim.x / 2.0;
	real x1 = - x0;

	real y0 = - dim.y / 2.0;
	real y1 = - y0;

	real z0 = - dim.z / 2.0;
	real z1 = - z0;
*/
	real x0 = 0;
	real x1 = dim.x;

	real y0 = 0;
	real y1 = dim.y;

	real z0 = 0;
	real z1 = dim.z;

	vec3 axis;
	real angle;

	rot.GetAxisAngle(axis, angle);

	glPushMatrix();
	
	glRotatef(angle, axis.x, axis.y, axis.z);
	glTranslatef(pos.x, pos.y, pos.z);

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0, 0.0,-1.0);
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y0, z0);
		glVertex3f(x0, y1, z0);
		glVertex3f(x1, y1, z0);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(x1, y0, z0);
		glVertex3f(x1, y0, z1);
		glVertex3f(x1, y1, z0);
		glVertex3f(x1, y1, z1);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(x1, y0, z1);
		glVertex3f(x0, y0, z1);
		glVertex3f(x1, y1, z1);
		glVertex3f(x0, y1, z1);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(x0, y0, z1);
		glVertex3f(x0, y0, z0);
		glVertex3f(x0, y1, z1);
		glVertex3f(x0, y1, z0);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(x0, y1, z0);
		glVertex3f(x1, y1, z0);
		glVertex3f(x0, y1, z1);
		glVertex3f(x1, y1, z1);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);

		glNormal3f(0.0,-1.0, 0.0);
		glVertex3f(x1, y0, z1);
		glVertex3f(x0, y0, z1);
		glVertex3f(x1, y0, z0);
		glVertex3f(x0, y0, z0);

	glEnd();

	glPopMatrix();
}
