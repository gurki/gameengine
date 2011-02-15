//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _MATRIX_H
#define _MATRIX_H

#include "Types.h"
#include "Vector.h"

#include <iostream>
#include <iomanip>

template <class T, uint R, uint C>
class Matrix
{
	public:

	// constructors
	
		Matrix(void)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] = 0;
				}
			}
		}
		
		template <class S>
		Matrix(const S* ent, uint n = R * C)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					if(r * C + c < n)
					{
						v[r][c] = ent[r * C + c];
					}
					else
					{
						v[r][c] = 0;
					}

				}
			}
		}
		
		template <class S>
		Matrix(const S* ent[], uint m = R, uint n = C)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					if(r < m - 1 && c < n - 1)
					{
						v[r][c] = ent[r][c];
					}
					else
					{
						v[r][c] = 0;
					}
				}
			}
		}
		
		template <class S>
		Matrix(const Matrix<S, R, C>& mat)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] = mat.v[r][c];
				}
			}
		}
		
		template <class S, uint D>
		Matrix(const Vector<S, D>& vec)
		{			
			for(uint c = 0; c < C; c++)
			{
				if(c < D)
				{
					v[0][c] = vec.v[c];
				}
				else
				{
					v[0][c] = 0;
				}
			}
			
			for(uint r = 1; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] = 0;
				}
			}
		}
		
    // arithmetic number operations
	
		Matrix<T, R, C> operator * (const T num)
		{
			Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = v[r][c] * num;
				}
			}
			
			return ret;
		}

		friend Matrix<T, R, C> operator * (const T num, const Matrix<T, R, C>& mat)
		{
			Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = num * mat.v[r][c];
				}
			}
			
			return ret;
		}

		Matrix<T, R, C> operator / (const T num)
		{
			Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = v[r][c] / num;
				}
			}
			
			return ret;
		}
		
	// arithmetic number assign operations
	
		void operator *= (const T num)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] *= num;
				}
			}
		}
		
		void operator /= (const T num)
		{
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] /= num;
				}
			}
		}
		
	// arithmetic matrix operations
	
		Matrix<T, R, C> operator + (const Matrix<T, R, C>& mat)
		{
			Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = v[r][c] + mat.v[r][c];
				}
			}
			
			return ret;
		}
		
		Matrix<T, R, C> operator - (const Matrix<T, R, C>& mat)
		{
			Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = v[r][c] - mat.v[r][c];
				}
			}
			
			return ret;
		}
		
		template <uint C2>
		Matrix<T, R, C2> operator * (const Matrix<T, C, C2>& mat)
		{			
			Matrix<T, R, C2> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C2; c++)
				{
					for(uint i = 0; i < C; i++)
					{
						ret.v[r][c] += v[r][i] * mat.v[i][c];
					}
				}
			}
			
			return ret;
		}
		
	// arithmetic matrix assign operations
	
		void operator += (const Matrix<T, R, C>& mat)
		{			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] += mat.v[r][c];
				}
			}
		}
		
		void operator -= (const Matrix<T, R, C>& mat)
		{			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					v[r][c] -= mat.v[r][c];
				}
			}
		}
		
	// matrix <-> vector operations

		Vector<T, R> operator * (const Vector<T, C>& vec)
		{
			Vector<T, R> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r] += v[r][c] * vec.v[c];
				}
			}
			
			return ret;
		}
		
		friend Vector<T, C> operator * (const Vector<T, R>& vec, const Matrix<T, R, C>& mat)
		{
			Vector<T, C> ret;
			
			for(uint c = 0; c < C; c++)
			{
				for(uint r = 0; r < R; r++)
				{
					ret.v[c] += mat.v[r][c] * vec.v[r];
				}
			}
			
			return ret;
		}	
		
	// matrix operations
		
		T det(void)
		{
			if(R != C) 
			{
				return -1;
			}
			
			if(R == 2)
			{
				return v[0][0] * v[1][1] - v[0][1] * v[1][0];
			}
			
			if(R == 3)
			{
				return v[0][0] * v[1][1] * v[2][2] +
				       v[0][1] * v[1][2] * v[2][0] + 
					   v[0][2] * v[1][3] * v[2][1] -
					   v[0][2] * v[1][1] * v[2][0] -
					   v[0][1] * v[1][0] * v[2][2] -
					   v[0][0] * v[1][2] * v[2][1];
			}
			
			T d = 0;
			
			for(uint c = 0; c < C; c++)
			{
				T p = 1;
				T n = 1;
				
				for(uint r = 0; r < R; r++)
				{
					uint index = fmodf(c + r, C);
					
					p *= v[r][index];
					n *= v[r][C - 1 - index];
				}
				
				d += p;
				d -= n;
			}
			
			return d;
		}
		
		Matrix<T, R, C> transpose(void)
		{
			Matrix<T, C, R> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = v[c][r];
				}
			}
			
			return ret;
		}
		
	// static standards
	
		static Matrix<T, R, C>& id(void)
		{
			static Matrix<T, R, C> ret;
			
			for(uint n = 0; n < ((R < C) ? R : C); n++)
			{
				ret.v[n][n] = 1;
			}
			
			return ret;
		}
		
		static Matrix<T, R, C>& one(void)
		{
			static Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = 1;
				}
			}
			
			return ret;
		}
		
		static Matrix<T, R, C>& zero(void)
		{
			static Matrix<T, R, C> ret;
			
			for(uint r = 0; r < R; r++)
			{
				for(uint c = 0; c < C; c++)
				{
					ret.v[r][c] = 0;
				}
			}
			
			return ret;
		}
		                                                                       		
	// output
		
		void PrintDetailed(uint w = 9)
		{	
			std::cout << std::setprecision(2);
			
			std::cout << R << "x" << C << ", Det: " << det() << std::endl;
			std::cout << std::endl;
			
			for(uint r = 0; r < R; r++)
			{
				std::cout << "[";
				
				for(uint c = 0; c < C; c++)
				{
					std::cout << std::setw(w) << v[r][c];
					
					if(c != C - 1)
					{
						std::cout << ", ";
					}
				}
				
				std::cout << "]" << std::endl;
			}
			
			std::cout << std::endl;
		}
		
		void Print(void)
		{		
			std::cout << "{";
			
			for(uint r = 0; r < R; r++)
			{
				std::cout << "{";
				
				for(uint c = 0; c < C; c++)
				{
					std::cout <<  v[r][c];
					
					if(c != C - 1)
					{
						std::cout << ",";
					}
				}
				
				std::cout << "}";
				
				if(r != R - 1)
				{
					std::cout << ", ";
				}
			}
			
			std::cout << "}" << std::endl;
			std::cout << std::endl;
		}

	// member variables

		T v[R][C];
};

// matrix typedefs
#define mat(r, c) Matrix<real, r, c>
#define mati(r, c) Matrix<int,    r, c>
#define matb(r, c) Matrix<bool,   r, c>
#define matf(r, c) Matrix<float,  r, c>
#define matd(r, c) Matrix<double, r, c>

typedef Matrix<real, 2, 2> mat2;
typedef Matrix<int,    2, 2> mat2i;
typedef Matrix<bool,   2, 2> mat2b;
typedef Matrix<float,  2, 2> mat2f;
typedef Matrix<double, 2, 2> mat2d;

typedef Matrix<real, 3, 3> mat3;
typedef Matrix<int,    3, 3> mat3i;
typedef Matrix<bool,   3, 3> mat3b;
typedef Matrix<float,  3, 3> mat3f;
typedef Matrix<double, 3, 3> mat3d;

typedef Matrix<real, 4, 4> mat4;
typedef Matrix<int,    4, 4> mat4i;
typedef Matrix<bool,   4, 4> mat4b;
typedef Matrix<float,  4, 4> mat4f;
typedef Matrix<double, 4, 4> mat4d;

#endif