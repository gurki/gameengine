//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "GameEngine.h"

//***************************************************************************//
//                            The GameEngine Class                           //
//***************************************************************************//

// GAMEENGINE HANDLING

void CGameEngine::Initialize(int argc, char** argv, unsigned int mode, char* title, unsigned int width, unsigned int height)
{
	m_mode = mode;

	if(m_mode > GAME_MODE_3D)
	{
		m_mode = GAME_MODE_3D;
	}

	glutInit(&argc, argv);
	

	if(m_mode == GAME_MODE_2D)
	{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

		// glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	}

	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) >> 1, (glutGet(GLUT_SCREEN_HEIGHT) - height) >> 1);
	glutCreateWindow(title);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	if(m_mode == GAME_MODE_2D)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearDepth(1.0f);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);

		glShadeModel(GL_SMOOTH);
	}

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glutIdleFunc(IdleFunction);
	glutDisplayFunc(RenderFunction);
	glutReshapeFunc(ReshapeFunction);

	m_paused = false;
	m_running = false;
	m_initialized = true;

	Mouse.Initialize();
	Keyboard.Initialize();

	// TextureManager.Initialize();
}

void CGameEngine::Start(void)
{
	if(m_initialized == true && m_running == false)
	{
		m_running = true;

		glutMainLoop();
	}
}

void CGameEngine::End(void)
{
	// TextureManager.Deinitialize();

	exit(EXIT_SUCCESS);
}

void CGameEngine::Pause(void)
{
	m_paused = true;
}

void CGameEngine::Unpause(void)
{
	m_paused = false;
}

bool CGameEngine::IsPaused(void)
{
	return m_paused;
}

unsigned int CGameEngine::GetGameMode(void)
{
	return m_mode;
}

void CGameEngine::RegisterCallbacks(func render, func idle, func input)
{
	m_idle = idle;
	m_input = input;
	m_render = render;	
}

void CGameEngine::ClearInput(void)
{
	Mouse.ClearButtons();
	Keyboard.ClearKeys();
}

void CGameEngine::IdleFunction(void)
{
	InputFunction();

	if(GameEngine.IsPaused() == false)
	{
		if(GameEngine.GetIdlePointer() != NULL)
		{
			GameEngine.GetIdlePointer()();
		}
		
		RenderFunction();
	}

	GameEngine.ClearInput();
}

void CGameEngine::InputFunction(void)
{
	if(Keyboard.KeyWasPressed(27)) 
	{
		GameEngine.End();
	}

	// Camera.HandleInput();

	if(GameEngine.GetInputPointer() != NULL) 
	{
		GameEngine.GetInputPointer()();
	}
}

void CGameEngine::RenderFunction(void)
{
	if(GameEngine.IsPaused() == false)
	{
		if(GameEngine.GetRenderPointer() != NULL)
		{
			GameEngine.GetRenderPointer()();
		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();	

			glutSwapBuffers();
		}
	}
}

void CGameEngine::ReshapeFunction(int width, int height)
{
	if(height == 0) 
	{
		height = 1;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(GameEngine.GetGameMode() == GAME_MODE_2D) 
	{	
		gluOrtho2D(0, width, 0, height);
		glViewport(0, 0, width, height);
	} 
	else
	{
		float ratio = (float)width / (float)height;

		gluPerspective(75.0f, ratio, 1.0f, 1000.0f);
		glViewport(0, 0, width, height);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

func CGameEngine::GetIdlePointer(void)
{
	return m_idle;
}

func CGameEngine::GetInputPointer(void)
{
	return m_input;	
}

func CGameEngine::GetRenderPointer(void)
{
	return m_render;	
}

unsigned int GetWindowWidth(void)
{
	return glutGet(GLUT_WINDOW_WIDTH);
}

unsigned int GetWindowHeight(void)
{
	return glutGet(GLUT_WINDOW_HEIGHT);
}

unsigned int GetScreenWidth(void)
{
	return glutGet(GLUT_SCREEN_WIDTH);
}

unsigned int GetScreenHeight(void)
{
	return glutGet(GLUT_SCREEN_HEIGHT);
}

//***************************************************************************//
//                             The Keyboard Class                            //
//***************************************************************************//

// KEYBOARD HANDLING

void CKeyboard::Initialize(void) 
{
	glutIgnoreKeyRepeat(true);

	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecialFunc);
	glutSpecialUpFunc(SpecialUpFunc);
}

void CKeyboard::ClearKeys(void) {
	m_bKeyWasPressed[m_ucKeyBuffer] = false;
}

void CKeyboard::UpdateModifiers(void)
{
	int mod = glutGetModifiers();

	m_bShiftIsPressed = false;
	m_bCtrlIsPressed = false;
	m_bAltIsPressed = false;
	
	if(mod == GLUT_ACTIVE_SHIFT) m_bShiftIsPressed = true;
	if(mod == GLUT_ACTIVE_CTRL) m_bCtrlIsPressed = true;
	if(mod == GLUT_ACTIVE_ALT) m_bAltIsPressed = true;
}

void CKeyboard::NormalKeyPress(unsigned char key, int x, int y, int state) 
{
	m_bKeyIsPressed[key] = false;
	m_bKeyIsPressed[key - 32] = false;
	m_bKeyIsPressed[key - 96] = false;

	if(m_bShiftIsPressed) {
		m_bKeyIsPressed[key + 32] = false;
	} else if(m_bCtrlIsPressed) {
		m_bKeyIsPressed[key + 96] = false;
	}

	if(state == GLUT_DOWN) {
		m_ucKeyBuffer = key;

		if(m_bCtrlIsPressed) {
			m_bKeyWasPressed[key + 96] = true;
			m_bKeyIsPressed[key + 96] = true;
		} else {
			m_bKeyWasPressed[key] = true;
			m_bKeyIsPressed[key] = true;
		}
	}
}

void CKeyboard::SpecialKeyPress(int key, int x, int y, int state) 
{
	m_bKeyIsPressed[key] = false;

	if(state == GLUT_DOWN) {
		m_ucKeyBuffer = key;

		if(m_bCtrlIsPressed) {
			m_bKeyWasPressed[key + 96] = true;
			m_bKeyIsPressed[key + 96] = true;
		} else {
			m_bKeyWasPressed[key] = true;
			m_bKeyIsPressed[key] = true;
		}
	}
}

// KEYBOARD GETTERS

bool CKeyboard::ShiftIsPressed(void) {
	return m_bShiftIsPressed;
}

bool CKeyboard::CtrlIsPressed(void) {
	return m_bCtrlIsPressed;
}

bool CKeyboard::AltIsPressed(void) {
	return m_bAltIsPressed;
}

bool CKeyboard::KeyIsPressed(unsigned char ucKey) {
	return m_bKeyIsPressed[ucKey];
}

bool CKeyboard::KeyWasPressed(unsigned char ucKey) {
	return m_bKeyWasPressed[ucKey];
}

// KEYBOARD CALLBACKS

void CKeyboard::KeyboardFunc(unsigned char key, int x, int y) 
{
	CKeyboard::GetInstance().UpdateModifiers();
	CKeyboard::GetInstance().NormalKeyPress(key, x, y, GLUT_DOWN);
}

void CKeyboard::KeyboardUpFunc(unsigned char key, int x, int y) 
{
	CKeyboard::GetInstance().UpdateModifiers();
	CKeyboard::GetInstance().NormalKeyPress(key, x, y, GLUT_UP);
}

void CKeyboard::SpecialFunc(int key, int x, int y) 
{ 
	CKeyboard::GetInstance().UpdateModifiers();
	CKeyboard::GetInstance().SpecialKeyPress(key, x, y, GLUT_DOWN);
}

void CKeyboard::SpecialUpFunc(int key, int x, int y) 
{
	CKeyboard::GetInstance().UpdateModifiers();
	CKeyboard::GetInstance().SpecialKeyPress(key, x, y, GLUT_UP);
}

//***************************************************************************//
//                              The Mouse Class                              //
//***************************************************************************//

// MOUSE HANDLING

void CMouse::Initialize(void)
{
	glutMouseFunc(CMouse::MouseFunc);
	glutEntryFunc(CMouse::EntryFunc);
	glutMotionFunc(CMouse::MotionFunc);
	glutPassiveMotionFunc(CMouse::PassiveMotionFunc);

	Center();
	HideCursor();
}

void CMouse::ClearButtons(void) {
	m_bButtonWasPressed[m_uiButtonBuffer] = false;
}

void CMouse::Center(void)
{
	m_vPosition.x = glutGet(GLUT_WINDOW_WIDTH) / 2;
	m_vPosition.y = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	glutWarpPointer(m_vPosition.x, m_vPosition.y);
}

void CMouse::HideCursor(void)
{
	m_bCursorIsVisible = false;
	glutSetCursor(GLUT_CURSOR_NONE);
}


void CMouse::ShowCursor(void)
{
	m_bCursorIsVisible = true;
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

void CMouse::UpdatePosition(int x, int y) 
{
	m_vPositionDelta.x = m_vPosition.x - x;
	m_vPositionDelta.y = m_vPosition.y - y;

	if(m_vPositionDelta.x == 0 && m_vPositionDelta.y == 0) {
		m_bHasMoved = false;
	} else {
		m_vPosition.x = x;
		m_vPosition.y = y;

		m_bHasMoved = true;
	}
}

void CMouse::Click(int button, int state, int x, int y)
{
	if(m_bButtonWasPressed[m_uiButtonBuffer]) {
		m_bButtonWasPressed[m_uiButtonBuffer] = false;
	}

	m_uiButtonBuffer = button;

	if(state == GLUT_DOWN)
	{
		m_bButtonIsPressed[button] = true;
		m_bButtonWasPressed[button] = true;
		m_vClickEventPosition.x = x;
		m_vClickEventPosition.y = y;
	} 	
	else if(state == GLUT_UP) {
		m_bButtonIsPressed[button] = false;
	}

	UpdatePosition(x, y);
}

// MOUSE SETTERS

void CMouse::SetPosition(int iPositionX, int iPositionY)
{
	m_vPosition.x = iPositionX;
	m_vPosition.y = iPositionY;

	m_vPositionDelta.x = m_vPosition.x - iPositionX;
	m_vPositionDelta.y = m_vPosition.y - iPositionY;

	glutWarpPointer(m_vPosition.x, m_vPosition.y);
}

// MOUSE GETTERS

vec2i CMouse::Position(void){
	return m_vPosition;
}

vec2i CMouse::PositionDelta(void) {
	return m_vPositionDelta;
}

vec2i CMouse::ClickEventPosition(void) {
	return m_vClickEventPosition;
}

bool CMouse::HasMoved(void) {
	return m_bHasMoved;
}

bool CMouse::CursorIsVisible(void) {
	return m_bCursorIsVisible;
}

bool CMouse::ButtonIsPressed(int iButton) {
	return m_bButtonIsPressed[iButton];
}

bool CMouse::ButtonWasPressed(int iButton) {
	return m_bButtonWasPressed[iButton];
}

// MOUSE CALLBACKS

void CMouse::EntryFunc(int state) {
	if(state == GLUT_LEFT) {} else {}
}

void CMouse::MotionFunc(int x, int y) {
	CMouse::GetInstance().UpdatePosition(x, y);
}

void CMouse::PassiveMotionFunc(int x, int y) {
	CMouse::GetInstance().UpdatePosition(x, y);
}

void CMouse::MouseFunc(int button, int state, int  x, int y) 
{
	CMouse::GetInstance().Click(button, state, x, y);
	CMouse::GetInstance().UpdatePosition(x, y);
}