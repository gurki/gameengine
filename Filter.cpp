//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Filter.h"

// constructor
Filter::Filter(real* matrix, uint rows, uint cols)
{
	this->matrix = 0;

	if(rows % 2 != 0 && cols % 2 != 0)
	{
		this->vern = (cols - 1) / 2;
		this->horn = (rows - 1) / 2;
	
		this->rows =  rows;
		this->cols =  cols;

		this->matrix = new real[rows * cols];

		for(uint i = 0; i < rows * cols; i++)
		{
			this->matrix[i] = matrix[i];
		}

		Normalize();
	}
}

Filter::~Filter(void)
{
	if(matrix != 0)
	{
		delete[] matrix;
	}
}

// methods
void Filter::Normalize(void)
{
	real k = 0.0f;

	for(uint i = 0; i < rows * cols; i++)
	{
		k += absr(matrix[i]);	
	}

	if(k != 0 && k != 1)
	{
		k = 1.0f / k;

		for(uint i = 0; i < rows * cols; i++)
		{
			matrix[i] *= k;
		}
	}
}

void Filter::ApplyToData(real* data, uint dataRows, uint dataCols) const
{
	// allocate memory for temporary data copy
	real* temp = new real[dataRows * dataCols];

	// loop through every point in data
	for(uint dataRow = 0; dataRow < dataRows; dataRow++)
	{
		for(uint dataCol = 0; dataCol < dataCols; dataCol++)
		{
			// zero current temp entry
			temp[dataRow * dataCols + dataCol] = 0.0f;
			
			// loop through every filter entry
			for(uint filterRow = 0; filterRow < this->rows; filterRow++)
			{
				for(uint filterCol = 0; filterCol < this->cols; filterCol++)
				{
					// calculate datagridpoint of filtermatrix overlap
					uint tempRow = dataRow + filterRow - vern;
					uint tempCol = dataCol + filterCol - horn;

					// check for out of bounds dataaccess
					if(tempRow >= 0 && tempRow < dataRows && tempCol >= 0 && tempCol < dataCols)
					{
						// add filtered datavalue to temp
						temp[dataRow * dataCols + dataCol] += data[tempRow * dataCols + tempCol] * matrix[filterRow * cols + filterCol]; 
					} // end bounds check
				} 
			} // end filter loop
		}	
	} // end data loop

	// copy temp to original data
	for(uint i = 0; i < dataRows * dataCols; i++)
	{
		data[i] = temp[i];
	}

	// clean up
	delete[] temp;
}

// class getter
Filter& Filter::Sobel(void)
{
	static real matrix[9] = {-1.0f,-2.0f,-1.0f,
							  0.0f, 1.0f, 0.0f,
							  1.0f, 2.0f, 1.0f};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::Lowpass(void)
{
	static real matrix[9] = {1, 1, 1, 
							 1, 1, 1, 
							 1, 1, 1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::Gaussian1(void)
{
	static real matrix[9] = {1, 2, 1,
							 2, 4, 2, 
							 1, 2, 1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::Gaussian2(void)
{
	static real matrix[25] = {1, 2, 4,  2, 1,
							  2, 4, 8,  4, 2,
							  4, 8, 16, 8, 4,
							  2, 4, 8,  4, 2,
							  1, 2, 4,  2, 1};
	static Filter filter(matrix, 5, 5);
	filter.Normalize();

	return filter;
}

Filter& Filter::Gaussian3(void)
{
	static real matrix[49] = {1, 2,  4,  8,  4,  2,  1,
		                      2, 4,  8,  16, 8,  4,  2,
							  4, 8,  16, 32, 16, 8,  4,
							  8, 16, 32, 64, 32, 16, 8,
							  4, 8,  16, 32, 16, 8,  4,
							  2, 4,  8,  16, 8,  4,  2,
							  1, 2,  4,  8,  4,  2,  1};
	static Filter filter(matrix, 7, 7);
	filter.Normalize();

	return filter;
}

Filter& Filter::Gaussian4(void)
{
	static real matrix[81] = {1,  2,  4,  8,   16,  8,   4,  2,  1,
							  2,  4,  8,  16,  32,  26,  8,  5,  2,
							  4,  8,  16, 32,  64,  32,  16, 8,  4, 
							  8,  16, 32, 64,  128, 64,  32, 16, 8,
							  16, 32, 64, 128, 256, 128, 64, 32, 16,
							  8,  16, 32, 64,  128, 64,  32, 16, 8,
							  4,  8,  16, 32,  64,  32,  16, 8,  4, 
							  2,  4,  8,  16,  32,  26,  8,  5,  2,
						      1,  2,  4,  8,   16,  8,   2,  4,  1};
	static Filter filter(matrix, 9, 9);
	filter.Normalize();

	return filter;
}

Filter& Filter::Sharpening(void)
{
	static real matrix[9] = { 0,-1, 0,
							 -1, 5,-1,
							  0,-1, 0};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::VerticalSharpening(void)
{
	static real matrix[9] = {-1, 2,-1,
							 -1, 3,-1,
							 -1, 2,-1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::HorizontalSharpening(void)
{

	static real matrix[9] = {-1,-1,-1,
							  2, 3, 2,
							 -1,-1,-1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::EdgeDetectionUpperLeft(void)
{
	static real matrix[9] = { 1, 0, 0,
							  0, 0, 0,
							  0, 0,-1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}

Filter& Filter::EdgeDetectionLowerRight(void)
{
	static real matrix[9] = {-1, 0, 0,
							  0, 0, 0,
							  0, 0, 1};
	static Filter filter(matrix, 3, 3);
	filter.Normalize();

	return filter;
}