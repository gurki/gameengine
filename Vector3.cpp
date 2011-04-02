//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Vector3.h"
#include "MathLib.h"

Vector3::Vector3(void)
{
	for(uint d = 0; d < 3; d++)
	{
		v[d] = 0;
	}
}
		
Vector3::Vector3(real x, real y, real z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
		
Vector3::Vector3(const real* ent)
{
	for(uint d = 0; d < 3; d++)
	{
		v[d] = ent[d];
	}
}
		
// unary operators
	
Vector3 Vector3::operator - (void) const
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = - v[d];
	}
			
	return ret;
}
		
// bool operators
	
bool Vector3::operator == (const Vector3& vec) const
{
	for(uint d = 0; d < 3; d++)
	{
		if(vec.v[d] != v[d])
		{
			return false;
		}
	}
			
	return true;
}
		
bool Vector3::operator != (const Vector3& vec) const
{
	for(uint d = 0; d < 3; d++)
	{
		if(vec.v[d] == v[d])
		{
			return false;
		}
	}
			
	return true;
}
		
// arithmetic operators
	
Vector3 Vector3::operator + (const Vector3& vec) const
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = v[d] + vec.v[d];
	}
			
	return ret;
}

Vector3 Vector3::operator - (const Vector3& vec) const 
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = v[d] - vec.v[d];
	}
			
	return ret;
}

Vector3 Vector3::operator * (const real num) const 
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = v[d] * num;
	}
			
	return ret;
}

Vector3 operator * (const real num, const Vector3& vec) 
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = num * vec.v[d];
	}
			
	return ret;
}
		
Vector3 Vector3::operator / (const real num) const 
{
	Vector3 ret;
			
	for(uint d = 0; d < 3; d++)
	{
		ret.v[d] = v[d] / num;
	}
		
	return ret;
}
		
// arithmetic assign operators
	
void Vector3::operator += (const Vector3& vec) 
{
	for(uint d = 0; d < 3; d++)
	{
		v[d] += vec.v[d];
	}
}
	
void Vector3::operator -= (const Vector3& vec) 
{
	for(uint d = 0; d < 3; d++)
	{
		v[d] -= vec.v[d];
	}
}
				
void Vector3::operator *= (const real num) 
{
	for(uint d = 0; d < 3; d++)
	{	
		v[d] *= num;
	}
}
				
void Vector3::operator /= (const real num) 
{
	for(uint d = 0; d < 3; d++)
	{	
		v[d] /= num;
	}
}
				
// vector operations

Vector3& Vector3::Normalise(void)
{
	(*this) *= (real)InverseMagnitude();

	return *this;
}

Vector3 Vector3::Normalised(void) const
{
	return (*this) * (real)InverseMagnitude();
}
	
real Vector3::Dot(const Vector3& vec) const
{
	real ret = 0;
			
	for(uint d = 0; d < 3; d++)
	{	
		ret += v[d] * vec.v[d];
	}
			
	return ret;
}
		
Vector3 Vector3::Cross(const Vector3& vec) const
{
	return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}
		
// properties
	
real Vector3::Magnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 3; d++)
	{	
		ret += v[d] * v[d];
	}
			
	return sqrtr(ret);
}
		
real Vector3::SquaredMagnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 3; d++)
	{	
		ret += v[d] * v[d];
	}
			
	return ret;
}

real Vector3::InverseMagnitude(void) const
{
	real ret = 0;
			
	for(uint d = 0; d < 3; d++)
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
			
ostream& operator << (ostream& out, const Vector3& vec) 
{
	out << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
	return out;
}
 
istream& operator >> (istream& in, Vector3& vec) 
{
	real x, y, z;

	in >> x >> y >> z;

	vec.x = x;
	vec.y = y;
	vec.z = z;

	return in;
}	

// static members
const Vector3 Vector3::X(void)
{
	static const Vector3 vec(1, 0, 0);
	return vec;
}

const Vector3 Vector3::Y(void)
{
	static const Vector3 vec(0, 1, 0);
	return vec;
}

const Vector3 Vector3::Z(void)
{
	static const Vector3 vec(0, 0, 1);
	return vec;
}

const Vector3 Vector3::Up(void)
{
	static const Vector3 vec( 0, 1, 0);
	return vec;
}

const Vector3 Vector3::Down(void)
{
	static const Vector3 vec( 0,-1, 0);
	return vec;
}

const Vector3 Vector3::Left(void)
{
	static const Vector3 vec(-1, 0, 0);
	return vec;
}

const Vector3 Vector3::Right(void)
{
	static const Vector3 vec( 1, 0, 0);
	return vec;
}

const Vector3 Vector3::Forward(void)
{
	static const Vector3 vec( 0, 0,-1);
	return vec;
}

const Vector3 Vector3::Backward(void)
{
	static const Vector3 vec(0, 0, 1);
	return vec;
}

const Vector3 Vector3::One(void)
{
	static const Vector3 vec( 1, 1, 1);
	return vec;
}

const Vector3 Vector3::Zero(void)
{
	static const Vector3 vec( 0, 0, 0);
	return vec;
}
