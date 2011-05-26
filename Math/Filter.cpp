//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Filter.h"

// constructor
Filter::Filter(void)
{
	this->rows = 0;
	this->cols = 0;

	this->matrix = 0;

	this->verticalNeighbours = 0;
	this->horizontalNeighbours = 0;
}

Filter::Filter(uint rows, uint cols)
{
	this->rows = 0;
	this->cols = 0;

	this->matrix = 0;

	this->verticalNeighbours = 0;
	this->horizontalNeighbours = 0;

	if(rows % 2 != 0 && cols % 2 != 0)
	{
		this->verticalNeighbours = (cols - 1) / 2;
		this->horizontalNeighbours = (rows - 1) / 2;
	
		this->rows =  rows;
		this->cols =  cols;

		this->matrix = new real[rows * cols];
	}
}

Filter::Filter(real* matrix, uint rows, uint cols)
{
	this->rows = 0;
	this->cols = 0;

	this->matrix = 0;

	this->verticalNeighbours = 0;
	this->horizontalNeighbours = 0;

	if(rows % 2 != 0 && cols % 2 != 0)
	{
		this->verticalNeighbours = (cols - 1) / 2;
		this->horizontalNeighbours = (rows - 1) / 2;
	
		this->rows =  rows;
		this->cols =  cols;

		this->matrix = new real[rows * cols];

		for(uint i = 0; i < rows * cols; i++)
		{
			this->matrix[i] = matrix[i];
		}
	}
}

Filter::~Filter(void)
{
	if(matrix != 0)
	{
		delete[] matrix;

		matrix = 0;
	}
}

// methods
Filter& Filter::Normalize(void)
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

	return *this;
}

void Filter::ApplyToData(real* data, uint dataRows, uint dataCols, uint offset, uint stride) const
{
	// allocate memory for temporary data copy
	real* temp = new real[dataRows * dataCols / stride];
	real norm = 0.0f;
	uint index = 0;

	// loop through every point in data
	for(int dataRow = 0; dataRow < dataRows; dataRow++)
	{
		for(int dataCol = offset; dataCol < dataCols; dataCol += stride)
		{
			// zero current temp entry
			index = (dataRow * dataCols + dataCol) / stride; 
			temp[index] = 0.0f;
			norm = 0.0f;

			// loop through every filter entry
			for(uint filterRow = 0; filterRow < this->rows; filterRow++)
			{
				for(uint filterCol = 0; filterCol < this->cols; filterCol++)
				{
					// calculate datagridpoint of filtermatrix overlap
					int tempRow = dataRow + filterRow - verticalNeighbours;
					int tempCol = dataCol + (filterCol - horizontalNeighbours) * stride;

					// check for out of bounds dataaccess
					if(tempRow >= 0 && tempRow < dataRows && tempCol >= 0 && tempCol < dataCols)
					{
						// add filtered datavalue to temp
						temp[index] += data[tempRow * dataCols + tempCol] * matrix[filterRow * cols + filterCol]; 

						norm += matrix[filterRow * cols + filterCol];
					} // end bounds check
				} 
			} // end filter loop 

			if(norm != 0)
			{
				temp[index] /= norm;
			}
		}	
	} // end data loop

	// copy temp to original data
	for(uint i = 0; i < dataRows * dataCols / stride; i++)
	{
		data[offset + i * stride] = temp[i];
	}

	// clean up
	delete[] temp;
}

// class getter
Filter& Filter::Sobel(void)
{
	static real matrix[9] = {-1,-2,-1,
							  0, 1, 0,
							  1, 2, 1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::Lowpass(void)
{
	static real matrix[9] = {1, 1, 1, 
							 1, 1, 1, 
							 1, 1, 1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::Gaussian1(void)
{
	static real matrix[9] = {1, 2, 1,
							 2, 4, 2, 
							 1, 2, 1};
	static Filter filter(matrix, 3, 3);

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

	return filter;
}

Filter& Filter::Gaussian4(void)
{
	static real matrix[81] = {1,  2,  4,  8,   16,  8,   4,  2,  1,
							  2,  4,  8,  16,  32,  16,  8,  4,  2,
							  4,  8,  16, 32,  64,  32,  16, 8,  4, 
							  8,  16, 32, 64,  128, 64,  32, 16, 8,
							  16, 32, 64, 128, 256, 128, 64, 32, 16,
							  8,  16, 32, 64,  128, 64,  32, 16, 8,
							  4,  8,  16, 32,  64,  32,  16, 8,  4, 
							  2,  4,  8,  16,  32,  16,  8,  4,  2,
						      1,  2,  4,  8,   16,  8,   4,  2,  1};
	static Filter filter(matrix, 9, 9);

	return filter;
}

void Filter::SetGaussian(uint neighbours)
{
	this->~Filter();

	verticalNeighbours = neighbours;
	horizontalNeighbours = neighbours;

	rows = neighbours * 2 + 1;
	cols = neighbours * 2 + 1;
	
	matrix = new real[rows * cols];
	
	real m = 1.0f;
	
	for(uint row = 0; row <= neighbours; row++)
	{
		for(uint col = 0; col < neighbours; col++)
		{
			if(col != 0) 
			{
				m = matrix[row * cols + col - 1] * 2.0f;
			}
			else
			{
				if(row != 0) 
				{
					m = matrix[(row - 1) * cols] * 2.0f;
				}
				else 
				{
					m = 1.0f;
				}
			}

			matrix[row * cols + col] = m;
			matrix[row * cols + (cols - 1) - col] = m;

			if(row != neighbours)
			{
				matrix[cols * (cols - 1) - row * cols + col] = m;
				matrix[cols * (cols - 1) - row * cols + (cols - 1) - col] = m;
			}
		}
		
		matrix[row * cols + neighbours] = m * 2.0f;

		if(row != neighbours)
		{
			matrix[cols * (cols - 1) - row * cols + neighbours] = m * 2.0f;
		}
	}
}

Filter& Filter::Sharpening(void)
{
	static real matrix[9] = { 0,-1, 0,
							 -1, 5,-1,
							  0,-1, 0};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::VerticalSharpening(void)
{
	static real matrix[9] = {-1, 2,-1,
							 -1, 3,-1,
							 -1, 2,-1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::HorizontalSharpening(void)
{

	static real matrix[9] = {-1,-1,-1,
							  2, 3, 2,
							 -1,-1,-1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::EdgeDetectionUpperLeft(void)
{
	static real matrix[9] = { 1, 0, 0,
							  0, 0, 0,
							  0, 0,-1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

Filter& Filter::EdgeDetectionLowerRight(void)
{
	static real matrix[9] = {-1, 0, 0,
							  0, 0, 0,
							  0, 0, 1};
	static Filter filter(matrix, 3, 3);

	return filter;
}

// streams
ostream& operator << (ostream& out, const Filter& filter)
{
	for(uint row = 0; row < filter.rows; row++)
	{
		cout << "{";

		for(uint col = 0; col < filter.cols; col++)
		{
			out << filter.matrix[row * filter.cols + col];

			if(col != filter.cols - 1)
			{
				cout << ", ";
			}
		}

		cout << "}" << endl;
	}

	return out;
}

istream& operator >> (istream& in, Filter& filter)
{
	uint rows;
	uint cols;

	cout << "Filter Rows: ";
	in >> rows;
	cout << "Filter Columns: ";
	in >> cols;

	real* matrix = new real[rows * cols];

	for(uint i = 0; i < rows * cols; i++)
	{
		cin >> matrix[i];
	}

	filter.~Filter();
	filter = Filter(matrix, rows, cols);

	delete[] matrix;

	return in;
}