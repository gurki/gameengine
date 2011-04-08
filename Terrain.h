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
#include "Vector2.h"
#include "Vector3.h"
#include "Filter.h"

class Terrain : public Object3
{
	public:
		
		// constructors
		Terrain(real width, real height, real depth);
		~Terrain(void);

		// methods
		void Render(void) const;
		void RenderBoundingBox(void) const;

		void Balance(void);
		void Normalize(void);

		void Erode(uint strength = 1);
		void Smooth(uint strength = 1);

		void GenerateRandomTerrain(void);

		// setter
		void SetPlane(void);
		void SetHeight(real height);
		void SetTileSize(real width, real depth);

		// getter
		vec3 GetClosestGridPoint(const vec3& point);

	protected:

		void UpdateNormals(void);
		void UpdateExtents(void);

		// variables
		uint rows;
		uint cols;

		real maxHeight;
		real minHeight;
		real midHeight;

		vec2 tileSize;
		vec3 dimensions;

		vec3* vertices; 
		vec3* normals;
};

#endif