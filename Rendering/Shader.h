//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _SHADER_H
#define _SHADER_H

#include "OpenGL.h"
#include "Types.h"
#include "File.h"

class Shader
{
	public:

		Shader(void);
		~Shader(void);

	protected:

		uint program;
		uint vertexShader;
		uint fragmentShader;
};

#endif