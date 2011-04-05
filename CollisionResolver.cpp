//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "CollisionResolver.h"
#include "Timer.h"

vector<RigidBody3*>* CollisionResolver::bodies = 0;
vector<Contact> CollisionResolver::contacts;

void CollisionResolver::HandleCollisions(vector<RigidBody3*>* rigidBodies)
{
	bodies = rigidBodies;

	contacts.clear();

	CourseDetection();
	FineDetection();
	Resolving();
}
		
void CollisionResolver::CourseDetection(void)
{
	Contact c;
	real vn;
	vec3 d;

	for(uint i = 0; i < bodies->size(); i++)
	{
		for(uint j = 0; j < bodies->size(); j++)
		{
			c.b1 = bodies->at(i);
			c.b2 = bodies->at(j);

			d = c.b2->GetPosition() - c.b1->GetPosition();
			c.v = c.b2->GetLinearVelocity() - c.b1->GetLinearVelocity(); 
			c.n = d.Normalised();

			vn = c.n.Dot(c.v);

			if(vn < 0) // nähern sich
			{
				c.v = c.n * vn;
				c.s = d.Magnitude() - (c.b1->GetBoundingSphereRadius() + c.b2->GetBoundingSphereRadius());

				if(c.s <= 0) // interpenetrieren
				{
					contacts.push_back(c);
				}
			}		
		}
	}
}

void CollisionResolver::FineDetection(void)
{

}

void CollisionResolver::Resolving(void)
{
	vec3 p1, p2;
	vec3 v1, v2;

	real e;

	for(uint i = 0; i < contacts.size(); i++)
	{
		p1 = contacts.at(i).b1->GetPosition();
		p2 = contacts.at(i).b2->GetPosition();

		v1 = contacts.at(i).b1->GetLinearVelocity();
		v2 = contacts.at(i).b2->GetLinearVelocity();

		e = sqrtr(contacts.at(i).b1->GetElasticity() * contacts.at(i).b2->GetElasticity());

		contacts.at(i).b1->SetPosition(p1 + contacts.at(i).n * contacts.at(i).s * 0.5f);
		contacts.at(i).b2->SetPosition(p2 - contacts.at(i).n * contacts.at(i).s * 0.5f);

		contacts.at(i).b1->SetLinearVelocity(v1 + contacts.at(i).v * 0.5f * e);
		contacts.at(i).b2->SetLinearVelocity(v2 - contacts.at(i).v * 0.5f * e);
	}
}
