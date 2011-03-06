//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Object.h"

Object::Object(void)
{
	pos = vec3::Zero();
	vel = vec3::Zero();

	f = vec3::Zero();
	invm = 1.0;
	
	rot = quat::Identity();
	ang = quat::Zero();

	t = vec3::Zero();
	invi = 1.0;
}