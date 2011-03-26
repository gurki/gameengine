//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Vector2.h"
#include "Types.h"
#include "OpenGL.h"
#include "Transform2.h"

#include <iostream>

using namespace std;

class Object2
{
	public:
	
		// constructors
		Object2(void);
		Object2(real x, real y);
		Object2(const vec2& position);
		
		// methods
		virtual void Render(void) const;
		
		// setter
		virtual void SetPosition(real x, real y);
		virtual void SetPosition(const vec2& position);
		
		virtual void SetRotation(real radians);
		
		virtual void SetTransformation(const trans2& t);
				
		// getter
		vec2 GetPosition(void) const;
		real GetRotation(void) const;
		
		trans2 GetTransformation(void) const;
		
	protected:
	
		// variables
		vec2 pos;
		real rot;
		
		trans2 trans;
};