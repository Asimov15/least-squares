#include "shared.h"

int main()
{
	int i,j;
	dzvector *f[NO_FUNC];
	dzvector *y;
	forma *expression;
	endodatio *b;

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
	cout.precision(17);
	for(i = 0; i < NO_FUNC; i++)
	{
		equation[i] = new long double[NO_FUNC + 1];
	}
	
	// output column headers
	cout << "Column Headers" << endl;
	
	for(i = 0; i < 2; i++)
	{
		cout << test.at(i).first << ",";
	}

	cout << endl;

	// output data points
	cout << "Data Points" << endl;
	for(i = 0; i < NO_DATA; i++)
	{
		t2[i] = test.at(1).second.at(i);
		cout << test.at(0).second.at(i) << "," << t2[i] << endl;
	}
	
	cout << endl;
	
	y = new dzvector((long double *) t2);
	
	cout << "y vector" << endl;
	
	y->output_vec();
	
	cout << "f vectors" << endl;
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			t1[j] = pow(j, i);
		}
		f[i] = new dzvector((long double *) t1);
		f[i]->output_vec();
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

	b = new endodatio();
	cout << "The equations:" << endl;
	expression->output();
	expression->eliminate();
	expression->substitute(b);
	cout << "coefficients:" << endl;
	b->output();
	b->save_coefficents();
	expression->test_solution(b);
	b->predict(NO_DATA + 1);
	b->save_coefficents();
	cout << "Actual: " << test.at(1).second.at(NO_DATA) << endl;
	return 0;
}
