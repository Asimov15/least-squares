#include "shared.h"

dzvector::dzvector()
{
	int i;
	x = (long double *) malloc(sizeof(long double) * NO_DATA);
	for (i = 0; i < NO_DATA; i++) 
	{
		x[i] = 0;
	}
}

dzvector::dzvector(long double *y)
{
	int i;
	x = (long double *) malloc(sizeof(long double) * NO_DATA);
	for (i = 0; i < NO_DATA; i++)
	{
		x[i] = y[i];
	}
}

void dzvector::output_vec()
{
	int j;
	for(j = 0; j < NO_DATA - 1; j++)
	{
		cout << x[j] << ", ";
	}
	cout << x[NO_DATA - 1] << endl;
}

long double dzvector::get(int i)
{
	return x[i];
}

long double dzvector::dot_product(dzvector* vec)
{
	long double r;
	int i;
	r = 0;
	for(i = 0; i < NO_DATA; i++)
	{
		r += x[i]*vec->get(i);
	}
	return r;
}
