#include "shared.h"

vector<pair<string, vector<long double>>> read_csv(string filename)
{
	// Reads a CSV file into a vector of <string, vector<int>> pairs where
	// each pair represents <column name, column values>

	// Create a vector of <string, long double vector> pairs to store the result
	vector<pair<string, vector<long double>>> result;

	// Create an input filestream
	ifstream myFile(filename);

	// Make sure the file is open
	if(!myFile.is_open()) throw runtime_error("Could not open file");

	// Helper vars
	string line, colname;
	long double val;

	// Read the column names
	if(myFile.good())
	{
		// Extract the first line in the file
		getline(myFile, line);

		// Create a stringstream from line
		stringstream ss(line);

		// Extract each column name
		while(getline(ss, colname, ','))
		{
			// Initialize and add <colname, long double vector> pairs to result
			result.push_back({colname, vector<long double> {}});
		}
	}

	// Read data, line by line
	while(getline(myFile, line))
	{
		// Create a stringstream of the current line
		stringstream ss(line);
		
		// Keep track of the current column index
		int colIdx = 0;
		
		// Extract each long double
		while(ss >> val)
		{
			// Add the current long double to the 'colIdx' column's values vector
			result.at(colIdx).second.push_back(val);
			
			// If the next token is a comma, ignore it and move on
			if(ss.peek() == ',') ss.ignore();
			
			// Increment the column index
			colIdx++;
		}
	}

	// Close file
	myFile.close();

	return result;
}

void write_csv(string filename, vector<pair<string, vector<int>>> dataset)
{
	// Make a CSV file with one or more columns of integer values
	// Each column of data is represented by the pair <column name, column data>
	//   as pair<string, vector<int>>
	// The dataset is represented as a vector of these columns
	// Note that all columns should be the same size
	
	// Create an output filestream object
	ofstream myFile(filename);
	
	// Send column names to the stream
	for(int j = 0; j < dataset.size(); j++)
	{
		myFile << dataset.at(j).first;
		if(j != dataset.size() - 1)
		{
			 myFile << ","; // No comma at end of line
		}
	}
	myFile << "\n";
	
	// Send data to the stream
	for(int i = 0; i < dataset.at(0).second.size(); i++)
	{
		for(int j = 0; j < dataset.size(); j++)
		{
			myFile << dataset.at(j).second.at(i);
			if(j != dataset.size() - 1)
			{
				 myFile << ","; // No comma at end of line
			}
		}
		myFile << "\n";
	}	
	// Close the file
	myFile.close();
}
