#ifndef _OPENGL_H
#define _OPENGL_H

#define GLUT_BUILDING_LIB

#ifdef _WIN32
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLUT32.lib")
#pragma comment(lib, "GLU32.lib")
#endif

#ifdef _WIN32
	#include <GL/GLUT.h>
#else
	#include <GLUT/GLUT.h>
#endif

#endif