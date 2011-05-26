//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Shader.h"

Shader::Shader(void)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	

	File vs, fs;

	const char * vv = vs.GetData();
	const char * ff = fs.GetData();

	glShaderSource(vertexShader, 1, &vv,NULL);
	glShaderSource(fragmentShader, 1, &ff,NULL);

	vs.~File();
	fs.~File();

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glUseProgram(program);
}

Shader::~Shader(void)
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(program);
}