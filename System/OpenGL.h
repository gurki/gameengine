#pragma once

#include "Types.h"

#define GLUT_BUILDING_LIB

#ifdef OS_WINDOWS
	#include <GL/GLEW.h>
	#include <GL/GLUT.h>
	#include <IL/ILUT.h>
#else
    // #include <OpenGL/GLEXT.h>
    #include <GLUT/GLUT.h>
	// #include <IL/ILUT.h>
#endif

#ifdef OS_WINDOWS
	#pragma comment(lib, "OpenGL32.lib")
	#pragma comment(lib, "GLU32.lib")
	#pragma comment(lib, "GLUT32.lib")

	#pragma comment(lib, "GLEW32.lib")

	#pragma comment(lib, "DevIL.lib")
	#pragma comment(lib, "ILU.lib")
	#pragma comment(lib, "ILUT.lib")
#endif