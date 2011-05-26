//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Screen.h"

CScreen::CScreen(void) : Rectangle()
{
	dim.x = glutGet(GLUT_SCREEN_WIDTH);
	dim.y = glutGet(GLUT_SCREEN_HEIGHT);
}