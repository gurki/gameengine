//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Quaternion.h"

#include <iostream>

using namespace std;

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion::Quaternion(void)
{
	for(uint n = 0; n < 4; n++)
	{
		v[n] = 0;
	}
}

Quaternion::Quaternion(const real* v)
{
	for(uint n = 0; n < 4; n++)
	{
		this->v[n] = v[n];
	}
}

Quaternion::Quaternion(real x, real y, real z, real w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Quaternion::Quaternion(const vec3& axis, real angle)
{
	SetFromAxisAngle(axis, angle);
}

Quaternion::Quaternion(real yaw, real pitch, real roll)
{
	SetFromEulerAngles(yaw, pitch, roll);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//
		 
bool Quaternion::operator == (const Quaternion& quat)
{
	for(uint n = 0; n < 4; n++)
	{
		if(quat.v[n] != v[n])
		{
			return false;
		}
	}
			
	return true;
}

bool Quaternion::operator != (const Quaternion& quat)
{
	for(uint n = 0; n < 4; n++)
	{
		if(quat.v[n] == v[n])
		{
			return false;
		}
	}
			
	return true;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Quaternion Quaternion::operator * (const Quaternion& quat)
{
	return Quaternion(y * quat.x + x * quat.y + z * quat.w - w * quat.z,
					  x * quat.z - y * quat.w + z * quat.x + w * quat.y,
					  x * quat.w + y * quat.z - z * quat.y + w * quat.x,
					  x * quat.x - y * quat.y - z * quat.z - w * quat.w);
}

vec3 Quaternion::operator * (const vec3& vec)
{
	vec3 v = vec;
	v.Normalise();
 
	Quaternion vecQuat, resQuat;

	vecQuat.x = v.x;
	vecQuat.y = v.y;
	vecQuat.z = v.z;
	vecQuat.w = 0.0f;
 
	resQuat = vecQuat * Conjugated();
	resQuat = (*this) * resQuat;
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

vec3 operator * (const vec3& vec, Quaternion& quat)
{
	vec3 v = vec;
	v.Normalise();
 
	Quaternion vecQuat, resQuat;

	vecQuat.x = v.x;
	vecQuat.y = v.y;
	vecQuat.z = v.z;
	vecQuat.w = 0.0f;
 
	resQuat = (quat * vecQuat) * quat.Conjugated();
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

void Quaternion::operator *= (const Quaternion& quat)
{
	real q0 = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
	real q1 = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
	real q2 = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
	real q3 = w * quat.w - x * quat.x - y * quat.y - z * quat.z;

	x = q0;
	y = q1;
	z = q2;
	w = q3;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Quaternion::Normalise(void)
{
	real mag2 = x * x + y * y + z * z + w * w;

	if(mag2 == 0.0)
	{
		return;
	}

	if(abs(mag2 - 1.0f) > C_EPSILON) 
	{
		real mag = (real)sqrt(mag2);

		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}

Quaternion Quaternion::Normalised(void)
{
	real mag2 = x * x + y * y + z * z + w * w;

	if(mag2 == 0.0)
	{
		return *this;
	}

	Quaternion quat = *this;

	if(abs(mag2 - 1.0f) > C_EPSILON) 
	{
		real mag = (real)sqrt(mag2);

		quat.x /= mag;
		quat.y /= mag;
		quat.z /= mag;
		quat.w /= mag;
	}

	return quat;
}

void Quaternion::Conjugate(void)
{
	x = -x;
	y = -y;
	z = -z;
}

Quaternion Quaternion::Conjugated(void)
{
	return Quaternion(-x,-y,-z, w);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Quaternion::SetFromAxisAngle(const vec3& axis, real angle)
{
	vec3 v = axis; 
	real s = sin(angle * 0.5);
 
	v.Normalise();

	x = v.x * s;
	y = v.y * s;
	z = v.z * s;
	w = cos(angle * 0.5);
}

void Quaternion::SetFromEulerAngles(real yaw, real pitch, real roll)
{
	double y = C_PIDIV180 / 2.0 * yaw;
	double p = C_PIDIV180 / 2.0 * pitch;
	double r = C_PIDIV180 / 2.0 * roll;
 
	real sinp = sin(p);
	real siny = sin(y);
	real sinr = sin(r);

	real cosp = cos(p);
	real cosy = cos(y);
	real cosr = cos(r);
 
	x = sinr * cosp * cosy - cosr * sinp * siny;
	y = cosr * sinp * cosy + sinr * cosp * siny;
	z = cosr * cosp * siny - sinr * sinp * cosy;
	w = cosr * cosp * cosy + sinr * sinp * siny;
 
	Normalise();
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Quaternion::GetAxis(void)
{
	return vec3(x, y,z).Normalise();
}

real Quaternion::GetAngle(void)
{
	return acos(w) * 2.0f;
}

real Quaternion::GetYaw(void)
{
	return atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (z * z + x * x));
}

real Quaternion::GetPitch(void)
{
	return asin(2.0 * (w * z - y * x));
}

real Quaternion::GetRoll(void)
{
	return atan2(2.0 * (w * y + z * x), 1.0 - 2.0 * (y * y + z * z));
}

void Quaternion::GetAxisAngle(vec3& axis, real& angle)
{
	axis = vec3(x, y, z).Normalised();
	angle = acos(w) * 2.0f;
}

void Quaternion::GetEulerAngles(real& yaw, real& pitch, real& roll)
{
	yaw = atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (z * z + x * x));
	pitch = asin(2.0 * (w * z - y * x));
	roll = atan2(2.0 * (w * y + z * x), 1.0 - 2.0 * (y * y + z * z));
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Quaternion::Print(void)
{		
	std::cout << "{";
			
	for(uint d = 0; d < 4; d++)
	{	
		std::cout << v[d];
				
		if(d < 3)
		{
			std::cout << ", ";
		}
	}
			
	std::cout << "}" << std::endl;
}		