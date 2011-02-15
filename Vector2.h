//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "Vector.h"

template <class T>
class Vector<T, 2>
{
	public:
	
	// constructors

		Vector(void)
		{
			for(uint d = 0; d < 2; d++)
			{
				v[d] = 0;
			}
		}
		
		Vector(T x, T y)
		{
			v[0] = x;
			v[1] = y;
		}

		template <class S>
		Vector(const S* ent)
		{
			for(uint d = 0; d < 2; d++)
			{
				v[d] = ent[d];
			}
		}
		
	// unary operators
	
		Vector<T, 2> operator - (void)
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = -v[d];
			}
			
			return ret;
		}
		
	// bool operators
	
		bool operator == (const Vector<T, 2>& vec)
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
		
		bool operator != (const Vector<T, 2>& vec)
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
		
		bool operator < (const Vector<T, 2>& vec)
		{
			return mag2() < vec.mag2();
		}
		
		bool operator <= (const Vector<T, 2>& vec)
		{
			return mag2() <= vec.mag2();
		}
		
		bool operator > (const Vector<T, 2>& vec)
		{
			return mag2() > vec.mag2();
		}
		
		bool operator >= (const Vector<T, 2>& vec)
		{
			return mag2() >= vec.mag2();
		}
		
	// arithmetic operators
	
		Vector<T, 2> operator + (const Vector<T, 2>& vec) 
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = v[d] + vec.v[d];
			}
			
			return ret;
		}

		Vector<T, 2> operator - (const Vector<T, 2>& vec) 
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = v[d] - vec.v[d];
			}
			
			return ret;
		}
		
		Vector<T, 2> operator * (const T num) 
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = v[d] * num;
			}
			
			return ret;
		}
		
		friend Vector<T, 2> operator * (const T num, const Vector<T, 2>& vec) 
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = num * vec.v[d];
			}
			
			return ret;
		}
		
		Vector<T, 2> operator / (const T num) 
		{
			Vector<T, 2> ret;
			
			for(uint d = 0; d < 2; d++)
			{
				ret.v[d] = v[d] / num;
			}
		
			return ret;
		}
		
	// arithmetic assign operators
	
		void operator += (const Vector<T, 2>& vec) 
		{
			for(uint d = 0; d < 2; d++)
			{
				v[d] += vec.v[d];
			}
		}
	
		void operator -= (const Vector<T, 2>& vec) 
		{
			for(uint d = 0; d < 2; d++)
			{
				v[d] -= vec.v[d];
			}
		}
				
		void operator *= (const T num) 
		{
			for(uint d = 0; d < 2; d++)
			{	
				v[d] *= num;
			}
		}
				
		void operator /= (const T num) 
		{
			for(uint d = 0; d < 2; d++)
			{	
				v[d] /= num;
			}
		}
				
	// vector operations
	
		T dot(const Vector<T, 2>& vec)
		{
			T ret = 0;
			
			for(uint d = 0; d < 2; d++)
			{	
				ret += v[d] * vec.v[d];
			}
			
			return ret;
		}
		
		T cross(const Vector<T, 2>& vec)
		{
			return x * vec.y - y * vec.x;
		}
		
	// properties
	
		double mag(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < 2; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return sqrt(ret);
		}
		
		T mag2(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < 2; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return ret;
		}
		
		double invmag(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < 2; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return 1.0 / sqrt(ret);
		}
		
	// static standards
	
		static Vector<T, 2>& zero(void)
		{
			static Vector<T, 2> ret;
			
			for(uint n = 0; n < 2; n++)
			{
				ret.v[n] = 0;
			}
			
			return ret;
		}
		
		static Vector<T, 2>& one(void)
		{
			static Vector<T, 2> ret;
			
			for(uint n = 0; n < 2; n++)
			{
				ret.v[n] = 1;
			}
			
			return ret;
		}
		
	// output
	
		void PrintFormatted(void)
		{
			std::cout << std::scientific << std::setprecision(3);
			
			for(uint d = 0; d < 2; d++)
			{	
				std::cout << "[" << std::setw(9) << v[d] << "]" << std::endl;
			}
		}
			
		void Print(void)
		{		
			std::cout << "{";
			
			for(uint d = 0; d < 2; d++)
			{	
				std::cout << v[d];
				
				if(d < 1)
				{
					std::cout << ", ";
				}
			}
			
			std::cout << "}" << std::endl;
		}	
		
	// member variables
	
		union 
		{
			T v[2];
			struct{ T x, y; };
		};
};

typedef Vector<real, 2> vec2;

typedef Vector<int,    2> vec2i;
typedef Vector<float,  2> vec2f;
typedef Vector<double, 2> vec2d;

#endif