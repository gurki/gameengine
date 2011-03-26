//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Screen.h"

CScreen::CScreen(void)
{
	pos = vec2(0, 0);

	dim.x = glutGet(GLUT_SCREEN_WIDTH);
	dim.y = glutGet(GLUT_SCREEN_HEIGHT);
}