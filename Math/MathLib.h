//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#pragma once

#ifndef _MATHLIB_H 
#define _MATHLIB_H

#include <cmath>
#include <climits>
#include <cstdlib>

#include "Types.h"

// angles
#define rad(deg) ((deg) * C_PIDIV180)
#define deg(rad) ((rad) * C_180DIVPI)

inline uint triant(real x, real y);
inline uint quadrant(real x, real y);
inline uint hexant(real x, real y);

// min & max
#define min2(a, b) ((a < b) ? a : b)
#define max2(a, b) ((a > b) ? a : b)

#define min3(a, b, c) (min2(min2(a, b), c))
#define max3(a, b, c) (max2(max2(a, b), c))

// remainder
#define mod(a, b) (((a) >= 0) ? (real)(a) - (int)((a) / (b)) * (real)(b) : (1 - (int)((a) / (b))) * (real)(b) + (real)(a))

#define modi(a, b) ((a >= 0) ? (int)   a - (int)(a / b) * (int)   b : (1 - (int)(a / b)) * (int)   b + (int)   a)
#define modf(a, b) ((a >= 0) ? (float) a - (int)(a / b) * (float) b : (1 - (int)(a / b)) * (float) b + (float) a)
#define modd(a, b) ((a >= 0) ? (double)a - (int)(a / b) * (double)b : (1 - (int)(a / b)) * (double)b + (double)a)

#define rem(a) (absr(mod(a, 1.0)))

#define round(a) ((rem(a) < 0.5) ? floor(a) : ceil(a))
#define sign(a) (a >= 0 ? 1 : -1)

#define frac(a) (a - (int)a)

// limiting
#define inf(n, i) (((n) < (i)) ? (i) : (n))
#define sup(n, s) (((n) > (s)) ? (s) : (n))

#define limit(n, i, s) (inf( sup(n, s), i ))

// integers
#define floor(a) ((int)(a))
#define ceil(a) ((int)(a) + 1)

#define absr(a) ((a >= 0) ? a : -a) 

// trigonometry
#define sinr(a) (real)sin(a)
#define cosr(a) (real)cos(a)
#define tanr(a) (real)tan(a)

#define asinr(a) (real)asin(a)
#define acosr(a) (real)acos(a)
#define atanr(a) (real)atan(a)
#define atan2r(a, b) (real)atan2(a, b)

#define cos2(rad, s) ((mod(rad + C_PIDIV2, C_2PI) < C_PI ? 1 : -1) * sqrt(1 - s * s))

// sqrt
#define sqrtr(a) (real)sqrt(a)

// prime
inline bool isPrime(int n);

// limits
#define C_FLOAT_MIN   1.401298464e-45         // smallest representable float value
#define C_FLOAT_MAX   3.402823466e38          // largest representable float value
#define C_FLOAT_EPS   1.1929093e-7            // epsilon
#define C_FLOAT_INF   (std::numeric_limits<float>::infinity())
#define C_FLOAT_NAN   (std::numeric_limits<float>::quiet_NaN())

#define C_DOUBLE_MIN  5e-324                  // smallest representable double value
#define C_DOUBLE_MAX  1.7976931348623157e308  // largest representable double value
#define C_DOUBLE_EPS  2.220446049250313e-16   // epsilon
#define C_DOUBLE_INF  (std::numeric_limits<double>::infinity())
#define C_DOUBLE_NAN  (std::numeric_limits<double>::quiet_NaN())

#ifdef DOUBLE_PRECISSION
	#define C_MIN C_DOUBLE_MIN
	#define C_MAX C_DOUBLE_MAX
	#define C_EPS C_DOUBLE_EPS
	#define C_INF C_DOUBLE_INF
	#define C_NAN C_DOUBLE_NAN
#else
	#define C_MIN C_FLOAT_MIN
	#define C_MAX C_FLOAT_MAX
	#define C_EPS C_FLOAT_EPS
	#define C_INF C_FLOAT_INF
	#define C_NAN C_FLOAT_NAN
#endif

// constants
#define C_1DIV3      (real)0.333333333333333333333 // 1/3
#define C_2DIV3      (real)0.666666666666666666667 // 2/3
#define C_1DIV6      (real)0.166666666666666666667 // 1/6

#define C_E          (real)2.71828182845904523536  // e
#define C_PI         (real)3.14159265358979323846  // pi
#define C_SQRT2      (real)1.41421356237309504880  // sqrt(2)
#define C_SQRT3      (real)1.73205080756887729353  // sqrt(3)

#define C_2PI        (real)6.28318530717958647692  // 2*pi

#define C_EDIV4      (real)0.679570457114761308840 // e/4
#define C_PIDIV4     (real)0.785398163397448309616 // pi/4
#define C_SQRT2DIV4  (real)0.353553390593273762200 // sqrt(2)/4

#define C_EDIV2      (real)1.35914091422952261768  // e/2
#define C_PIDIV2     (real)1.57079632679489661923  // pi/2
#define C_SQRT2DIV2  (real)0.707106781186547524400 // sqrt(2)/2
#define C_SQRT3DIV2  (real)0.866025403778443864676 // sqrt(3)/2

#define C_SQRT3DIV3  (real)0.577350269189625764509 // sqrt(3)/3

#define C_1DIVE      (real)0.367879441171442321595 // 1/e
#define C_1DIVPI     (real)0.318309886183790671538 // 1/pi
#define C_1DIVSQRT2  (real)0.707106781186547524401 // 1/sqrt(2)

#define C_2DIVE      (real)0.735758882342884643191 // 2/e
#define C_2DIVPI     (real)0.636619772367581343076 // 2/pi
#define C_2DIVSQRT2  (real)1.41421356237309504880  // 2/sqrt(2) = sqrt(2)

#define C_LOG2E      (real)1.44269504088896340736  // log2(e)
#define C_LOG10E     (real)0.434294481903251827651 // log10(e)

#define C_LN2        (real)0.693147180559945309417 // ln(2)
#define C_LN10       (real)2.30258509299404568402  // ln(10)

#define C_PIDIV180   (real)0.017453292519943295769 // pi/180
#define C_180DIVPI   (real)57.2957795130823208769  // 180/pi

#define C_RAD0       (real)0.000000000000000000000 // 0°
#define C_RAD30      (real)0.523598775598298873077 // 30°
#define C_RAD45      (real)0.785398163397448309616 // 45°
#define C_RAD60      (real)1.047197551196597746154 // 60°
#define C_RAD90      C_PIDIV2                      // 90°
#define C_RAD120     (real)2.094395102393195492308 // 120°
#define C_RAD135     (real)2.356194490192344928847 // 135°
#define C_RAD180     C_PI                          // 180°

// efficient algorithms

/* 
	sincos functions

	standard c-library: slow tempo, reference
	tangens conversion: mid tempo, temp variable costs, precision in ED
	trigonom. identity: fast tempo, sign costs, precision in EF

	template <class T>
	inline void clibrary(const T angle, T& s, T& c) 
	{
		s = sin(angle);
		c = cos(angle);
	}

	template <class T>
	inline void tangent(const T angle, T& s, T& c) 
	{
		double z = tan(angle * 0.5);

		s = 2 * z / (1 + z * z);
		c = (1 - z * z) / (1 + z * z);
	}

	template <class T>
	inline void trigid(const T angle, T& s, T& c) 
	{
		s = sin(angle);
		c = (mod(angle + C_PIDIV2, C_2PI) < C_PI ? 1 : -1) * sqrt(1 - s * s);
	}

	problem with all: function call takes too long!!
*/

#endif