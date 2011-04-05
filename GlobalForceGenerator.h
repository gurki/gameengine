//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _GLOBALFORCEGENERATOR_H
#define _GLOBALFORCEGENERATOR_H

#include "Types.h"
#include "Vector3.h"
#include "RigidBody3.h"

class GlobalForceGenerator
{
	public:	

		// methods
		virtual void ApplyForce(RigidBody3* rigidBody) {};
};

#endif