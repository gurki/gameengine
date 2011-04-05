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

void CGameEngine::Initialize(int argc, char** argv)
{
	Time.Initialize();

	glutInit(&argc, argv);

	Window.Initialize();

	m_paused = false;
	m_running = false;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glPointSize(5.0f);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void CGameEngine::Start(void)
{
	if(m_running == false)
	{
		m_running = true;
		
		glutIdleFunc(IdleFunction);
		glutDisplayFunc(RenderFunction);

		glutMainLoop();
	}
}

void CGameEngine::End(void)
{
	exit(EXIT_SUCCESS);
}

void CGameEngine::TogglePause(void)
{
	if(m_paused == true)
	{
		m_paused = false;
	}
	else
	{
		m_paused = true;
	}
}

bool CGameEngine::IsPaused(void)
{
	return m_paused;
}

void CGameEngine::ClearInput(void)
{
	Mouse.ClearButtons();
	Keyboard.ClearKeys();
}

void CGameEngine::IdleFunction(void)
{
	Time.Update();

	InputFunction();

	if(GameEngine.IsPaused() == false)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		PhysicsEngine.Update();
		GameEngine.Idle();
		GameEngine.Render();

		glutSwapBuffers();
	}

	GameEngine.ClearInput();
}

void CGameEngine::InputFunction(void)
{
	if(Keyboard.KeyWasPressed(27)) 
	{
		GameEngine.End();
	}

	GameEngine.Input();
}

void CGameEngine::RenderFunction(void)
{
	if(GameEngine.IsPaused() == false)
	{
		GameEngine.Render();
	}
}

//***************************************************************************//
//                             The Keyboard Class                            //
//***************************************************************************//

// KEYBOARD HANDLING

CKeyboard::CKeyboard(void) 
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

CMouse::CMouse(void)
{
	glutMouseFunc(CMouse::MouseFunc);
	glutEntryFunc(CMouse::EntryFunc);
	glutMotionFunc(CMouse::MotionFunc);
	glutPassiveMotionFunc(CMouse::PassiveMotionFunc);

	Center();
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

vec2 CMouse::Position(void){
	return m_vPosition;
}

vec2 CMouse::PositionDelta(void) {
	return m_vPositionDelta;
}

vec2 CMouse::ClickEventPosition(void) {
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