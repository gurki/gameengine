//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifdef TEXTURES

#pragma once

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "OpenGL.h"
#include "Log.h"
#include "MathLib.h"

class Texture
{
	public:	
		
		// constructor
		Texture(void);
		~Texture(void);

		// methods
		void Save(const char* filename);
		bool Load(const char* filename);

		void GenerateTexture(uint width, uint height, uint channels);

		// getter
		uint GetWidth(void) const;
		uint GetHeight(void) const;
		uint GetSize(void) const;

		float* GetData(void) const;

	protected:

		// variables
		uint width;
		uint height;
		uint size;

		uint channels;
		uint format;

		float* data;
		uint dataSize;
};


#endif
#endif