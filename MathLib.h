//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _MATHLIB_H
#define _MATHLIB_H

#include <math.h>
#include "Types.h"

// angles
#define rad(deg) deg * C_PIDIV180
#define deg(rad) rad * C_180DIVPI

// min & max
template <class T> inline T min2(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max2(T a, T b) { return (a > b) ? a : b; }

template <class T> inline T min3(T a, T b, T c) { return min2(min2(a, b), c); }
template <class T> inline T max3(T a, T b, T c) { return max2(max2(a, b), c); }

// remainder
#define mod(a, b) ((a >= 0) ? (real)a - (int)(a / b) * (real)b : (1 - (int)(a / b)) * (real)b + (real)a)

#define modi(a, b) ((a >= 0) ? (int)   a - (int)(a / b) * (int)   b : (1 - (int)(a / b)) * (int)   b + (int)   a)
#define modf(a, b) ((a >= 0) ? (float) a - (int)(a / b) * (float) b : (1 - (int)(a / b)) * (float) b + (float) a)
#define modd(a, b) ((a >= 0) ? (double)a - (int)(a / b) * (double)b : (1 - (int)(a / b)) * (double)b + (double)a)

#define rem(a) (absr(mod(a, 1.0)))

#define round(a) ((rem(a) < 0.5) ? floor(a) : ceil(a))

// limiting
#define stick(n, inf) ((n < inf) ? inf : n)
#define clamp(n, sup) ((n > sup) ? sup : n)

#define limit(n, inf, sup) (stick( clamp(n, sup), inf ))

// integers
#define floor(a) (int)(a)
#define ceil(a) (int)(a) + 1

#define absr(a) ((a >= 0) ? a : -a) 

// trigonometry
#define sinr(a) (real)sin(a)
#define cosr(a) (real)cos(a)
#define tanr(a) (real)tan(a)

#define asinr(a) (real)asin(a)
#define acosr(a) (real)acos(a)
#define atanr(a) (real)atan(a)
#define atan2r(a, b) (real)atan2(a, b)

// sqrt
#define sqrtr(a) (real)sqrt(a)

// prime
inline bool isPrime(int n);

// constants
#define C_EPSILON    (real)0.00001                 // smallest possible float value different from 1.0

#define C_1DIV3      (real)0.333333333333333333333 // 1/3
#define C_2DIV3      (real)0.666666666666666666667 // 2/3
#define C_1DIV6      (real)0.166666666666666666667 // 1/6

#define C_E          (real)2.71828182845904523536  // e
#define C_PI         (real)3.14159265358979323846  // pi
#define C_SQRT2      (real)1.41421356237309504880  // sqrt(2)

#define C_EDIV4      (real)0.679570457114761308840 // e/4
#define C_PIDIV4     (real)0.785398163397448309616 // pi/4
#define C_SQRT2DIV4  (real)0.353553390593273762200 // sqrt(2)/4

#define C_EDIV2      (real)1.35914091422952261768  // e/2
#define C_PIDIV2     (real)1.57079632679489661923  // pi/2
#define C_SQRT2DIV2  (real)0.707106781186547524400 // sqrt(2)/2

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

#endif