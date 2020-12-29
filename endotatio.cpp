#include "shared.h"

// class to hold the solution 
endodatio::endodatio()
{
	// constructor
	int i;
	solution = (double *) malloc(NO_FUNC * sizeof(double));
	for(i = 0; i < NO_FUNC; i++)
	{
		solution[i] = 0;
	}
}

double endodatio::get(int i)
{
	assert(i >= 0 && i < NO_FUNC);
	return solution[i];
}

void endodatio::put(int i, double value)
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

endodatio::~endodatio()
{
	// destructor
	delete[] solution;
}
