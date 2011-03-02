//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Object3.h"

//***************************************************************************//
//                                                                           //
//***************************************************************************//

Object3::Object3(void)
{
	pos = vec3::Zero();
	rot = quat::Identity();
}

Object3::Object3(const vec3& position, const quat& rotation)
{
	pos = position;
	rot = rotation;
}

Object3::Object3(real x, real y, real z, real yaw, real pitch, real roll)
{
	pos = vec3(x, y, z);
	rot = quat(yaw, pitch, roll);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::Move(const vec3& vec)
{
	pos += vec;
}

void Object3::Move(real x, real y, real z)
{
	pos += vec3(x, y, z);
}

void Object3::MoveRelative(const vec3& vec)
{
	pos += rot * vec;
}

void Object3::MoveRelative(real x, real y, real z)
{
	pos += rot * vec3(x, y, z);
}

void Object3::LookAt(const vec3& point)
{
	vec3 d = point - pos;

	real s = deg(atan2r(d.x, d.z)) + 180;
	real t = deg(asinr(d.y / d.Magnitude()));

	rot = quat(s, t, 0);
}

void Object3::LookAt(real x, real y, real z)
{
	vec3 point(x, y, z);

	vec3 d = point - pos;

	real s = deg(atan2r(d.x, d.z)) + 180;
	real t = deg(asinr(d.y / d.Magnitude()));

	rot = quat(s, t, 0);
}

void Object3::Rotate(const vec3& direction)
{
	rot *= quat(direction);
}

void Object3::Rotate(real yaw, real pitch, real roll)
{
	rot *= quat(yaw, pitch, roll);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::SetPosition(const vec3& position)
{
	pos = position;
}

void Object3::SetPosition(real x, real y, real z)
{
	pos = vec3(x, y, z);
}

void Object3::SetRotation(const vec3& direction)
{
	rot = quat(direction);
}

void Object3::SetRotation(real yaw, real pitch, real roll)
{
	rot = quat(yaw, pitch, roll);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Object3::GetPosition(void) const
{
	return pos;
}

quat Object3::GetRotation(void) const
{
	return rot;
}
