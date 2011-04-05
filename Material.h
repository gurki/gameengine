//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Color.h"
#include "Types.h"
#include "OpenGL.h"

class Material
{
	public:

		Material(void);
		Material(real R, real G, real B);
		Material(const Color& color);

		void Bind(void) const;

	protected:

		Color color;
};

#endif