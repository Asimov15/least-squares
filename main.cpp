#include "shared.h"

class dzvector
{
	// dzvectors should be NO_DATA in length
	private:
		double *x;

	public:
		dzvector();
		dzvector(double*);
		void output_vec();
		double get(int i);
		double dot_product(dzvector* vec);
};

dzvector::dzvector()
{
	int i;
	x = (double *) malloc(sizeof(double) * NO_DATA);
	for (i = 0; i < NO_DATA; i++) 
	{
		x[i] = 0;
	}
}

dzvector::dzvector(double *y)
{
	int i;
	x = (double *) malloc(sizeof(double) * NO_DATA);
	for (i = 0; i < NO_DATA; i++)
	{
		x[i] = y[i];
	}
}

void dzvector::output_vec()
{
	int j;
	for(j = 0; j < NO_DATA-1; j++)
	{
		cout << x[j] << ", ";
	}
	cout << x[NO_DATA - 1] << endl;
}

double dzvector::get(int i)
{
	return x[i];
}

double dzvector::dot_product(dzvector* vec)
{
	double r;
	int i;
	r = 0;
	for(i = 0; i < NO_DATA; i++)
	{
		r += x[i]*vec->get(i);
	}
	return r;
}

int main()
{
	int i,j;
	dzvector *f[NO_FUNC];
	dzvector *y;

	// fit these points to c1 + c2x + c3x^2
	// f1 = 1 f2 = x f3 = x^2
	// x indices go from 0 to 3 because there are 4 points.
	// f indices go from 0 to 2 because there are 3 functions.

	double p[NO_DATA][2] = {{1, 5.9}, {2, 17}, {3, 34}, {4, 57.1}};
	
	// number of rows = number of points
	// number of columns = number of dimensions
	
	double e[NO_FUNC][NO_DATA + 1];
	
	double t1[NO_DATA];
	double t2[NO_DATA];
	
	y = new dzvector();
	
	for(i = 0; i < NO_DATA; i++)
	{
		t2[i] = p[i][1];
	}
	
	y = new dzvector((double *) t2);
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			t1[j] =  pow(p[j][0],i);
		}
		f[i] = new dzvector((double *) t1);
	}
	
	
	for(i = 0; i < NO_FUNC; i++)
	{
		cout << "f" << i << " =";
		f[i]->output_vec();
	}
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			e[i][j] = f[i]->dot_product(f[j]);
		}
		e[i][NO_DATA] = f[i]->dot_product(y);
	}
	return 0;
}
