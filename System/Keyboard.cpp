//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Keyboard.h"

bool CKeyboard::keyUp[288];
bool CKeyboard::keyHold[288];
bool CKeyboard::keyDown[288];

CKeyboard::CKeyboard(void) 
{
	glutIgnoreKeyRepeat(true);

	glutKeyboardFunc(KeyboardFunction);
	glutKeyboardUpFunc(KeyboardUpFunction);
	glutSpecialFunc(SpecialFunction);
	glutSpecialUpFunc(SpecialUpFunction);
}

CKeyboard::~CKeyboard(void) {};

void CKeyboard::Update(void)
{
	memset(keyUp, 0, sizeof(keyUp));
	memset(keyDown, 0, sizeof(keyDown));
}

void CKeyboard::UpdateModifiers(void)
{
	int modifier = glutGetModifiers();
	
	// shift
	if((modifier & 1) == GLUT_ACTIVE_SHIFT)
	{	
		if(keyHold[Keys.Shift] == false)
		{
			keyDown[Keys.Shift] = true;
			keyHold[Keys.Shift] = true;
		}
	}
	else
	{
		keyHold[Keys.Shift] = false;
	}

	// control
	if((modifier & (1 << 1)) == GLUT_ACTIVE_CTRL)
	{
		if(keyHold[Keys.Control] == false)
		{
			keyDown[Keys.Control] = true;
			keyHold[Keys.Control] = true;
		}
	}
	else
	{
		keyHold[Keys.Control] = false;
	}

	// alt
	if((modifier & (1 << 2)) == GLUT_ACTIVE_ALT)
	{
		if(keyHold[Keys.Alt] == false)
		{
			keyDown[Keys.Alt] = true;
			keyHold[Keys.Alt] = true;
		}
	}
	else
	{
		keyHold[Keys.Alt] = false;
	}

}

// getter
bool CKeyboard::KeyDown(uchar key)
{
	return keyDown[key];
}

bool CKeyboard::KeyHold(uchar key)
{
	return keyHold[key];
}

bool CKeyboard::KeyUp(uchar key)
{
	return keyUp[key];
}

int CKeyboard::KeyFromSpecial(int key)
{
	switch(key)
	{
		case 1:   return 257;
		case 2:   return 258;
		case 3:   return 259;
		case 4:   return 260;
		case 5:   return 261;
		case 6:   return 262;
		case 7:   return 263;
		case 8:   return 264;
		case 9:   return 265;
		case 10:  return 266;
		case 11:  return 267;
		case 12:  return 268;
		case 100: return 269;
		case 101: return 270;
		case 102: return 271;
		case 103: return 272;
		case 104: return 273;
		case 105: return 274;
		case 106: return 275;
		case 107: return 276;
		case 108: return 277;

		default:  return 0;
	}
}

// callbacks
void CKeyboard::KeyboardFunction(unsigned char key, int x, int y) 
{
	UpdateModifiers();
	
	keyDown[key] = true;
	keyHold[key] = true;
}

void CKeyboard::KeyboardUpFunction(unsigned char key, int x, int y) 
{
	UpdateModifiers();
	
	keyUp[key] = true;
	keyHold[key] = false;
}

void CKeyboard::SpecialFunction(int key, int x, int y) 
{ 
	UpdateModifiers();

	key = KeyFromSpecial(key);

	keyDown[key] = true;
	keyHold[key] = true;
}

void CKeyboard::SpecialUpFunction(int key, int x, int y) 
{
	UpdateModifiers();

	key = KeyFromSpecial(key);

	keyUp[key] = true;
	keyHold[key] = false;	
}