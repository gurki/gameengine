//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Material.h"

Material::Material(void)
{
	color = Color::WithWhite();
}

Material::Material(real R, real G, real B)
{
	color = Color::WithRGB(R, G, B);
}

Material::Material(const Color& color)
{
	this->color = color;
}

void Material::Bind(void) const
{
	color.Bind();
}