//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once
#pragma warning(disable: 4250)

#include "MathLib.h"
#include "Vector3.h"
#include "OpenGL.h"
#include "Quaternion.h"
#include "Transform3.h"
#include "Material.h"

class Object3
{
	public:

		// constructors
		Object3(void);
		Object3(const vec3& position);
		Object3(real x, real y, real z);

		// methods
		virtual void Render(void) const;

		// setter
		virtual void SetPosition(const vec3& position);
		virtual void SetPosition(real x, real y, real z);
		
		virtual void SetOrientation(const quat& orientation);
		virtual void SetOrientation(real yaw, real pitch, real roll);

		void SetMaterial(const Material& material);

		// getter
		vec3 GetPosition(void) const;
		quat GetOrientation(void) const;

	protected:

		void UpdateWorldMatrix(void);

		// variables
		vec3 pos;
		quat ori;

		trans3 modelMatrix;

		Material material;
};