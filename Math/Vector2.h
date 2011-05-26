//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#include "Types.h"
#include <iostream>

using namespace std;

class Vector2
{
	public:
	
	// constructors

		Vector2(void);		
		Vector2(const real* ent);
		Vector2(real x, real y);
		
	// unary operators
	
		Vector2 operator - (void) const;
		
	// bool operators
	
		bool operator == (const Vector2& vec) const;
		bool operator != (const Vector2& vec) const;
		
	// arithmetic operators
	
		Vector2 operator + (const Vector2& vec) const;
		Vector2 operator - (const Vector2& vec) const;
		Vector2 operator * (const real num) const; 
		Vector2 operator / (const real num) const; 

		friend Vector2 operator * (const real num, const Vector2& vec);
		
	// arithmetic assign operators
	
		void operator += (const Vector2& vec); 	
		void operator -= (const Vector2& vec); 				
		void operator *= (const real num); 
		void operator /= (const real num); 
				
	// vector operations

		Vector2& Normalise(void);
		Vector2 Normalised(void) const;
	
		real Dot(const Vector2& vec) const;
		real Cross(const Vector2& vec) const;
		
	// properties
	
		real Magnitude(void) const;		
		real SquaredMagnitude(void) const;
		real InverseMagnitude(void) const;
		
	// output
			
		friend ostream& operator << (ostream& out, const Vector2& vec);  
		friend istream& operator >> (istream& in, Vector2& vec); 

		
	// member variables
	
		union 
		{
			real v[2];
			struct{ real x, y; };
		};

		static const Vector2 Up(void);
		static const Vector2 Right(void);

		static const Vector2 One(void);
		static const Vector2 Zero(void);
};


typedef Vector2 vec2;