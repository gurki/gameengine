//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"

#include <math.h>

#include <iomanip>
#include <iostream>

template <class T, uint D>
class Vector
{
	public:
	
	// constructors
	
		Vector(void)
		{
			for(uint d = 0; d < D; d++)
			{
				v[d] = 0;
			}
		}

		template <class S>
		Vector(const S* ent)
		{
			for(uint d = 0; d < D; d++)
			{
				v[d] = ent[d];
			}
		}
		
	// unary operators
	
		Vector<T, D> operator - (void)
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = -v[d];
			}
			
			return ret;
		}
		
	// bool operators
	
		bool operator == (const Vector<T, D>& vec)
		{
			for(uint d = 0; d < D; d++)
			{
				if(vec.v[d] != v[d])
				{
					return false;
				}
			}
			
			return true;
		}
		
		bool operator != (const Vector<T, D>& vec)
		{
			for(uint d = 0; d < D; d++)
			{
				if(vec.v[d] == v[d])
				{
					return false;
				}
			}
			
			return true;
		}
		
		bool operator < (const Vector<T, D>& vec)
		{
			return mag2() < vec.mag2();
		}
		
		bool operator <= (const Vector<T, D>& vec)
		{
			return mag2() <= vec.mag2();
		}
		
		bool operator > (const Vector<T, D>& vec)
		{
			return mag2() > vec.mag2();
		}
		
		bool operator >= (const Vector<T, D>& vec)
		{
			return mag2() >= vec.mag2();
		}
		
	// arithmetic operators
	
		Vector<T, D> operator + (const Vector<T, D>& vec) 
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = v[d] + vec.v[d];
			}
			
			return ret;
		}

		Vector<T, D> operator - (const Vector<T, D>& vec) 
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = v[d] - vec.v[d];
			}
			
			return ret;
		}
		
		Vector<T, D> operator * (const T num) 
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = v[d] * num;
			}
			
			return ret;
		}
		
		friend Vector<T, D> operator * (const T num, const Vector<T, D>& vec) 
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = num * vec.v[d];
			}
			
			return ret;
		}
		
		Vector<T, D> operator / (const T num) 
		{
			Vector<T, D> ret;
			
			for(uint d = 0; d < D; d++)
			{
				ret.v[d] = v[d] / num;
			}
		
			return ret;
		}
		
	// arithmetic assign operators
	
		void operator += (const Vector<T, D>& vec) 
		{
			for(uint d = 0; d < D; d++)
			{
				v[d] += vec.v[d];
			}
		}
	
		void operator -= (const Vector<T, D>& vec) 
		{
			for(uint d = 0; d < D; d++)
			{
				v[d] -= vec.v[d];
			}
		}
				
		void operator *= (const T num) 
		{
			for(uint d = 0; d < D; d++)
			{	
				v[d] *= num;
			}
		}
				
		void operator /= (const T num) 
		{
			for(uint d = 0; d < D; d++)
			{	
				v[d] /= num;
			}
		}
	
	// vector operations
	
		T dot(const Vector<T, D>& vec)
		{
			T ret = 0;
			
			for(uint d = 0; d < D; d++)
			{	
				ret += v[d] * vec.v[d];
			}
			
			return ret;
		}
		
	// properties
	
		double mag(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < D; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return sqrt(ret);
		}
		
		T mag2(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < D; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return ret;
		}
		
		double invmag(void)
		{
			T ret = 0;
			
			for(uint d = 0; d < D; d++)
			{	
				ret += v[d] * v[d];
			}
			
			return 1.0 / sqrt(ret);
		}
		
	// static standards
	
		static Vector<T, D>& zero(void)
		{
			static Vector<T, D>&  ret;
			
			for(uint n = 0; n < D; n++)
			{
				ret.v[n] = 0;
			}
			
			return ret;
		}
		
		static Vector<T, D>& one(void)
		{
			static Vector<T, D>&  ret;
			
			for(uint n = 0; n < D; n++)
			{
				ret.v[n] = 1;
			}
			
			return ret;
		}
		
	// output
	
		void PrintFormatted(void)
		{
			std::cout << std::scientific << std::setprecision(3);
			
			for(uint d = 0; d < D; d++)
			{	
				std::cout << "[" << std::setw(9) << v[d] << "]" << std::endl;
			}
		}
			
		void Print(void)
		{		
			std::cout << "{";
			
			for(uint d = 0; d < D; d++)
			{	
				std::cout << v[d];
				
				if(d < D -1)
				{
					std::cout << ", ";
				}
			}
			
			std::cout << "}" << std::endl;
		}
	
	// member variables

		T v[D];
};

// typedefs
#define vec(n) Vector<real, n>

#define veci(n) Vector<int,    n>
#define vecb(n) Vector<bool,   n>
#define vecf(n) Vector<float,  n>
#define vecd(n) Vector<double, n>