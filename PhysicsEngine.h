//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include <vector>
#include "Types.h"
#include "Timer.h"

#include "RigidBody3.h"
#include "RigidBox.h"
#include "RigidSphere.h"
#include "RigidCylinder.h"

#include "ForceGenerator.h"
#include "ParticleSpring.h"

#include "GlobalForceGenerator.h"
#include "Gravity.h"

using namespace std;

#define PhysicsEngine CPhysicsEngine::GetInstance()

class CPhysicsEngine
{
	public:

		// methods
		void TogglePause(void);

		void Update(void);
		void RenderRigidBodies(void);

		// setter
		void AddRigidBody(RigidBody3* body);
		void AddForceGenerator(ForceGenerator* generator);
		void AddGlobalForceGenerator(GlobalForceGenerator* generator);

		// getter
		RigidBody3* GetRigidBody(uint n) const;
		uint GetNumberOfRigidBodies(void) const;

	private:

		// variables
		vector<RigidBody3*> rigidBodies;
		vector<ForceGenerator*> forceGenerators;
		vector<GlobalForceGenerator*> globalForceGenerators;

		real timestep;
		real dt;

		bool paused;

	public:

 		// singleton
		static CPhysicsEngine& GetInstance(void)
		{
			static CPhysicsEngine Singleton;
			return Singleton;
		};

	private:

		CPhysicsEngine(void);
		CPhysicsEngine(CPhysicsEngine const&) {};
		CPhysicsEngine& operator = (CPhysicsEngine const&) { return *this; };
		~CPhysicsEngine(void) {};
};

#endif