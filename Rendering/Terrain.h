//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifdef TEXTURES

#pragma once

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Types.h"
#include "OpenGL.h"
#include "Object3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Filter.h"
#include "Texture.h"
#include "MathLib.h"

class Terrain : public Object3
{
	public:
		
		// constructors
		Terrain(real width, real height, real depth);
		~Terrain(void);

		// methods
		void Render(void) const;
		void RenderIndexed(void) const;
		void RenderVBO(void) const;
		void RenderNormals(void) const;

		void UpdateMaps(void);

		void Flatten(void);
		void Normalize(void);

		void SaveHeightmap(const char* filename);
		void LoadHeightmap(const char* filename);

		// terrain generation
		void GenerateRandom(uint steps);
		void GenerateParticleDeposition(uint series, uint iterations);
		void GenerateFaultLine(uint iterations);
		void GenerateFaultLinePlateau(real size, uint iterations);
		void GenerateFaultLineSine(real size, uint iterations);
		void GenerateFaultLineCosine(real size, uint iterations);
		void GenerateFaultLineWithFunction(real (*function)(real distance, real size), real size, uint iterations);

		// filtering
		void Smooth(uint iterations = 1);
		void ApplyFilter(const Filter& filter);

		// getter
		real GetHeightAtPoint(const vec3& point) const;
		
	protected:

		// methods
		void FreeMemory(void);
		void AllocateMemory(void);

		void CalculateNormals(void);
		
		vec3 dimensions;

		Texture normalmap;
		Texture heightmap;

		uint* indices; 
		vec3* vertices;
		vec3* normals;
		vec2* texcoords;
};

#endif
#endif