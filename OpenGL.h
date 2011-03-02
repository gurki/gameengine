#ifndef _OPENGL_H
#define _OPENGL_H

#include "Types.h"

#define GLUT_BUILDING_LIB

#ifdef OS_WINDOWS
	#include <GL/GLUT.h>
#else
	#include <GLUT/GLUT.h>
#endif

#ifdef OS_WINDOWS
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLUT32.lib")
#pragma comment(lib, "GLU32.lib")
#endif

#endif