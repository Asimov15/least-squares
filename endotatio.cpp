#include "shared.h"

// class to hold the solution 
endodatio::endodatio()
{
	// constructor
	int i;
	solution = (long double *) malloc(NO_FUNC * sizeof(long double));
	for(i = 0; i < NO_FUNC; i++)
	{
		solution[i] = 0;
	}
}

long double endodatio::get(int i)
{
	assert(i >= 0 && i < NO_FUNC);
	return solution[i];
}

void endodatio::put(int i, long double value)
{
	assert(i >= 0 && i < NO_FUNC);
	solution[i] = value;
}

void endodatio::output()
{
	// display the solution
	int i;
	for (i = 0; i < NO_FUNC - 1; i++)
	{
		cout << solution[i] << ",";
	}

	cout << solution[NO_FUNC - 1] << endl;
}

void endodatio::predict(int next)
{
	int i;
	long double result;
	result = 0;
	for (i = 0; i < NO_FUNC; i++)
	{
		result += solution[i]*pow(next,i);
	}
	cout << "Prediction: " << result << endl;
	return;
}

endodatio::~endodatio()
{
	// destructor
	delete[] solution;
}
