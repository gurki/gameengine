//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Integrator.h"

Derivative CIntegrator::f(const Object& obj, real dt, const Derivative& d)
{	
	Derivative out;

    out.dp = obj.vel + d.dv * dt;
    out.dv = obj.f * obj.invm;

	return out;
}

void CIntegrator::RK4(Object& obj, real dt)
{
    Derivative a = f(obj, 0.0f, Derivative());
    Derivative b = f(obj, dt * 0.5f, a);
    Derivative c = f(obj, dt * 0.5f, b);
    Derivative d = f(obj, dt, c);

    const vec3 dp = 1.0f / 6.0f * (a.dp + 2.0f * (b.dp + c.dp) + d.dp);
    const vec3 dv = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

    obj.pos = obj.pos + dp * dt;
    obj.vel = obj.vel + dv * dt;
}

void CIntegrator::Euler(Object& obj, real dt)
{
	obj.pos = obj.pos + obj.vel * dt;
	obj.vel = obj.vel + obj.f * obj.invm * dt;
}

void CIntegrator::Newton(Object& obj, real dt)
{
	vec3 adt = obj.f * obj.invm * dt;

	obj.pos = obj.pos + obj.vel * dt + 0.5 * adt * dt; 
	obj.vel = obj.vel + adt;
}