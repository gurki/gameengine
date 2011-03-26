//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "MathLib.h"
#include "Vector2.h"

class CRectangle
{
	public:

		CRectangle(void);
		CRectangle(const vec2& position, const vec2& dimensions);
		CRectangle(real x, real y, real width, real height);

		virtual void SetPosition(const vec2& position);
		virtual void SetPosition(real x, real y);

		virtual void SetDimensions(const vec2& dimensions);
		virtual void SetDimensions(real width, real height);
		
		vec2 GetPosition(void) const;
		vec2 GetDimensions(void) const;

		vec2 GetCenter(void) const;
		vec2 GetAbsoluteCenter(void) const;

		real GetRatio(void) const;

	protected:

		vec2 pos;
		vec2 dim;
};

typedef CRectangle rect;