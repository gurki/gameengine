//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "MathLib.h"

#include <iomanip>
#include <iostream>

class Vector3
{
	public:
	
	// constructors

		Vector3(void)
		{
			for(uint d = 0; d < 3; d++)
			{
				v[d] = 0;
			}
		}
		
		Vector3(real x, real y, real z)
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
		}

		template <class S>
		Vector3(const S* ent)
		{
			for(uint d = 0; d < 3; d++)
			{
				v[d] = ent[d];
			}
		}
		
	// unary operators
	
		Vector3 operator - (void)
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = -v[d];
			}
			
			return ret;
		}
		
	// bool operators
	
		bool operator == (const Vector3& vec)
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
		
		bool operator != (const Vector3& vec)
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
		
		bool operator < (Vector3& vec)
		{
			return SquaredMagnitude() < vec.SquaredMagnitude();
		}
		
		bool operator <= (Vector3& vec)
		{
			return SquaredMagnitude() <= vec.SquaredMagnitude();
		}
		
		bool operator > (Vector3& vec)
		{
			return SquaredMagnitude() > vec.SquaredMagnitude();
		}
		
		bool operator >= (Vector3& vec)
		{
			return SquaredMagnitude() >= vec.SquaredMagnitude();
		}
		
	// arithmetic operators
	
		Vector3 operator + (const Vector3& vec) 
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = v[d] + vec.v[d];
			}
			
			return ret;
		}

		Vector3 operator - (const Vector3& vec) 
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = v[d] - vec.v[d];
			}
			
			return ret;
		}

		Vector3 operator * (const real num) 
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = v[d] * num;
			}
			
			return ret;
		}

		friend Vector3 operator * (const real num, const Vector3& vec) 
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = num * vec.v[d];
			}
			
			return ret;
		}
		
		Vector3 operator / (const real num) 
		{
			Vector3 ret;
			
			for(uint d = 0; d < 3; d++)
			{
				ret.v[d] = v[d] / num;
			}
		
			return ret;
		}
		
	// arithmetic assign operators
	
		void operator += (const Vector3& vec) 
		{
			for(uint d = 0; d < 3; d++)
			{
				v[d] += vec.v[d];
			}
		}
	
		void operator -= (const Vector3& vec) 
		{
			for(uint d = 0; d < 3; d++)
			{
				v[d] -= vec.v[d];
			}
		}
				
		void operator *= (const real num) 
		{
			for(uint d = 0; d < 3; d++)
			{	
				v[d] *= num;
			}
		}
				
		void operator /= (const real num) 
		{
			for(uint d = 0; d < 3; d++)
			{	
				v[d] /= num;
			}
		}
				
	// vector operations

		Vector3& Normalise(void)
		{
			(*this) *= (real)InverseMagnitude();

			return *this;
		}

		Vector3 Normalised(void)
		{
			return (*this) * (real)InverseMagnitude();
		}
	
		real Dot(const Vector3& vec)
		{
			real ret = 0;
			
			for(uint d = 0; d < 3; d++)
			{	
				ret += v[d] * vec.v[d];
			}
			
			return ret;
		}
		
		Vector3 Cross(const Vector3& vec)
		{
			return Vector3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
		}
		
	// properties
	
		double Magnitude(void)
		{
			real ret = 0;
			
			for(uint d = 0; d < 3; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return sqrt(ret);
		}
		
		real SquaredMagnitude(void)
		{
			real ret = 0;
			
			for(uint d = 0; d < 3; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return ret;
		}

		double InverseMagnitude(void)
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
			
			return 1.0 / sqrt(ret);
		}	
		
	// output
	
		void Print(void)
		{		
			std::cout << "{";
			
			for(uint d = 0; d < 3; d++)
			{	
				std::cout << v[d];
				
				if(d < 2)
				{
					std::cout << ", ";
				}
			}
			
			std::cout << "}" << std::endl;
		}		
		
	// member variables
	
		union 
		{
			real v[3];
			struct{ real x, y, z; };
		};
};

typedef Vector3 vec3;

#endif