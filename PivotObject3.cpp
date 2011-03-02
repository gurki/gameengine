//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "PivotObject3.h"


PivotObject3::PivotObject3(void) : Object3()
{
	piv = vec3(0, 0, 0);
}

PivotObject3::PivotObject3(const vec3& position, const quat& rotation, const vec3& pivot) : Object3(position, rotation)
{
	piv = pivot;
}

void PivotObject3::RotateAroundPivot(const quat& quat)
{
	pos = piv + (pos - piv) * quat;
}

void PivotObject3::RotateAroundPivot(const vec3& axis, real angle)
{
	pos = piv + (pos - piv) * quat(axis, angle);
}

void PivotObject3::RotateAroundPivot(real yaw, real pitch, real roll)
{
	pos = piv + (pos - piv) * quat(yaw, pitch, roll);
}
	
void PivotObject3::SetRotationAroundPivot(const quat& quat)
{

}

void PivotObject3::SetRotationAroundPivot(const vec3& axis, real angle)
{

}

void PivotObject3::SetRotationAroundPivot(real yaw, real pitch, real roll)
{

}

void PivotObject3::SetPivot(const vec3& pivot)
{
	piv = pivot;
}

vec3 PivotObject3::GetPivot(void) const
{
	return piv;
}

