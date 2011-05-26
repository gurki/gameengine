//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Grid3.h"
#include "OpenGL.h"

Grid3::Grid3(void) : Object3()
{
	dim = vec2::One();
	res = vec2::One();
}

Grid3::Grid3(const vec3& position, const quat& rotation, const vec2& dimensions, const vec2& resolution) : Object3(position)
{
	dim = dimensions;
	res = resolution;
}

void Grid3::SetDimensions(real x, real y)
{
	dim = vec2(x, y);
}

void Grid3::SetDimensions(const vec2& dimensions)
{
	dim = dimensions;
}

void Grid3::SetResolution(real x, real y)
{
	res = vec2(x, y);
}

void Grid3::SetResolution(const vec2& resolution)
{
	res = resolution;
}

void Grid3::Render(void)
{
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	int nx = floor(dim.x / res.x);
	int ny = floor(dim.y / res.y);

	real x0 = - dim.x / 2.0;
	real x1 = - x0;

	real y0 = - dim.y / 2.0;
	real y1 = - y0;

	glBegin(GL_LINES);

		for(int x = 0; x < nx; x++)
		{
			glVertex3f(x0 + x * res.x, 0.0, y0);
			glVertex3f(x0 + x * res.x, 0.0, y1);
		}

		glVertex3f(x1, 0.0, y0);
		glVertex3f(x1, 0.0, y1);

		for(int y = 0; y < ny; y++)
		{
			glVertex3f(x0, 0.0, y0 + y * res.y);
			glVertex3f(x1, 0.0, y0 + y * res.y);
		}

		glVertex3f(x0, 0.0, y1);
		glVertex3f(x1, 0.0, y1);

	glEnd();

	glPopAttrib();
}