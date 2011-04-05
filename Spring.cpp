//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Spring.h"

// constructors
Spring::Spring(void)
{
	l = 0.0f;
	k = 1.0f; 
	b = 1.0f;
}

Spring::Spring(real l, real k, real b)
{
	this->l = inf(l, 0.0f);
	this->k = k;
	this->b = b;
}

// setter
void Spring::SetRestLength(real l)
{
	this-> l = inf(l, 0.0f);
}

void Spring::SetDamping(real b)
{
	this->b = b;
}

void Spring::SetStiffness(real k)
{
	this->k = k;
}

// getter
real Spring::GetRestLength(void) const
{
	return l;
}

real Spring::GetDamping(void) const
{
	return b;
}

real Spring::GetStiffness(void) const
{
	return k;
}