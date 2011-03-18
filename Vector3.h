//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "Types.h"
#include <iostream>

using namespace std;

class Vector3
{
	public:
	
	// constructors

		Vector3(void);		
		Vector3(const real* ent);
		Vector3(real x, real y, real z);
		
	// unary operators
	
		Vector3 operator - (void) const;
		
	// bool operators
	
		bool operator == (const Vector3& vec) const;
		bool operator != (const Vector3& vec) const;
		
	// arithmetic operators
	
		Vector3 operator + (const Vector3& vec) const;
		Vector3 operator - (const Vector3& vec) const;
		Vector3 operator * (const real num) const; 
		Vector3 operator / (const real num) const; 

		friend Vector3 operator * (const real num, const Vector3& vec);
		
	// arithmetic assign operators
	
		void operator += (const Vector3& vec); 	
		void operator -= (const Vector3& vec); 				
		void operator *= (const real num); 
		void operator /= (const real num); 
				
	// vector operations

		Vector3& Normalise(void);
		Vector3 Normalised(void) const;
	
		real Dot(const Vector3& vec) const;
		Vector3 Cross(const Vector3& vec) const;
		
	// properties
	
		real Magnitude(void) const;		
		real SquaredMagnitude(void) const;
		real InverseMagnitude(void) const;
		
	// output
			
		friend ostream& operator << (ostream& out, const Vector3& vec);  
		friend istream& operator >> (istream& in, Vector3& vec); 
		
	// member variables
	
		union 
		{
			real v[3];
			struct{ real x, y, z; };
		};

		static const Vector3 Up(void);
		static const Vector3 Down(void);
		static const Vector3 Left(void);
		static const Vector3 Right(void);
		static const Vector3 Forward(void);
		static const Vector3 Backward(void);

		static const Vector3 One(void);
		static const Vector3 Zero(void);
};

typedef Vector3 vec3;

#endif