//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifdef TEXTURES

#include "Terrain.h"
#include "Timer.h"
#include "Color.h"
#include "Sphere.h"

real FaultLineStep(real distance, real offset);
real FaultLinePlateau(real distance, real size);
real FaultLineSine(real distance, real size);
real FaultLineCosine(real distance, real size);

// constructors
Terrain::Terrain(real width, real height, real depth)
{
	dimensions.x = inf(width, 0.0f);
	dimensions.y = height;
	dimensions.z = inf(depth, 0.0f);
}

Terrain::~Terrain(void)
{
	heightmap.~Texture();
	normalmap.~Texture();

	if(indices != 0)
	{
		delete[] indices;
		indices = 0;
	}

	if(vertices != 0)
	{
		delete[] vertices;
		vertices = 0;
	}

	if(normals != 0)
	{
		delete[] normals;
		normals = 0;
	}

	if(texcoords != 0)
	{
		delete[] texcoords;
		texcoords = 0;
	}
}

// methods
void Terrain::Render(void) const
{
	glPushMatrix();
	glMultMatrixf(modelMatrix.v);

	uint index1;
	uint index2;

	vec2 tex1, tex2;
	vec3 pos1, pos2;

	for(uint y = 0; y < heightmap.GetHeight() - 1; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for(uint x = 0; x < heightmap.GetWidth(); x++)
		{
			index1 = y * heightmap.GetWidth() + x;
			index2 = index1 + heightmap.GetWidth();

			tex1.x = (real)x / (real)heightmap.GetWidth();
			tex1.y = (real)y / (real)heightmap.GetHeight();

			pos1.x = dimensions.x * x / heightmap.GetWidth() - dimensions.x * 0.5f;
			pos1.y = dimensions.y * heightmap.GetData()[index1];
			pos1.z = dimensions.z * y / heightmap.GetHeight() - dimensions.z * 0.5f;

			tex2.x = tex1.x;
			tex2.y = (real)(y + 1.0f) / (real)heightmap.GetHeight();

			pos2.x = pos1.x;
			pos2.y = dimensions.y * heightmap.GetData()[index2];
			pos2.z = dimensions.z * (y + 1.0f) / heightmap.GetHeight() - dimensions.z * 0.5f;

			glNormal3fv(normalmap.GetData() + 3 * index1);
			glTexCoord2fv(tex1.v);
			glVertex3fv(pos1.v);

			glNormal3fv(normalmap.GetData() + 3 * index2);
			glTexCoord2fv(tex2.v);
			glVertex3fv(pos2.v);
		}

		glEnd();
	}

	glPopMatrix();
}

void Terrain::RenderIndexed(void) const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	for(uint i = 0; i < heightmap.GetHeight() - 1; i++)
	{
		glDrawRangeElements(GL_TRIANGLE_STRIP, i * heightmap.GetWidth(), i * (heightmap.GetWidth() + 1), heightmap.GetWidth() * 2, GL_UNSIGNED_INT, indices);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Terrain::RenderVBO(void) const
{

}

void Terrain::UpdateMaps(void) 
{
	if(indices == 0)
	{
		indices = new uint[heightmap.GetWidth() * (heightmap.GetHeight() * 2 - 1)];
		vertices = new vec3[heightmap.GetSize()];
		normals = new vec3[heightmap.GetSize()];
		texcoords = new vec2[heightmap.GetSize()];
	}

	uint index;

	for(uint y = 0; y < heightmap.GetHeight(); y++)
	{
		for(uint x = 0; x < heightmap.GetWidth(); x++)
		{
			index = y * heightmap.GetWidth() + x;

			if(y < heightmap.GetHeight() - 1)
			{
				indices[index * 2 + 0] = index;
				indices[index * 2 + 1] = index + heightmap.GetWidth();
			}

			texcoords[index].x = x / (real)heightmap.GetWidth();
			texcoords[index].y = y / (real)heightmap.GetHeight();

			vertices[index].x = dimensions.x * (x / (real)heightmap.GetWidth() - 0.5f);
			vertices[index].y = dimensions.y * heightmap.GetData()[index];
			vertices[index].z = dimensions.z * (y / (real)heightmap.GetHeight() - 0.5f);

			normals[index].x = normalmap.GetData()[index * 3 + 0];
			normals[index].y = normalmap.GetData()[index * 3 + 1];
			normals[index].z = normalmap.GetData()[index * 3 + 2];
		}
	}
}

void Terrain::RenderNormals(void) const
{
	glPushMatrix();
	glMultMatrixf(modelMatrix.v);
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);

	uint index;
	vec3 pos1, pos2;

	Color::WithGreen().Bind();

	for(uint y = 0; y < heightmap.GetHeight(); y++)
	{
		for(uint x = 0; x < heightmap.GetWidth(); x++)
		{
			glBegin(GL_LINES);

			index = y * heightmap.GetWidth() + x;
			
			pos1.x = dimensions.x * x / heightmap.GetWidth() - dimensions.x * 0.5f;
			pos1.y = dimensions.y * heightmap.GetData()[index];
			pos1.z = dimensions.z * y / heightmap.GetHeight() - dimensions.z * 0.5f;

			pos2.x = pos1.x + normalmap.GetData()[3 * index + 0];
			pos2.y = pos1.y + normalmap.GetData()[3 * index + 1];
			pos2.z = pos1.z + normalmap.GetData()[3 * index + 2];

			glVertex3fv(pos1.v);
			glVertex3fv(pos2.v);

			glEnd();
		}
	}

	glPopAttrib();
	glPopMatrix();
}

void Terrain::SaveHeightmap(const char* filename)
{
	heightmap.Save(filename);
	/*
	char buffer[256];

	sprintf_s<256>(buffer, "%s_heightmap.png", filename);
	heightmap.Save(buffer);

	sprintf_s<256>(buffer, "%s_normalmap.png", filename);
	normalmap.Save(buffer);
	
	Texture tex;
	tex.GenerateTexture(normalmap.GetWidth(), normalmap.GetHeight(), 4);

	real x, y;

	for(uint i = 0; i < normalmap.GetSize(); i++)
	{
		x = normalmap.GetData()[3 * i + 0];
		y = normalmap.GetData()[3 * i + 1];

		tex.GetData()[4 * i + 0] = 127.5f * (x + 1.0f);
		tex.GetData()[4 * i + 1] = 255.0f * frac(127.5f * (x + 1.0f));
		tex.GetData()[4 * i + 2] = 127.5f * (y + 1.0f);
		tex.GetData()[4 * i + 3] = 255.0f * frac(127.5f * (y + 1.0f));	
	}

	tex.Save(buffer);
	*/
}

void Terrain::LoadHeightmap(const char* filename)
{
	heightmap.Load(filename);

	this->CalculateNormals();
	/*
	char buffer[256];
	
	sprintf_s<256>(buffer, "%s_heightmap.png", filename);
	heightmap.Load(buffer);
	
	sprintf_s<256>(buffer, "%s_normalmap.png", filename);
	normalmap.Load(buffer);
	*/
	/*
	Texture tex;
	tex.Load(buffer);

	real R, G, B, A;
	real x, y;

	for(uint i = 0; i < tex.GetSize(); i++)
	{
		R = tex.GetData()[4 * i + 0];
		G = tex.GetData()[4 * i + 1];
		B = tex.GetData()[4 * i + 2];
		A = tex.GetData()[4 * i + 3];

		x = (R / 127.5f + G / 32512.5f) - 1.0f;
		y = (B / 127.5f + A / 32512.5f) - 1.0f;

		normalmap.GetData()[3 * i + 0] = x;
		normalmap.GetData()[3 * i + 1] = y;
		normalmap.GetData()[3 * i + 2] = sqrt(1.0f - x * x - y * y);
	}
	*/
}

// terrain generation
void Terrain::GenerateRandom(uint steps)
{
	if(heightmap.GetSize() != dimensions.x * dimensions.z)
	{
		heightmap.GenerateTexture(dimensions.x, dimensions.z, 1);
	}

	real inverseSteps = 1.0f / steps;

	for(uint i = 0; i < heightmap.GetSize(); i++)
	{
		heightmap.GetData()[i] = (rand() % steps) * inverseSteps;
	}
	
	this->CalculateNormals();
}

void Terrain::GenerateFaultLine(uint iterations)
{
	this->GenerateFaultLineWithFunction(FaultLineStep, 0, iterations);
}

void Terrain::GenerateFaultLinePlateau(real size, uint iterations)
{
	this->GenerateFaultLineWithFunction(FaultLinePlateau, 0, iterations);
}

void Terrain::GenerateFaultLineSine(real size, uint iterations)
{
	this->GenerateFaultLineWithFunction(FaultLineSine, 0, iterations);
}

void Terrain::GenerateFaultLineCosine(real size, uint iterations)
{
	this->GenerateFaultLineWithFunction(FaultLineCosine, 0, iterations);
}

void Terrain::GenerateFaultLineWithFunction(real (*function)(real distance, real size), real size, uint iterations)
{
	if(heightmap.GetSize() != dimensions.x * dimensions.z)
	{
		heightmap.GenerateTexture(dimensions.x, dimensions.z, 1);
	}
	
	vec2 p0, p1, p2, n;
	real displacement, distance;

	for(uint i = 0; i < iterations; i++)
	{
		p1.x = rand() % heightmap.GetWidth();
		p1.y = rand() % heightmap.GetHeight();

		p2.x = rand() % heightmap.GetWidth();
		p2.y = rand() % heightmap.GetHeight();

		n = p2 - p1;
		n.Normalise();

		displacement = 1.0f - (real)i / (real)iterations;

		for(uint row = 0; row < heightmap.GetHeight(); row++)
		{
			for(uint col = 0; col < heightmap.GetWidth(); col++)
			{
				p0.x = col;
				p0.y = row;

				distance = n.Cross(p1 - p0);
								
				heightmap.GetData()[row * heightmap.GetWidth() + col] += function(distance, size) * displacement;
			}
		}
	}
	
	this->Normalize();
	this->UpdateMaps();
}

void Terrain::GenerateParticleDeposition(uint series, uint iterations)
{
	if(heightmap.GetSize() != dimensions.x * dimensions.z)
	{
		heightmap.GenerateTexture(dimensions.x, dimensions.z, 1);
	}
	
	uint x, y, direction;

	for(uint s = 0; s < series; s++)
	{
		x = rand() % heightmap.GetWidth();
		y = rand() % heightmap.GetHeight();
	
		for(uint i = 0; i < iterations; i++)
		{
			direction = rand() % 4;

			switch(direction)
			{
				case 0:
					y = (y - 1) % heightmap.GetHeight();
					break;

				case 1:
					x = (x + 1)  % heightmap.GetWidth();
					break;

				case 2:
					y = (y + 1)  % heightmap.GetHeight();
					break;

				default:
					x = (x - 1)  % heightmap.GetWidth();
					break;
			}

			heightmap.GetData()[y * heightmap.GetWidth() + x] += 1.0f;
		}
	}

	this->Normalize();
}

void Terrain::Smooth(uint iterations)
{
	for(uint i = 0; i < iterations; i++)
	{
		Filter::Lowpass().ApplyToData(heightmap.GetData(), heightmap.GetHeight(), heightmap.GetWidth());
	}

	this->CalculateNormals();
}

void Terrain::ApplyFilter(const Filter& filter)
{
	filter.ApplyToData(heightmap.GetData(), heightmap.GetHeight(), heightmap.GetWidth());

	this->CalculateNormals();
}

void Terrain::Normalize(void)
{
	real maxHeight = heightmap.GetData()[0];
	real minHeight = heightmap.GetData()[0];

	for(uint i = 1; i < heightmap.GetSize(); i++)
	{
		if(heightmap.GetData()[i] > maxHeight)
		{
			maxHeight = heightmap.GetData()[i];
		}

		if(heightmap.GetData()[i] < minHeight)
		{
			minHeight = heightmap.GetData()[i];
		}
	}

	if(maxHeight - minHeight != 0)
	{
		for(uint i = 0; i < heightmap.GetSize(); i++)
		{	
			heightmap.GetData()[i] /= (maxHeight - minHeight);
			heightmap.GetData()[i] -= minHeight / (maxHeight - minHeight);	
		}
	}

	this->CalculateNormals();
}

void Terrain::Flatten(void)
{
	memset(heightmap.GetData(), 0, heightmap.GetSize() * sizeof(real));
}

// getter
real Terrain::GetHeightAtPoint(const vec3& point) const
{
	vec3 p = modelMatrix.TransformFromGlobalToLocal(point);

	vec2 d;
	
	d.x = dimensions.x * 0.5f;
	d.y = dimensions.y * 0.5f;

	if(p.x < -d.x || p.x > d.x || p.y < -d.y || p.y > d.y)
	{
		return 0.0f;
	}

	p.x += d.x;
	p.y += d.y;

	p.x /= dimensions.x;
	p.y /= dimensions.y;

	p.x *= heightmap.GetWidth();
	p.y *= heightmap.GetHeight();

	vec2 p1, p2, p3, p4;

	p1.x = floor(p.x);
	p1.y = floor(p.y);

	p2.x = ceil(p.x);
	p2.y = floor(p.y);
	
	p3.x = ceil(p.x);
	p3.y = ceil(p.y);
	
	p4.x = floor(p.x);
	p4.y = ceil(p.y);

	real height = 0.0f;

	height += heightmap.GetData()[(uint)(p1.x * heightmap.GetWidth() + p1.y)];
	height += heightmap.GetData()[(uint)(p2.x * heightmap.GetWidth() + p2.y)];
	height += heightmap.GetData()[(uint)(p3.x * heightmap.GetWidth() + p3.y)];
	height += heightmap.GetData()[(uint)(p4.x * heightmap.GetWidth() + p4.y)];

	height /= 4.0f;

	return height;
}

// hidden methods
void Terrain::CalculateNormals(void)
{
	if(normalmap.GetSize() != heightmap.GetSize())
	{
		normalmap.GenerateTexture(heightmap.GetWidth(), heightmap.GetHeight(), 3);
	}

	uint index;
	vec3 n, u, l, r, d;

	// loop through all normals
	for(uint y = 0; y < heightmap.GetHeight(); y++)
	{
		for(uint x = 0; x < heightmap.GetWidth(); x++)
		{
			// current index in array
			index = y * heightmap.GetWidth() + x;

			// left tangent
			if(x > 0)
			{
				l.x =-1.0f;
				l.y = heightmap.GetData()[index - 1] - heightmap.GetData()[index];
				l.z = 0.0f;
			}
			else
			{
				l = vec3::Zero();
			}

			// up tangent
			if(y > 0)
			{
				u.x = 0.0f;
				u.y = heightmap.GetData()[index - heightmap.GetWidth()] - heightmap.GetData()[index];
				u.z =-1.0f;
			}
			else
			{
				u = vec3::Zero();
			}

			// right tangent
			if(x < heightmap.GetWidth() - 1)
			{
				r.x = 1.0f;
				r.y = heightmap.GetData()[index + 1] - heightmap.GetData()[index];
				r.z = 0.0f;
			}
			else
			{
				r = vec3::Zero();
			}

			// down tangent
			if(y < heightmap.GetHeight() - 1)
			{
				d.x = 0.0f;
				d.y = heightmap.GetData()[index + heightmap.GetWidth()] - heightmap.GetData()[index];
				d.z = 1.0f;
			}
			else
			{
				d = vec3::Zero();
			}

			// calculate weighted normal
			n = u.Cross(l) + r.Cross(u) + d.Cross(r) + l.Cross(d);
			n.Normalise();
			
			memcpy(normalmap.GetData() + 3 * index, &n, sizeof(n));
		}
	}
}

// faulline functions
real FaultLineStep(real distance, real offset)
{
	if(distance >= 0) 
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

real FaultLinePlateau(real distance, real size)
{
	size *= 0.5f;

	if(distance >= size)
	{
		return 1;
	}
	else if(distance <= -size)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

real FaultLineSine(real distance, real size)
{
	size *= 0.5f;

	if(distance >= size)
	{
		return 1;
	}
	else if(distance <= -size)
	{
		return -1;
	}
	else
	{
		return sin(distance * C_PIDIV2 / size);
	}
}

real FaultLineCosine(real distance, real size)
{
	size *= 0.5f;

	if(distance >= size)
	{
		return -1;
	}
	else if(distance <= -size)
	{
		return -1;
	}
	else
	{
		return cos(distance * C_PI / size);
	}
}

#endif