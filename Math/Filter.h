//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _FILTER_H
#define _FILTER_H

#include "Types.h"
#include "MathLib.h"

#include <iostream>
#include <iomanip>

using namespace std;

class Filter
{
	public:

		// constructor
		Filter(void);
		Filter(uint rows, uint cols);
		Filter(real* matrix, uint rows, uint cols);
		~Filter(void);

		// methods
		Filter& Normalize(void);
		virtual void ApplyToData(real* data, uint dataRows, uint dataCols, uint offset = 0, uint stride = 1) const;
		
		// setter
		void SetGaussian(uint neighbours);

		// getter

		// class getter
		static Filter& Sobel(void);

		static Filter& Lowpass(void);
		static Filter& Gaussian1(void);
		static Filter& Gaussian2(void);
		static Filter& Gaussian3(void);
		static Filter& Gaussian4(void);

		static Filter& Sharpening(void);
		static Filter& VerticalSharpening(void);
		static Filter& HorizontalSharpening(void);

		static Filter& EdgeDetectionUpperLeft(void);
		static Filter& EdgeDetectionLowerRight(void);

		// streams
		friend ostream& operator << (ostream& out, const Filter& filter);
		friend istream& operator >> (istream& in, Filter& filter);

		// public variables
		real* matrix;

	protected:

		// variables
		uint verticalNeighbours;
		uint horizontalNeighbours;

		uint rows;
		uint cols;
};

#endif