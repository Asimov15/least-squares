#include "shared.h"

int main()
{
	int i,j;
	dzvector *f[NO_FUNC];
	dzvector *y;
	forma *expression;
	endodatio *b;
	long double p[NO_DATA][2] = { {1, 5.99}, {2, 17}, {3, 34}, {4, 57.1} };
	long double **equation;
	long double t1[NO_DATA];
	long double t2[NO_DATA];
	std::vector<std::pair<std::string, std::vector<long double>>> test = read_csv("copper3.csv");
	
	// fit these points to c1 + c2x + c3x^2
	// f1 = 1 f2 = x f3 = x^2
	// x indices go from 0 to 3 because there are 4 points.
	// f indices go from 0 to 2 because there are 3 functions.

	// number of rows = number of points
	// number of columns = number of dimensions

	equation = new long double *[NO_FUNC];

	for(i = 0; i < NO_FUNC; i++)
	{
		equation[i] = new long double[NO_FUNC + 1];
	}
	
	for(i = 0; i < 2; i++)
	{
		cout << test.at(i).first << "," << endl;
	
	}
	
	for(i = 0; i < 2; i++)
	{
		cout << test.at(i).second.at(0) << "," << endl;
	
	}
	
	//return 0;
	
	for(i = 0; i < NO_DATA; i++)
	{
		//t2[i] = p[i][1];
		t2[i] = test.at(1).second.at(i);
		cout << t2[i] << endl;
	}
	
	y = new dzvector((long double *) t2);
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			//t1[j] =  pow(p[j][0], i);
			t1[j] = pow(j, i);
		}
		f[i] = new dzvector((long double *) t1);
	}
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_FUNC; j++)
		{
			equation[i][j] = f[i]->dot_product(f[j]);
		}
		equation[i][NO_FUNC] = f[i]->dot_product(y);
	}

	expression = new forma((long double **) equation);
	//expression->output_matrix();
	
	b = new endodatio();

	expression->eliminate();
	expression->substitute(b);

	b->output();
	expression->test_solution(b);
	b->predict(NO_DATA + 1);
	
	return 0;
}
