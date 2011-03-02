//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _PIVOT_OBJECT3_H
#define _PIVOT_OBJECT3_H

#include "Object3.h"

class PivotObject3 : public Object3
{
	public:

		PivotObject3(void);
		PivotObject3(const vec3& position, const quat& rotation, const vec3& pivot);

		void RotateAroundPivot(const quat& quat);
		void RotateAroundPivot(const vec3& axis, real angle);
		void RotateAroundPivot(real yaw, real pitch, real roll);
		
		void SetRotationAroundPivot(const quat& quat);
		void SetRotationAroundPivot(const vec3& axis, real angle);
		void SetRotationAroundPivot(real yaw, real pitch, real roll);

		void SetPivot(const vec3& pivot);

		vec3 GetPivot(void) const;

	protected:

		vec3 piv;
};

#endif