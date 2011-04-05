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

class Filter
{
	public:

		// constructor
		Filter(real* matrix, uint rows, uint cols);
		~Filter(void);

		// methods
		void Normalize(void);
		virtual void ApplyToData(real* data, uint rows, uint cols) const;
		
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

	protected:

		// variables
		uint horn;
		uint vern;

		uint rows;
		uint cols;

		real* matrix;
};

#endif