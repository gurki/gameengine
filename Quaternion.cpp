//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Quaternion.h"

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

Quaternion::Quaternion(const vec3& from, const vec3& to)
{
	SetFromDirections(from, to);
}

Quaternion::Quaternion(const vec3& to)
{
	SetFromDirection(to);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//
		 
void Quaternion::operator = (const Quaternion& quat)
{
	x = quat.x;
	y = quat.y;
	z = quat.z;
	w = quat.w;
}

bool Quaternion::operator == (const Quaternion& quat) const
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

bool Quaternion::operator != (const Quaternion& quat) const
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

Quaternion Quaternion::operator * (const Quaternion& quat) const
{
	return Quaternion(w * quat.x + x * quat.w + y * quat.z - z * quat.y,
					  w * quat.y - x * quat.z + y * quat.w + z * quat.x,
					  w * quat.z + x * quat.y - y * quat.x + z * quat.w,
					  w * quat.w - x * quat.x - y * quat.y - z * quat.z);
}

vec3 Quaternion::operator * (const vec3& vec) const
{
	Quaternion vecQuat, resQuat;

	vecQuat.x = vec.x;
	vecQuat.y = vec.y;
	vecQuat.z = vec.z;
	vecQuat.w = 0.0f;
 
	resQuat = ((*this) * vecQuat) * Conjugated();
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

vec3 operator * (const vec3& vec, const Quaternion& quat)
{
	Quaternion vecQuat, resQuat;

	vecQuat.x = vec.x;
	vecQuat.y = vec.y;
	vecQuat.z = vec.z;
	vecQuat.w = 0.0f;

	resQuat = (quat * vecQuat) * quat.Conjugated();
 
	return vec3(resQuat.x, resQuat.y, resQuat.z);
}

void Quaternion::operator *= (const Quaternion& quat)
{
    real q0 = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
    real q1 = w * quat.y - x * quat.z + y * quat.w + z * quat.x;
    real q2 = w * quat.z + x * quat.y - y * quat.x + z * quat.w;
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
	real n = x * x + y * y + z * z + w * w;

	if(n == 0.0 || n == 1.0)
	{
		return;
	}

	n = sqrtr(n);

	x /= n;
	y /= n;
	z /= n;
	w /= n;
}

Quaternion Quaternion::Normalised(void) const
{
	real n = x * x + y * y + z * z + w * w;

	if(n == 0.0 || n == 1.0)
	{
		return *this;
	}

	Quaternion quat = *this;

	n = sqrtr(n);

	quat.x /= n;
	quat.y /= n;
	quat.z /= n;
	quat.w /= n;

	return quat;
}

void Quaternion::Conjugate(void)
{
	x = -x;
	y = -y;
	z = -z;
}

Quaternion Quaternion::Conjugated(void) const
{
	return Quaternion(-x,-y,-z, w);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Quaternion::SetFromAxisAngle(const vec3& axis, real angle)
{
	real a = 0.5f * rad(angle);
	real s = sinr(a);
	
	vec3 v = axis; 
	v.Normalise();

	x = v.x * s;
	y = v.y * s;
	z = v.z * s;
	w = cosr(a);
}

void Quaternion::SetFromEulerAngles(real yaw, real pitch, real roll)
{
	real y = 0.5f * rad(yaw);
	real r = 0.5f * rad(roll);
	real p = 0.5f * rad(pitch);

	real siny = sinr(y);
	real sinr = sinr(r);
	real sinp = sinr(p);

	real cosy = cosr(y);
	real cosr = cosr(r);
	real cosp = cosr(p);

	this->x = siny * sinr * cosp + cosy * cosr * sinp;
	this->y = siny * cosr * cosp + cosy * sinr * sinp;
	this->z = cosy * sinr * cosp - siny * cosr * sinp;
	this->w = cosy * cosr * cosp - siny * sinr * sinp;
}

void Quaternion::SetFromDirections(const vec3& from, const vec3& to)
{
	vec3 f = from;
	f.Normalise();

	vec3 t = to;
	t.Normalise();

	vec3 n = t.Cross(f);
	w = 0.5f * t.Dot(f);
	real s = sinr(acosr(w));

	x = n.x * s;
	y = n.y * s;
	z = n.z * s;
}

void Quaternion::SetFromDirection(const vec3& to)
{
	vec3 f = vec3::Forward();

	vec3 t = to;
	t.Normalise();

	vec3 n = t.Cross(f);
	w = 0.5f * t.Dot(f);
	real s = sinr(acosr(w));

	x = n.x * s;
	y = n.y * s;
	z = n.z * s;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Quaternion::GetDirection(void) const
{
	return (*this) * vec3::Forward();
}

vec3 Quaternion::GetAxis(void) const
{
	return vec3(x, y,z).Normalise();
}

real Quaternion::GetAngle(void) const
{
	return deg(acosr(w) * 2.0f);
}

real Quaternion::GetYaw(void) const
{
	return atan2r(2.0 * (w * x + y * z), 1.0 - 2.0 * (z * z + x * x));
}

real Quaternion::GetPitch(void) const
{
	return asinr(2.0 * (w * z - y * x));
}

real Quaternion::GetRoll(void) const
{
	return atan2r(2.0 * (w * y + z * x), 1.0 - 2.0 * (y * y + z * z));
}

void Quaternion::GetAxisAngle(vec3& axis, real& angle) const
{
	axis = vec3(x, y, z);
	angle = deg(acosr(w) * 2.0f);
}

void Quaternion::GetEulerAngles(real& yaw, real& pitch, real& roll) const
{
	yaw = deg(atan2r(2.0 * (w * x + y * z), 1.0 - 2.0 * (z * z + x * x)));
	pitch = deg(asinr(2.0 * (w * z - y * x)));
	roll = deg(atan2r(2.0 * (w * y + z * x), 1.0 - 2.0 * (y * y + z * z)));
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

ostream& operator << (ostream& out, const Quaternion& quat)
{
	out << "{" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << "}";

	return out;
}

istream& operator >> (istream& in, Quaternion& quat)
{
	real x, y, z, w;

	in >> x >> y >> z >> w;

	quat = Quaternion(x, y, z, w);

	return in;
}

const Quaternion Quaternion::Zero(void)
{
	static const Quaternion quat(0, 0, 0, 0);
	return quat;
}

const Quaternion Quaternion::Identity(void)
{
	static const Quaternion quat(0, 0, 0, 1);
	return quat;
}