//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Types.h"
#include "OpenGL.h"
#include "Object3.h"
#include "Vector3.h"
#include "Filter.h"

class Terrain : public Object3
{
	public:
		
		// constructors
		Terrain(uint rows, uint cols);
		~Terrain(void);

		// methods
		void Render(void) const;
		void Reset(void);
		void ApplyFilter(const Filter& filter);
		void GenerateRandomHeights(void);

		// setter
		void SetHeight(real height);

	protected:

		// variables
		uint rows;
		uint cols;

		real height;
		real* heights; 
};

#endif