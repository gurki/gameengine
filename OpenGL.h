#pragma once

#include "Types.h"

#define GLUT_BUILDING_LIB

#ifdef OS_WINDOWS
	#include <GL/GLEW.h>
	#include <GL/GLUT.h>
#else
	#include <GL/GLEW.h>
	#include <GLUT/GLUT.h>
#endif

#ifdef OS_WINDOWS
	#pragma comment(lib, "OpenGL32.lib")
	#pragma comment(lib, "GLEW32.lib")
	#pragma comment(lib, "GLUT32.lib")
	#pragma comment(lib, "GLU32.lib")
#endif