//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Sphere.h"
#include "Color.h"
#include "Transform2.h"
#include "Vector2.h"

Sphere::Sphere(void) : Object3()
{
	SetRadius(0.5f);
}

Sphere::Sphere(const vec3& position, real radius) : Object3(position)
{
	SetRadius(radius);
}

void Sphere::Render(void) const
{
	static const uint iter = 3;
	static const real alpha = C_2PI / (4.0f * (iter + 1));
	static const uint k = floor(4.0f * (iter + 1) * 0.5f);
	static const real d = sin(alpha) * radius * 0.5f;

	static vec3 v[k];
	static vec3 n[k];
	
	real beta = alpha * 0.5f;
	
	// ring
	for(uint i = 0; i < k * 0.5f; i++)
	{		
		v[2*i].x = cos(beta) * radius;
		v[2*i].y =-d;
		v[2*i].z = sin(beta) * radius;		
		
		v[2*i+1].x = v[2*i].x;
		v[2*i+1].y = d;
		v[2*i+1].z = v[2*i].z;		
		
		n[2*i].x = v[2*i].x;
		n[2*i].y = 0;
		n[2*i].z = v[2*i].z;
		
		n[2*i+1] = n[2*i];
		
		beta += alpha;
	}
	
	// faces
	for(uint i = 0; i < k; i++)
	{
		for(uint j = 0; j <= i; j++)
		{
			
		}
	}

	glPushMatrix();
	glMultMatrixf(world.v);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, v);
	glNormalPointer(GL_FLOAT, 0, n);

	// x-axis ring
	Color::WithOrange().Bind();	
	glPushMatrix();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, k);		
	for(uint i = 0; i < 3; i++)
	{
		glMultMatrixf(Transform3::With90DegreeRotationAboutY().v);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, k);	
	}
	glPopMatrix();

	// y-axis ring
	Color::WithGreen().Bind();	
	glPushMatrix();
	glMultMatrixf(Transform3::With90DegreeRotationAboutZ().v);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, k);		
	for(uint i = 0; i < 3; i++)
	{
		glMultMatrixf(Transform3::With90DegreeRotationAboutY().v);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, k);	
	}
	glPopMatrix();
	
	// z-axis ring
	Color::WithPurple().Bind();	
	glPushMatrix();
	glMultMatrixf(Transform3::With90DegreeRotationAboutX().v);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, k);		
	for(uint i = 0; i < 3; i++)
	{
		glMultMatrixf(Transform3::With90DegreeRotationAboutY().v);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, k);	
	}
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();
}

void Sphere::SetRadius(real radius)
{
	this->radius = inf(radius, 0);
}
		
// getter
real Sphere::GetRadius(void) const
{
	return radius;
}

