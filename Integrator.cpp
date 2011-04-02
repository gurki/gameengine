//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//
/*
#include "Integrator.h"

Derivative CIntegrator::f(const Particle& p, real dt, const Derivative& d)
{	
	Derivative out;

    out.dp = p.GetVelocity() + d.dv * dt;
    out.dv = p.GetForce() * p.GetInverseMass();

	return out;
}

// runge-kutta 4th order
void CIntegrator::RungeKutta4(Particle& p, real dt)
{
	Derivative s;
	
	s.dp = p.GetVelocity();
	s.dv = p.GetForce() * p.GetInverseMass();

    Derivative a = f(p, 0.0f, s);
    Derivative b = f(p, dt * 0.5f, a);
    Derivative c = f(p, dt * 0.5f, b);
    Derivative d = f(p, dt, c);

    const vec3 dp = 1.0f / 6.0f * (a.dp + 2.0f * (b.dp + c.dp) + d.dp);
    const vec3 dv = 1.0f / 6.0f * (a.dv + 2.0f * (b.dv + c.dv) + d.dv);

	p.SetPosition(p.GetPosition() + dp * dt);
	p.SetVelocity(p.GetVelocity() + dv * dt);
}

// euler 1st order
void CIntegrator::Euler1(Particle& p, real dt)
{
	p.SetPosition(p.GetPosition() + p.GetVelocity() * dt);
	p.SetVelocity(p.GetVelocity() + p.GetForce() * p.GetInverseMass() * dt);
}

// newton 1st order
void CIntegrator::Newton1(Particle& p, real dt)
{
	vec3 adt = p.GetForce() * p.GetInverseMass() * dt;

	p.SetPosition(p.GetPosition() + p.GetVelocity() * dt + 0.5 * adt * dt); 
	p.SetVelocity(p.GetVelocity() + adt);
}

// symplectic euler 1st order
void CIntegrator::SymplecticEuler1(Particle& p, real dt)
{
	p.SetVelocity(p.GetVelocity() + p.GetForce() * p.GetInverseMass() * dt);
	p.SetPosition(p.GetPosition() + p.GetVelocity() * dt);
}

// leapfrog 2nd order
void CIntegrator::Leapfrog2(Particle& p, real dt)
{
	vec3 hadt = 0.5 * p.GetForce() * p.GetInverseMass() * dt;

	p.SetVelocity(p.GetVelocity() + hadt);
	p.SetPosition(p.GetPosition() + p.GetVelocity() * dt);
	p.SetVelocity(p.GetVelocity() + hadt);
}

// velocity verlet 2nd order
void CIntegrator::VelocityVerlet2(Particle& p, real dt)
{
	vec3 hadt = 0.5 * p.GetForce() * p.GetInverseMass() * dt;

	p.SetVelocity(p.GetVelocity() + hadt);
	p.SetPosition(p.GetPosition() + p.GetVelocity()*dt + hadt*dt);
	p.SetVelocity(p.GetVelocity() + hadt);
}

// Verlet integration step
void CIntegrator::VelocityLessVerlet2(Particle& p, real dt) 
{
	// x(t+dt) = x(t) + x(t) - x(t-1) + at²;
	// x(t-1) = x(t);
}
*/
/*
   case 0:                          // Euler method 
      k1 = h * (*fcn)(y0);
      ynew = y0 + k1;
      break;
   case 1:                          // Modified Euler
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1);
      ynew = y0 + (k1 + k2) / 2;
      break;
   case 2:                          // Heuns method
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + 2 * k1 / 3);
      ynew = y0 + k1 / 4 + 3 * k2 / 4;
      break;
   case 3:                          // Midpoint
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1 / 2);
      ynew = y0 + k2;
      break;
   case 4:                          // 4'th order Runge-kutta
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1/2);
      k3 = h * (*fcn)(y0 + k2/2);
      k4 = h * (*fcn)(y0 + k3);
      ynew = y0 + k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6;
      break;
   case 5:                          // England 4'th order, six stage
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1 / 2);
      k3 = h * (*fcn)(y0 + (k1 + k2) / 4);
      k4 = h * (*fcn)(y0 - k2 + 2 * k3);
      k5 = h * (*fcn)(y0 + (7 * k1 + 10 * k2 + k4) / 27);
      k6 = h * (*fcn)(y0 + (28*k1 - 125*k2 + 546*k3 + 54*k4 - 378*k5) / 625);
      ynew = y0 + k1 / 6 + 4 * k3 / 6 + k4 / 6;
      break;
	  */