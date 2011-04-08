//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

#include "MathLib.h"
#include "Types.h"

#include <vector>

using namespace std;

class Polynomial
{
	public:

		Polynomial(void);
		Polynomial(const double* a, uint num);

		bool operator == (Polynomial& p);
		bool operator != (Polynomial& p);
		bool operator <= (Polynomial& p);
		bool operator >= (Polynomial& p);
		bool operator < (Polynomial& p);
		bool operator > (Polynomial& p);

		Polynomial operator + (Polynomial& p);
		Polynomial operator - (Polynomial& p);

		int degree(void);
		double solve(double x);
		vector<double> table(double a, double b, double s = 1);

		Polynomial& derive(void);
		Polynomial& integrate(double c = 0);

		Polynomial derived(void);
		Polynomial integrated(double c = 0);

		void print(void);
		void printTable(double a, double b, double s = 1, uint w = 5);

	protected:

		vector<double> v;
};

#endif