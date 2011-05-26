//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _COLLISIONRESOLVER_H
#define _COLLISIONRESOLVER_H

#include "Types.h"
#include "Vector3.h"
#include "RigidBody3.h"

#include <vector>

using namespace std;

class Contact
{
	public:

		RigidBody3* b1;
		RigidBody3* b2;

		real s;
		vec3 v;
		vec3 n;
};

class CollisionResolver
{
	public:

		static void HandleCollisions(vector<RigidBody3*>* rigidBodies);

	protected:

		static void CourseDetection(void);
		static void FineDetection(void);
		static void Resolving(void);

		static vector<RigidBody3*>* bodies;
		static vector<Contact> contacts;
};

#endif