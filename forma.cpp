#include "shared.h"

forma::forma()
{
	// constructor
	int i;
	
	// aequare is a matrix holding the coefficients of the equations. The last column holds the constants
	aequare = (long double *) malloc((pow(NO_FUNC,2) + NO_FUNC) * sizeof(long double));
	
	for(i = 0; i < (pow(NO_FUNC,2) + NO_FUNC); i++)
	{
		aequare[i] = 0;
	}
}

forma::forma(long double **m)
{
	// this constructor takes the address of a 2D array so that the matrix can be conviently initialized.
	int i, j;
	
	aequare = (long double *) malloc(NO_FUNC * (NO_FUNC + 1) * sizeof(long double));
	for (j = 0; j < NO_FUNC; j++)
	{
		for (i = 0; i < NO_FUNC + 1; i++)
		{
			aequare[j*(NO_FUNC + 1) + i] = *(*(m + j) + i);  //[row][col] j = row number; i = col number 
		}
	}
}

forma::~forma()
{
	// destructor
	delete[] aequare;
}

long double forma::get(int i, int j)
{
	// return an element
	assert(i >= 0 && i < (NO_FUNC +1));
	assert(j >= 0 && j < NO_FUNC);
	return aequare[j*(NO_FUNC + 1) + i]; // i = column number; j = row number
}

void forma::put(int i, int j, long double value)
{
	// set an elelment
	assert(i >= 0 && i < (NO_FUNC + 1));
	assert(j >= 0 && j < NO_FUNC);
	aequare[j*(NO_FUNC + 1) + i] = value;
}

void forma::initialize()
{
	int i,j;
	dzvector *f[NO_FUNC];
	dzvector *y;
	long double t1[NO_DATA];
	long double t2[NO_DATA];
	
	std::vector<std::pair<std::string, std::vector<long double>>> csv_file = read_csv("copper4.csv");
	
	// fit these points to c1 + c2x + c3x^2 + ...
	// f1 = 1 f2 = x f3 = x^2 ...

	// number of rows = number of points
	// number of columns = number of dimensions
	
	cout.precision(17);
	// output column headers
	//cout << "Column Headers" << endl;
	
	for(i = 0; i < 2; i++)
	{
		//cout << csv_file.at(i).first << ",";
	}
	
	cout << endl;

	// output data points
	//cout << "Data Points" << endl;
	for(i = 0; i < NO_DATA; i++)
	{
		t2[i] = csv_file.at(1).second.at(i);
		//cout << csv_file.at(0).second.at(i) << "," << t2[i] << endl;
	}
	
	cout << endl;
	
	y = new dzvector((long double *) t2);
	
	//cout << "y vector" << endl;
	
	//y->output_vec();
	
	//cout << "f vectors" << endl;
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_DATA; j++)
		{
			t1[j] = pow(j, i);
		}
		f[i] = new dzvector((long double *) t1);
		//f[i]->output_vec();
	}
	
	for(i = 0; i < NO_FUNC; i++)
	{
		for(j = 0; j < NO_FUNC; j++)
		{
			put(j,i, f[i]->dot_product(f[j]));
		}
		put(j,i, f[i]->dot_product(y));
	}
	for(i = 0; i < NO_FUNC; i++)
	{
		delete f[i];
	}

	delete y;
}

void forma::eliminate()
{
	// forward elimination phase
	int i, j, k, max;
	long double t;
	for (i = 0; i < NO_FUNC; i++)
	{
		// find max row
		max = i;
		for (j = i + 1; j < NO_FUNC; j++)
		{
			if (abs(get(i,j)) > abs(get(i,max))) 
			{
				max = j;
			}
		}
		
		// move max row to top
		for (k = i; k < (NO_FUNC + 1); k++)
		{
			t = get(k,i);
			put(k,i, get(k,max));
			put(k, max, t);
		}
		
		for (j = i + 1; j < NO_FUNC; j++)
		{
			for (k = NO_FUNC; k >= i; k--)
			{
				put(k,j, get(k,j) - get(k,i) * get(i,j) / get(i,i));
			}
		}
	}
}

void forma::substitute(endodatio *c)
{
	// backward substitution phase
	int j, k;
	long double t;
	for ( j = NO_FUNC - 1; j >= 0; j--)
	{
		t = 0.0;
		for ( k = j + 1; k < NO_FUNC; k++)
		{
			t += get(k,j) * c->get(k);
		}
		c->put(j, (get(NO_FUNC,j) - t) / get(j,j));
	}
}

void forma::output_matrix()
{
	int i,j;
	long double val;
	
	cout << endl;
	for (j = 0; j < NO_FUNC; j++)
	{
		cout << "[ ";
		for (i = 0; i < NO_FUNC + 1; i++)
		{
			val = get(i,j);
			cout << val << " ";
		}
		cout << "]" << endl;
	}
	cout << "_______________________" << endl;
}

void forma::test_solution(endodatio *c)
{
	long double result;
	cout.precision(17);
	int i;
	
	result = 0.0;
	for (i = 0; i < NO_FUNC; i++)
	{
		result += get(i,0) * c->get(i);
	}
	
	if ((abs(result - get(NO_FUNC,0)) * 100) / result < 0.1)
	{
		cout << "success" << endl;
		cout << result << endl;
		cout << get(NO_FUNC, 0) << endl;
	}
	else
	{
		cout << "failed" << endl;
		cout << result << endl;
		cout << get(NO_FUNC, 0) << endl;
	}
}

void forma::output()
{
	int i,j;
	for (j = 0; j < NO_FUNC; j++)
	{
		for (i = 0; i < NO_FUNC + 1; i++)
		{
			cout << get(i,j) << ",";
		}
		cout << endl;
	}
}
