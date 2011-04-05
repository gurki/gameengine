//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Object3.h"

// constructors
Object3::Object3(void)
{
	SetPosition( vec3::Zero() );
	SetOrientation( quat::Identity() );
	SetElasticity(0.8f);
}

Object3::Object3(const vec3& position)
{
	SetPosition(position);
	SetOrientation( quat::Identity() );
	SetElasticity(0.8f);
}

Object3::Object3(real x, real y, real z)
{
	SetPosition(x, y, z);
	SetOrientation( quat::Identity() );
	SetElasticity(0.8f);
}

// methods
void Object3::Render(void) const
{
	material.Bind();

	glBegin(GL_POINTS);

		glVertex3fv(pos.v); 

	glEnd();
}

void Object3::UpdateWorldMatrix(void)
{
	world.SetTranslation(pos);
	world.SetRotation(ori);
}

// setter
void Object3::SetPosition(const vec3& position)
{
	pos = position;
	world.SetTranslation(pos);
}

void Object3::SetPosition(real x, real y, real z)
{
	pos = vec3(x, y, z);
	world.SetTranslation(pos);
}

void Object3::SetOrientation(const quat& orientation)
{
	ori = orientation;
	world.SetRotation(ori);
}

void Object3::SetOrientation(real yaw, real pitch, real roll)
{
	ori = Quaternion::WithEulerAngles(yaw, pitch, roll);
	world.SetRotation(ori);
}

void Object3::SetElasticity(real elasticity)
{
	this->elasticity = elasticity;
}

void Object3::SetMaterial(const Material& material)
{
	this->material = material;
}

// getter
vec3 Object3::GetPosition(void) const
{
	return pos;
}

quat Object3::GetOrientation(void) const
{
	return ori;
}

real Object3::GetBoundingSphereRadius(void) const
{
	return 0.0f;
}

real Object3::GetElasticity(void) const
{
	return elasticity;
}