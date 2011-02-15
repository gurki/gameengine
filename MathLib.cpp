//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "MathLib.h"

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
