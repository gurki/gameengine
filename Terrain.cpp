//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Terrain.h"
#include "Timer.h"
#include "Color.h"
#include "Sphere.h"

// constructors
Terrain::Terrain(real width, real height, real depth)
{
	dimensions.x = inf(width, 0.0f);
	dimensions.y = height;
	dimensions.z = inf(depth, 0.0f);
	
	SetTileSize(1.0f, 1.0f);
	SetPlane();
}

Terrain::~Terrain(void)
{
	if(vertices != 0)
	{
		delete[] vertices;
	}

	if(normals != 0)
	{
		delete[] normals;
	}
}

// methods
void Terrain::Render(void) const
{
	real h1 = 0.0f;
	real h2 = 0.0f;

	real height = maxHeight - minHeight;
	height = (height == 0 ? 1 : height);

	for(uint y = 0; y < rows - 1; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for(uint x = 0; x < cols; x++)
		{
			h1 = (vertices[(y + 0) * cols + x].y / height) + 0.5f;
			h2 = (vertices[(y + 1) * cols + x].y / height) + 0.5f;

			Color::WithHLS(h1, 0.5f, 1.0f).Bind();
			glNormal3fv(normals[(y + 0) * cols + x].v);
			glVertex3fv(vertices[(y + 0) * cols + x].v);
			
			Color::WithHLS(h2, 0.5f, 1.0f).Bind();
			glNormal3fv(normals[(y + 1) * cols + x].v);
			glVertex3fv(vertices[(y + 1) * cols + x].v);
		}

		glEnd();
	}
}

void Terrain::RenderBoundingBox(void) const
{
	real dx = dimensions.x * 0.5f;
	real dy = dimensions.y * 0.5f;
	real dz = dimensions.z * 0.5f;

	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);
	
	Color::WithWhite().Bind();

	glBegin(GL_LINE_LOOP);

		glVertex3f(-dx, dy, dz);
		glVertex3f( dx, dy, dz);
		glVertex3f( dx, dy,-dz);
		glVertex3f(-dx, dy,-dz);

	glEnd();

	glBegin(GL_LINE_LOOP);

		glVertex3f(-dx,-dy, dz);
		glVertex3f( dx,-dy, dz);
		glVertex3f( dx,-dy,-dz);
		glVertex3f(-dx,-dy,-dz);

	glEnd();

	glBegin(GL_LINES);

		glVertex3f(-dx, -dy, dz);
		glVertex3f(-dx,  dy, dz);

		glVertex3f(-dx, -dy,-dz);
		glVertex3f(-dx,  dy,-dz);

		glVertex3f( dx, -dy, dz);
		glVertex3f( dx,  dy, dz);

		glVertex3f( dx, -dy,-dz);
		glVertex3f( dx,  dy,-dz);

	glEnd();

	glPopAttrib();
}

void Terrain::Erode(uint strength)
{
	for(uint i = 0; i < (uint)ceil(strength * 0.25f); i++)
	{
		switch (strength % 4)
		{
			case 1:
				Filter::Gaussian1().ApplyNormToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 2:
				Filter::Gaussian2().ApplyNormToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 3:
				Filter::Gaussian3().ApplyNormToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 0:
				Filter::Gaussian4().ApplyNormToData((real*)vertices, rows, cols * 3, 1, 3);
				break;
		}
	}
		
	UpdateExtents();
	UpdateNormals();
	Balance();
}

void Terrain::Smooth(uint strength)
{
	real height = maxHeight - minHeight;

	for(uint i = 0; i < (uint)ceil(strength * 0.25f); i++)
	{
		switch (strength % 4)
		{
			case 1:
				Filter::Gaussian1().ApplyToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 2:
				Filter::Gaussian2().ApplyToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 3:
				Filter::Gaussian3().ApplyToData((real*)vertices, rows, cols * 3, 1, 3);
				break;

			case 0:
				Filter::Gaussian4().ApplyToData((real*)vertices, rows, cols * 3, 1, 3);
				break;
		}
	}
		
	UpdateExtents();		
	SetHeight(height);
	Balance();
}

void Terrain::GenerateRandomTerrain(void)
{
	static uint precision = 1000;
	static real inversePrecision = 1.0f / precision;

	for(uint i = 0; i < rows * cols; i++)
	{
		vertices[i].y = dimensions.y * (rand() % precision - precision * 0.5f) * inversePrecision;
	}

	UpdateExtents();
	UpdateNormals();

	Balance();
}

// setter
void Terrain::SetPlane(void)
{
	maxHeight = 0.0f;
	minHeight = 0.0f;

	for(uint y = 0; y < rows; y++)
	{
		for(uint x = 0; x < cols; x++)
		{
			vertices[y * cols + x].y = 0.0f;
			normals[y * cols + x] = vec3::Up();
		}
	}
}

void Terrain::SetHeight(real height)
{
	real k = height / (maxHeight - minHeight);
	
	for(uint i = 0; i < rows * cols; i++)
	{
		vertices[i].y *= k;
	}

	UpdateExtents();
	UpdateNormals();
}

void Terrain::SetTileSize(real width, real depth)
{
	tileSize.x = inf(width, 0.0f);
	tileSize.y = inf(depth, 0.0f);
	
	cols = round(dimensions.x / tileSize.x);
	rows = round(dimensions.z / tileSize.y);

	tileSize.x = dimensions.x / cols;
	tileSize.y = dimensions.z / rows;

	this->~Terrain();

	vertices = new vec3[this->rows * this->cols];
	normals = new vec3[this->rows * this->cols];

	for(uint y = 0; y < rows; y++)
	{
		for(uint x = 0; x < cols; x++)
		{
			vertices[y * cols + x].x = x * tileSize.x - dimensions.x * 0.5f;
			vertices[y * cols + x].z = y * tileSize.y - dimensions.z * 0.5f;
		}
	}

	SetPlane();
}

// getter
vec3 Terrain::GetClosestGridPoint(const vec3& point)
{
	return vec3::Zero();
}

// hidden methods
void Terrain::Normalize(void)
{
	real inverseHeight = 1.0f / (maxHeight - minHeight);

	for(uint i = 0; i < rows * cols; i++)
	{
		vertices[i].y *= inverseHeight;
	}

	UpdateExtents();
}

void Terrain::Balance(void)
{
	for(uint i = 0; i < rows * cols; i++)
	{
		vertices[i].y -= midHeight;
	}

	maxHeight += midHeight;
	minHeight += midHeight;
	midHeight = 0.0f;
}

void Terrain::UpdateNormals(void)
{
	uint index;
	vec3 u, l, r, d;

	// loop through all normals
	for(uint y = 0; y < rows; y++)
	{
		for(uint x = 0; x < cols; x++)
		{
			// current index in array
			index = y * cols + x;

			// left tangent
			if(x > 0)
			{
				l = vertices[index - 1] - vertices[index];
			}
			else
			{
				l = vec3::Zero();
			}

			// up tangent
			if(y > 0)
			{
				u = vertices[index - cols] - vertices[index];
			}
			else
			{
				u = vec3::Zero();
			}

			// right tangent
			if(x < cols - 1)
			{
				r = vertices[index + 1] - vertices[index];
			}
			else
			{
				r = vec3::Zero();
			}

			// down tangent
			if(y < rows - 1)
			{
				d = vertices[index + cols] - vertices[index];
			}
			else
			{
				d = vec3::Zero();
			}

			// calculate weighted normal
			normals[index] = u.Cross(l) + r.Cross(u) + d.Cross(r) + l.Cross(d);
			normals[index].Normalise();
		}
	}
}

void Terrain::UpdateExtents(void)
{
	maxHeight = 0.0f;
	minHeight = 0.0f;
	midHeight = 0.0f;

	for(uint i = 0; i < rows * cols; i++)
	{
		midHeight += vertices[i].y;

		if(vertices[i].y > maxHeight)
		{
			maxHeight = vertices[i].y;
		}

		if(vertices[i].y < minHeight)
		{
			minHeight = vertices[i].y;
		}
	}

	midHeight /= rows * cols;
}