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
	pos = vec3(0, 0, 0);
	rot = quat(0, 0, 0, 0);
}

Object3::Object3(const vec3& position, const quat& rotation)
{
	pos = position;
	rot = rotation;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::Move(const vec3& vec)
{
	pos += vec;
}

void Object3::MoveRelative(const vec3& vec)
{
	pos += rot * vec;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::MoveTowards(const vec3& point, real distance)
{
	vec3 n = point;
	n -= pos;
	n.Normalise();

	pos += n * distance;
}

void Object3::MoveAlong(const vec3& direction, real distance)
{
	vec3 n = direction;
	n.Normalise();

	pos += n * distance;
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::Rotate(const quat& rotation)
{
	rot *= rotation;
}

void Object3::Rotate(real yaw, real pitch, real roll)
{
	rot *= quat(yaw, pitch, roll);
}

void Object3::RotateAroundAxis(const vec3& axis, real angle)
{
	rot *= quat(axis, angle);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::LookAt(const vec3& point)
{
	vec3 axis = point;

	axis -= pos;
	axis += rot.GetAxis();
	axis.Normalise();

	rot *= quat(axis, C_PI);
}

void Object3::LookAwayFrom(const vec3& point)
{
	vec3 axis = point;

	axis -= pos;
	axis *= -1;
	axis += rot.GetAxis();
	axis.Normalise();

	rot *= quat(axis, C_PI);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

void Object3::SetPosition(const vec3& position)
{
	pos = position;
}

void Object3::SetRelativePosition(Object3& object, const vec3& position)
{
	pos = object.GetPosition() + object.GetRotation() * position; 
}

void Object3::SetRotation(const quat& rotation)
{
	rot = rotation;
}

void Object3::SetRotation(const vec3& axis, real angle)
{
	rot = quat(axis, angle);
}

void Object3::SetRotation(real yaw, real pitch, real roll)
{
	rot = quat(yaw, pitch, roll);
}

//***************************************************************************//
//                                                                           //
//***************************************************************************//

vec3 Object3::GetPosition(void)
{
	return pos;
}

quat Object3::GetRotation(void)
{
	return rot;
}
