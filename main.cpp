#include "shared.h"

int main()
{
	forma *expression; // object to hold matrix equation
	endodatio *coefficient_list; // object to hold the solution which are the coefficients.	
	
	expression = new forma();
	coefficient_list = new endodatio();
	
	// construct the matrix equation using the method described on pp 551-553 of 
	// Algorithms in C by Robert Sedgewick
	expression->initialize();
	//cout << "The equations:" << endl;
	//expression->output();
	
	// Perform Gaussian Elimination using the method described on 539 of 
	// Algorithms in C by Robert Sedgewick
	expression->eliminate();
	
	// Perform Gaussian back substitution using the method described on 540 of 
	// Algorithms in C by Robert Sedgewick
	expression->substitute(coefficient_list);
	cout << "coefficients:" << endl;
	coefficient_list->output();
	
	// Substitute the coefficients back in to equation one to test the solution.
	expression->test_solution(coefficient_list);
	
	// Extrapolate the price on for a future date.
	coefficient_list->predict(NO_DATA + 1);
	
	// Save the coefficients to a csv for use by graphing script.
	coefficient_list->save_coefficents();
	//cout << "Actual: " << test.at(1).second.at(NO_DATA) << endl;
	return 0;
}
