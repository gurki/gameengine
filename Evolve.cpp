//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

#include "Grid3.h"
#include "OrbitingCamera.h"

#include "Terrain.h"
#include "OpenGL.h"
#include "File.h"

OrbitingCamera cam;
Grid3 grid;
Terrain terrain(10, 10, 10);

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
	printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
	printf("%s\n",infoLog);
        free(infoLog);
    }
}

int main(int argc, char* argv[])
{
	// initialize gameengine
	GameEngine.Initialize(argc, argv);

	// initialize objects
	cam.SetViewport(0, 0, Window.GetDimensions().x, Window.GetDimensions().y);
	grid.SetDimensions(10, 10);
	terrain.GenerateRandomTerrain();
	
	// initialize glew
	glewInit();
	
	if(glewIsSupported("GL_VERSION_2_0")) 
	{
		cout << "GLEW initialized" << endl;
	}

	uint v = glCreateShader(GL_VERTEX_SHADER);
	uint f = glCreateShader(GL_FRAGMENT_SHADER);
	
	File vert;
	File frag;

	vert.LoadFromFile("C:/Users/Gurki/Documents/My Dropbox/Programming/DirectionalPerPixelLighting.vert");
	frag.LoadFromFile("C:/Users/Gurki/Documents/My Dropbox/Programming/DirectionalPerPixelLighting.frag");
	
	const char* vc = vert.GetData();
	const char* fc = frag.data;
		
	glShaderSource(v, 1, &vc, 0);
	glShaderSource(f, 1, &fc, 0);
	
	vert.~File();
	frag.~File();
	
	glCompileShader(v);
	glCompileShader(f);
	
	uint p = glCreateProgram();

	glAttachShader(p, v);
	glAttachShader(p, f);

	glLinkProgram(p);
	glUseProgram(p);

	printShaderInfoLog(v);
	printShaderInfoLog(f);
	printProgramInfoLog(p);
	
	// start game
	GameEngine.Start();

	// clean up
	glDetachShader(p, v);
	glDetachShader(p, f);

	glDeleteShader(v);
	glDeleteShader(f);

	system("PAUSE");
	return 0;
}

void CGameEngine::Render(void) const
{
	cam.Enable();

	// initialize lights
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
	GLfloat light_direction[] = {-1.0, -1.0, -1.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	terrain.Render();
	//grid.Render();
}

void CGameEngine::Idle(void) const
{

}

void CGameEngine::Input(void) const
{
	static real last = Time.GetRunTime();

	if(Time.GetRunTime() - last > 0.1f)
	{
		if(Keyboard.KeyIsPressed('e')) terrain.Erode(1);
		if(Keyboard.KeyIsPressed('s')) terrain.Smooth(1);

		last = Time.GetRunTime();
	}

	if(Keyboard.KeyWasPressed('r')) terrain.GenerateRandomTerrain();

	// game
	if(Keyboard.KeyWasPressed('p')) GameEngine.TogglePause();
	if(Keyboard.KeyWasPressed('f')) Window.ToggleFullScreen();
	
	static bool wireframe = false;

	if(Keyboard.KeyWasPressed('w'))
	{
		if(wireframe == false)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireframe = true;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireframe = false;
		}
	}

	if(Mouse.ButtonIsPressed(BUTTON_LEFT))
	{
		cam.Orbit(Mouse.PositionDelta().x * Time.GetTimeDelta(), 0);
	}
}