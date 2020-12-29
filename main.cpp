#include "shared.h"

class puncti
{
	private:
		double *p;

	public:
		puncti(double*);
};

class dzvector
{
	// dzvectors should be NO_DATA in length
	private:
		double *x;

	public:
		dzvector();
		dzvector(double*);
		void output_vec();
};

dzvector::dzvector()
{
	x = (double *) malloc(sizeof(double) * NO_DATA);
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



puncti::puncti(double *q)
{
	int i, j;
	
	p = (double *) malloc(NO_DATA * 2 * sizeof(double));
	for (i = 0; i < NO_DATA; i++)
	{
		p[2 * i] = *(q + i * 2);
		p[(2 * i) + 1] = *(q + i * 2 + 1);
	}
}

int main()
{
	int i,j;
	dzvector *f[NO_FUNC];
	double y[NO_DATA];

	// fit these points to c1 + c2x + c3x^2
	// f1 = 1 f2 = x f3 = x^2
	// x indices go from 0 to 3 because there are 4 points.
	// f indices go from 0 to 2 because there are 3 functions.

	double p[NO_DATA][2] = {{1, 5.9}, {2, 17}, {3, 34}, {4, 57.1}};
	
	// number of rows = number of points
	// number of columns = number of dimensions
	
	double e[NO_DATA][NO_FUNC + 1];
	
	double temp[NO_DATA];
	
	//puncti *points;
	//points = new puncti((double *) p);

	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			temp[j] =  pow(p[j][0],i);
		}
		f[i] = new dzvector((double *) temp);
	}
	for(i = 0; i < NO_FUNC; i++)
	{
		cout << "f" << i << " =";
		f[i]->output_vec();
	}
	return 0;
}
