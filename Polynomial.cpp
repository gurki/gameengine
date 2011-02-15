//***************************************************************************//
//                                                                           //
//                          Gurki Media Productions                          //
//                             (C) Tobias Gurdan                             //
//                                                                           //
//***************************************************************************//

#include "Polynomial.h"

#include <iostream>
#include <iomanip>

Polynomial::Polynomial(void) 
{ 
	v.push_back(0); 
}

Polynomial::Polynomial(const double* a, uint num)
{
	for(uint n = 0; n < num; n++)
	{
		v.push_back(a[n]);
	}
}

bool Polynomial::operator == (Polynomial& p)
{
	if(degree() != p.degree())
	{
		return false;
	}

	for(int n = 0; n < degree(); n++)
	{
		if(p.v[n] != v[n])
		{
			return false;
		}
	}

	return true;
}

bool Polynomial::operator != (Polynomial& p)
{
	if(degree() != p.degree())
	{
		return true;
	}

	for(int n = 0; n < degree(); n++)
	{
		if(p.v[n] != v[n])
		{
			return true;
		}
	}

	return false;
}

bool Polynomial::operator <= (Polynomial& p)
{
	return degree() <= p.degree();
}

bool Polynomial::operator >= (Polynomial& p)
{
	return degree() >= p.degree();
}

bool Polynomial::operator < (Polynomial& p)
{
	return degree() < p.degree();
}

bool Polynomial::operator > (Polynomial& p)
{
	return degree() > p.degree();
}

Polynomial Polynomial::operator + (Polynomial& p)
{
	Polynomial ret = max2(*this, p);
	Polynomial min = min2(*this, p);

	for(int n = 0; n < min.degree(); n++)
	{
		ret.v[n] += min.v[n];
	}

	return ret;
}

Polynomial Polynomial::operator - (Polynomial& p)
{
	Polynomial ret = max2(*this, p);
	Polynomial min = min2(*this, p);

	for(int n = 0; n < min.degree(); n++)
	{
		ret.v[n] -= min.v[n];
	}

	return ret;
}

double Polynomial::solve(double x) 
{
	double ret = 0;

	for(uint n = 0; n < v.size(); n++)
	{
		ret += v[n] * pow(x, (int)n);		
	}

	return ret;
}

vector<double> Polynomial::table(double a, double b, double s)
{
	double d = abs(b - a);

	vector<double> v;

	for(int n = 0; n <= d / s; n++)
	{
		v.push_back(solve(a + n * s));
	}

	return v;
}

Polynomial& Polynomial::derive(void)
{
	for(uint n = 0; n < v.size() - 1; n++)
	{
		v[n] = v[n+1] * (double)(n+1);		
	}

	v.pop_back();

	return *this;
}

Polynomial Polynomial::derived(void)
{
	Polynomial p = *this;

	p.derive();

	return p;
}

Polynomial& Polynomial::integrate(double c) 
{
	v.push_back(0);

	for(int n = v.size() - 1; n > 0; n--)
	{
		v[n] = v[n-1] / (double)(n);		
	}

	v[0] = c;

	return *this;
}

Polynomial Polynomial::integrated(double c)
{
	Polynomial p = *this;

	p.integrate(c);

	return p;
}

int Polynomial::degree(void)
{
	return (int)v.size() - 1;
}

void Polynomial::print(void)
{
	cout << defaultfloat;
	cout << "f(x) = ";

	// alle durchgehn, größte potenz zuerst
	for(int n = v.size() - 1; n >= 0; n--)
	{
		// is es sowas wie 0 * x^3
		if(v[n] != 0)
		{
			// is es sowas wie 3 * x^2
			if(v[n] >= 0)
			{
				// kein + vor dem ersten glied
				if(n != v.size() - 1)
				{
					cout << " + ";
				}
			}
			// oder eher -3 * x^2
			else 
			{
				// keine leerzeichen beim minus vorm ersten glied
				if(n == v.size() - 1)
				{
					cout << "-";
				}
				// sonst schon
				else
				{
					cout << " - ";
				}
			}
				
			// keine einsen schreiben, es sei denn, es ist das letzte glied
			if(abs(v[n]) != 1 || n == 0) 
			{
				cout << abs(v[n]);
			}

			// das letzte x nich schreiben
			if(n > 0) 
			{
				cout << "x";

				// und die potenz nur, wenn sie nicht eins is
				if(n != 1) 
				{
					cout << "^" << n;
				}
			}
		}
	}

	// neue zeile
	cout << endl << endl;
}

void Polynomial::printTable(double a, double b, double s, uint w)
{
	double d = abs(b - a);

	cout << fixed << setprecision(2);

	for(int n = 0; n <= d / s; n++)
	{
		cout << "f(" << a + n * s << ") = " << setw(w) << right << solve(a + n * s) << endl;
	}

	cout << endl;
}