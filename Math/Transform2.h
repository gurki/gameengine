//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Matrix3x3.h"
#include "Vector2.h"
#include "MathLib.h"

class Transform2 : public Matrix3x3
{
	public:
		
		// constructors
		Transform2(void);
		Transform2(const Vector2& translation, real radians);
	
		// vector arithmetics
		Vector2 operator * (const Vector2& v) const;
		friend Vector2 operator * (const Vector2& v, const Transform2& t);
	
		// methods
		Vector2 FromWorldToLocal(const Vector2& v) const;
		Vector2 FromLocalToWorld(const Vector2& v) const;
	
		// setter
		Transform2& SetRotation(real radians);
		Transform2& SetTranslation(const Vector2& translation);
};

typedef Transform2 trans2;
