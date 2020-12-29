#ifndef SHARED_INCLUDES_HEADER
	#define SHARED_INCLUDES_HEADER

	#include <string>
	#include <fstream>
	#include <vector>
	#include <utility> 		// std::pair
	#include <stdexcept> 	// std::runtime_error
	#include <sstream> 		// std::stringstream
	#include <math.h>
	#include <iostream>
	#include <assert.h>
	
	using namespace std; 

	#define NO_DATA 4
	#define NO_FUNC 4
	
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

	class endodatio
	{
		private:
			double *solution;
		
		public:
			endodatio();
			~endodatio();
			void put(int, double);
			double get(int);
			void output();
	};
	
	class forma
	{
		private: 
			double *x;

		public:
			forma();
			~forma();
			forma(double**);
			double get(int, int);
			void put(int, int, double);
			void eliminate();
			void substitute(endodatio*);
			void output_matrix();
			void test_solution(endodatio*);
	};
#endif
