//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _OBJECT3_H
#define _OBJECT3_H

#include "MathLib.h"
#include "Vector3.h"
#include "Quaternion.h"

class Object3
{
	public:

		Object3(void);
		Object3(const vec3& position, const quat& rotation);
		Object3(real x, real y, real z, real yaw = 0, real pitch = 0, real roll = 0);

		virtual void Move(const vec3& direction);
		virtual void Move(real x, real y, real z);

		virtual void MoveRelative(const vec3& direction);
		virtual void MoveRelative(real x, real y, real z);

		virtual void LookAt(const vec3& point);
		virtual void LookAt(real yaw, real pitch, real roll);

		virtual void Rotate(const vec3& direction);
		virtual void Rotate(real yaw, real pitch, real roll);

		virtual void SetPosition(const vec3& position);
		virtual void SetPosition(real x, real y, real z);
		
		virtual void SetRotation(const vec3& direction);
		virtual void SetRotation(real yaw, real pitch, real roll);

		vec3 GetPosition(void) const;
		quat GetRotation(void) const;

	protected:

		vec3 pos;
		quat rot;
};

#endif