//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _OBJECT3_H
#define _OBJECT3_H

#include "Types.h"
#include "Vector3.h"
#include "Quaternion.h"

class Object3
{
	public:

		Object3(void);
		Object3(const vec3& position, const quat& rotation);

		void Move(const vec3& direction);
		void MoveRelative(const vec3& direction);

		void MoveTowards(const vec3& point, real distance);
		void MoveAlong(const vec3& direction, real distance);

		void Rotate(const quat& rotation);
		void Rotate(real yaw, real pitch, real roll);
		void RotateAroundAxis(const vec3& axis, real angle);

		void LookAt(const vec3& point);
		void LookAwayFrom(const vec3& point);

		void SetPosition(const vec3& position);
		void SetRelativePosition(Object3& object, const vec3& position);

		void SetRotation(const quat& rotation);
		void SetRotation(const vec3& axis, real angle);
		void SetRotation(real yaw, real pitch, real roll);

		vec3 GetPosition(void);
		quat GetRotation(void);

	protected:

		vec3 pos;
		quat rot;
};

#endif