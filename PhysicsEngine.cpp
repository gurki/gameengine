//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "PhysicsEngine.h"
#include "CollisionResolver.h"

// constructors
CPhysicsEngine::CPhysicsEngine(void)
{
	timestep = 0.01f;
	dt = 0.0f;
}

// methods
void CPhysicsEngine::TogglePause(void)
{
	if(paused == true)
	{
		paused = false;		
	}
	else
	{
		paused = true;
	}
}

void CPhysicsEngine::Update(void)
{
	if(paused == false)
	{
		dt += Time.GetTimeDelta();

		while(dt > 0)
		{
			// local forces
			for(uint i = 0; i < forceGenerators.size(); i++)
			{
				forceGenerators[i]->ApplyForce();
			}
			
			// global forces
			for(uint i = 0; i < globalForceGenerators.size(); i++)
			{
				for(uint j = 0; j < rigidBodies.size(); j++)
				{
					globalForceGenerators[i]->ApplyForce(rigidBodies.at(j));
				}
			}

			// proceed
			for(uint i = 0; i < rigidBodies.size(); i++)
			{
				rigidBodies[i]->Update(timestep);
			}

			// clear forces
			for(uint i = 0; i < rigidBodies.size(); i++)
			{
				rigidBodies[i]->ClearAccumulators();
			}

			// solve collisions
			CollisionResolver::HandleCollisions(&rigidBodies);

			dt -= timestep;
		}
	}
}

void CPhysicsEngine::RenderRigidBodies(void)
{
	for(uint i = 0; i < rigidBodies.size(); i++)
	{
		rigidBodies[i]->Render();
	}
}

// setter
void CPhysicsEngine::AddRigidBody(RigidBody3* body)
{
	rigidBodies.push_back(body);
}

void CPhysicsEngine::AddForceGenerator(ForceGenerator* generator)
{
	forceGenerators.push_back(generator);
}

void CPhysicsEngine::AddGlobalForceGenerator(GlobalForceGenerator* generator)
{
	globalForceGenerators.push_back(generator);
}

// getter
RigidBody3* CPhysicsEngine::GetRigidBody(uint n) const
{
	return rigidBodies.at(n);
}

uint CPhysicsEngine::GetNumberOfRigidBodies(void) const
{
	return rigidBodies.size();
}