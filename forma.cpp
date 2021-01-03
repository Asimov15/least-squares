#include "shared.h"

forma::forma()
{
	// constructor
	int i;
	
	// x is a matrix holding the coefficients of the equations. The last column holds the constants
	x = (long double *) malloc((pow(NO_FUNC,2) + NO_FUNC) * sizeof(long double));
	
	for(i = 0; i < (pow(NO_FUNC,2) + NO_FUNC); i++)
	{
		x[i] = 0;
	}
}

forma::forma(long double **m)
{
	// this constructor takes the address of a 2D array so that the matrix can be conviently initialized.
	int i, j;
	
	x = (long double *) malloc(NO_FUNC * (NO_FUNC + 1) * sizeof(long double));
	for (j = 0; j < NO_FUNC; j++)
	{
		for (i = 0; i < NO_FUNC + 1; i++)
		{
			x[j*(NO_FUNC + 1) + i] = *(*(m + j) + i);  //[row][col] j = row number; i = col number 
		}
	}
}

forma::~forma()
{
	// destructor
	delete[] x;
}

long double forma::get(int i, int j)
{
	// return an element
	assert(i >= 0 && i < (NO_FUNC +1));
	assert(j >= 0 && j < NO_FUNC);
	return x[j*(NO_FUNC + 1) + i]; // i = column number; j = row number
}

void forma::put(int i, int j, long double value)
{
	// set an elelment
	assert(i >= 0 && i < (NO_FUNC + 1));
	assert(j >= 0 && j < NO_FUNC);
	x[j*(NO_FUNC + 1) + i] = value;
}

void forma::initialise()
{

}

void forma::eliminate()
{
	// forward elemination phase
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
