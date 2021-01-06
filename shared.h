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
	#include <iomanip> 
	
	using namespace std; 

	#define NO_DATA 70
	#define NO_FUNC 21
	
	class dzvector
{
	// dzvectors should be NO_DATA in length
	private:
		long double *cursus;

	public:
		dzvector();
		dzvector(long double*);
		void output_vec();
		long double get(int i);
		long double dot_product(dzvector* vec);
};

	class endodatio
	{
		private:
			long double *solution;
		
		public:
			endodatio();
			~endodatio();
			void put(int, long double);
			long double get(int);
			void output();
			void predict(int next);
			void save_coefficents();
	};
	
	class forma
	{
		private: 
			long double *aequare;

		public:
			forma();
			~forma();
			forma(long double**);
			long double get(int, int);
			void put(int, int, long double);
			void eliminate();
			void substitute(endodatio*);
			void output_matrix();
			void test_solution(endodatio*);
			void output();
			void initialize();
	};
	
	std::vector<std::pair<std::string, std::vector<long double>>> read_csv(std::string );
	void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<long double>>> );
	
#endif
