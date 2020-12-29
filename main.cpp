#include "shared.h"

int main()
{
	int i,j;
	dzvector *f[NO_FUNC];
	dzvector *y;
	forma *expression;
	endodatio *b;

	// fit these points to c1 + c2x + c3x^2
	// f1 = 1 f2 = x f3 = x^2
	// x indices go from 0 to 3 because there are 4 points.
	// f indices go from 0 to 2 because there are 3 functions.

	double p[NO_DATA][2] = {{1, 5.9}, {2, 17}, {3, 34}, {4, 57.1}};
	
	// number of rows = number of points
	// number of columns = number of dimensions
	
	double **equation;
	equation = new double *[NO_FUNC];

	for(i = 0; i < NO_FUNC; i++)
	{
		equation[i] = new double[NO_FUNC + 1];
	}
	
	double t1[NO_DATA];
	double t2[NO_DATA];
	
	for(i = 0; i < NO_DATA; i++)
	{
		t2[i] = p[i][1];
	}
	
	y = new dzvector((double *) t2);
	
	// y->output_vec();
	
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
		for(j = 0; j < NO_FUNC; j++)
		{
			equation[i][j] = f[i]->dot_product(f[j]);
		}
		equation[i][NO_FUNC] = f[i]->dot_product(y);
	}

	expression = new forma((double **) equation);
	//expression->output_matrix();
	
	b = new endodatio();

	expression->eliminate();
	expression->substitute(b);

	b->output();
	expression->test_solution(b);
	
	return 0;
}
