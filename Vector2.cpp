//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Vector2.h"
#include "MathLib.h"

Vector2::Vector2(void)
{
	for(uint d = 0; d < 2; d++)
	{
		v[d] = 0;
	}
}
		
Vector2::Vector2(real x, real y)
{
	v[0] = x;
	v[1] = y;
}
		
Vector2::Vector2(const real* ent)
{
	for(uint d = 0; d < 2; d++)
	{
		v[d] = ent[d];
	}
}
		
// unary operators
	
Vector2 Vector2::operator - (void) const
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = - v[d];
	}
			
	return ret;
}
		
// bool operators
	
bool Vector2::operator == (const Vector2& vec) const
{
	for(uint d = 0; d < 2; d++)
	{
		if(vec.v[d] != v[d])
		{
			return false;
		}
	}
			
	return true;
}
		
bool Vector2::operator != (const Vector2& vec) const
{
	for(uint d = 0; d < 2; d++)
	{
		if(vec.v[d] == v[d])
		{
			return false;
		}
	}
			
	return true;
}
		
// arithmetic operators
	
Vector2 Vector2::operator + (const Vector2& vec) const
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = v[d] + vec.v[d];
	}
			
	return ret;
}

Vector2 Vector2::operator - (const Vector2& vec) const 
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = v[d] - vec.v[d];
	}
			
	return ret;
}

Vector2 Vector2::operator * (const real num) const 
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = v[d] * num;
	}
			
	return ret;
}

Vector2 operator * (const real num, const Vector2& vec) 
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = num * vec.v[d];
	}
			
	return ret;
}
		
Vector2 Vector2::operator / (const real num) const 
{
	Vector2 ret;
			
	for(uint d = 0; d < 2; d++)
	{
		ret.v[d] = v[d] / num;
	}
		
	return ret;
}
		
// arithmetic assign operators
	
void Vector2::operator += (const Vector2& vec) 
{
	for(uint d = 0; d < 2; d++)
	{
		v[d] += vec.v[d];
	}
}
	
void Vector2::operator -= (const Vector2& vec) 
{
	for(uint d = 0; d < 2; d++)
	{
		v[d] -= vec.v[d];
	}
}
				
void Vector2::operator *= (const real num) 
{
	for(uint d = 0; d < 2; d++)
	{	
		v[d] *= num;
	}
}
				
void Vector2::operator /= (const real num) 
{
	for(uint d = 0; d < 2; d++)
	{	
		v[d] /= num;
	}
}
				
// vector operations

Vector2& Vector2::Normalise(void)
{
	(*this) *= (real)InverseMagnitude();

	return *this;
}

Vector2 Vector2::Normalised(void) const
{
	return (*this) * (real)InverseMagnitude();
}
	
real Vector2::Dot(const Vector2& vec) const
{
	real ret = 0;
			
	for(uint d = 0; d < 2; d++)
	{	
		ret += v[d] * vec.v[d];
	}
			
	return ret;
}

real Vector2::Cross(const Vector2& vec) const
{
	return x * vec.y - y * vec.x;
}
		
// properties
	
real Vector2::Magnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 2; d++)
	{	
		ret += v[d] * v[d];
	}
			
	return sqrtr(ret);
}
		
real Vector2::SquaredMagnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 2; d++)
	{	
		ret += v[d] * v[d];
	}
			
	return ret;
}

real Vector2::InverseMagnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 2; d++)
	{	
		ret += v[d] * v[d];
	}

	if(ret == 0.0) 
	{
		return 0.0;
	}
			
	return real(1.0 / sqrt(ret));
}	
		
// output
			
ostream& operator << (ostream& out, const Vector2& vec) 
{
	out << "{" << vec.x << ", " << vec.y << "}";
	return out;
}
 
istream& operator >> (istream& in, Vector2& vec) 
{
	real x, y;

	in >> x >> y;

	vec.x = x;
	vec.y = y;

	return in;
}	

const Vector2 Vector2::Up(void)
{
	static const Vector2 vec = Vector2(0, 1);
	return vec;
}

const Vector2 Vector2::Right(void)
{
	static const Vector2 vec = Vector2(1, 0);
	return vec;
}

const Vector2 Vector2::One(void)
{
	static const Vector2 vec = Vector2(1, 1);
	return vec;
}

const Vector2 Vector2::Zero(void) 
{
	static const Vector2 vec = Vector2(0, 0);
	return vec;
}