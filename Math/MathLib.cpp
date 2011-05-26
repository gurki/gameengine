//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "MathLib.h"

// angles
inline uint triant(real x, real y)
{
	if(x == 0.0f && y == 0.0f)
	{
		return 0;
	}

	real alpha = atan2(y, x);
	
	if(alpha > C_RAD60 && alpha <= C_RAD180)
	{
		return 1;
	}
	else if(alpha > -C_RAD60 && alpha <= C_RAD60)
	{
		return 2;
	}
	else if(alpha > -C_RAD180 && alpha <= -C_RAD60)
	{
		return 3;
	}
	else
	{
		return 1;
	}
}

inline uint quadrant(real x, real y)
{
	if(x == 0.0f && y == 0.0f)
	{
		return 0;
	}
	else if(x > 0 && y >= 0)
	{
		return 1;
	}
	else if(x <= 0 && y > 0)
	{
		return 2;
	}
	else if(x < 0 && y <= 0)
	{
		return 3;
	}
	else if(x >= 0 && y < 0)
	{
		return 4;
	}
}

inline uint hexant(real x, real y)
{
	if(x == 0.0f && y == 0.0f)
	{
		return 0;
	}

	real alpha = atan2(y, x);
	
	if(alpha > C_RAD120 && alpha <= C_RAD180)
	{
		return 1;
	}
	else if(alpha > C_RAD60 && alpha <= C_RAD120)
	{
		return 2;
	}
	else if(alpha > 0.0f && alpha <= C_RAD60)
	{
		return 3;
	}
	else if(alpha > -C_RAD60 && alpha <= 0.0f)
	{
		return 4;
	}
	else if(alpha > -C_RAD120 && alpha <= -C_RAD60)
	{
		return 5;
	}
	else if(alpha > -C_RAD180 && alpha <= -C_RAD120)
	{
		return 6;
	}
	else
	{
		return 1;
	}
}

// prime
bool isPrime(int n)
{
	if((n % 2 == 0 && n != 2) || (n == 1))
	{
		return false;
	}
 
    for (int i = 3; i <= sqrt((double)n); i += 2)
	{
		if (n % i == 0)
		{
			return false;
		}
	}

	return true;
}
