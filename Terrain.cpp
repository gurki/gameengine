//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Terrain.h"
#include "Timer.h"

// constructors
Terrain::Terrain(uint rows, uint cols)
{
	this->rows = inf(rows, 0.0f);
	this->cols = inf(cols, 0.0f);
	
	height = 1.0f;
	heights = new real[this->rows * this->cols];

	Reset();
}

Terrain::~Terrain(void)
{
	delete[] heights;
}

// methods
void Terrain::Render(void) const
{
	real dx = cols * 0.5f;
	real dy = rows * 0.5f;

	for(uint y = 0; y < rows - 1; y++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for(uint x = 0; x < cols; x++)
		{
			glVertex3f(x - dx, height * heights[(y + 0) * cols + x], (y + 0) - dy);
			glVertex3f(x - dx, height * heights[(y + 1) * cols + x], (y + 1) - dy);
		}

		glEnd();
	}
}

void Terrain::Reset(void)
{
	for(uint i = 0; i < rows * cols; i++)
	{
		heights[i] = 0.0f;
	}
}

void Terrain::ApplyFilter(const Filter& filter)
{
	filter.ApplyToData(heights, rows, cols);
}

void Terrain::GenerateRandomHeights(void)
{
	for(uint i = 0; i < rows * cols; i++)
	{
		heights[i] = (rand() % 1000 - 500) * 0.001f;
	}
}

// setter
void Terrain::SetHeight(real height)
{
	this->height = inf(height, 0.0f);
}