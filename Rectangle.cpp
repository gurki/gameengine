#include "Rectangle.h"

CRectangle::CRectangle(void)
{
	pos = vec2::Zero();
	dim = vec2::Zero();
}

CRectangle::CRectangle(const vec2& position, const vec2& dimensions)
{
	pos = position;

	dim.x = inf(dimensions.x, 0);
	dim.y = inf(dimensions.y, 0);
}

CRectangle::CRectangle(real x, real y, real width, real height)
{
	pos = vec2(x, y);
	
	dim.x = inf(width, 0);
	dim.y = inf(height, 0);
}
		
void CRectangle::SetPosition(const vec2& position)
{
	pos = position;
}

void CRectangle::SetPosition(real x, real y)
{
	pos = vec2(x, y);
}

void CRectangle::SetDimensions(const vec2& dimensions)
{
	dim.x = inf(dimensions.x, 0);
	dim.y = inf(dimensions.y, 0);
}

void CRectangle::SetDimensions(real width, real height)
{
	dim.x = inf(width, 0);
	dim.y = inf(height, 0);
}

vec2 CRectangle::GetPosition(void) const
{
	return pos;
}

vec2 CRectangle::GetDimensions(void) const
{
	return dim;
}

vec2 CRectangle::GetCenter(void) const
{
	return dim * 0.5;
}

vec2 CRectangle::GetAbsoluteCenter(void) const
{
	return pos + (dim * 0.5);
}

real CRectangle::GetRatio(void) const
{
	return dim.x / dim.y;
}