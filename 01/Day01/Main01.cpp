#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef unsigned int uint;

#define INT_NAN INT_MIN

uint MAX_ITERATIONS = 999999999;

/*
Problem A:

1) Read input file
2) Parse input files (extract sign and then value)
3) Add to accumulated amount
*/

bool HumptyDumptyAssert(bool b, const char* msg)
{
	if (!b)
	{
		std::cout << "Error: " << msg << std::endl;
		return false;
	}
	
	// No error
	return true;
}

int CalculateProblemA(const char* fileName)
{
	std::ifstream infile(fileName);

	if(!HumptyDumptyAssert(infile.good(), "Input file not found!"))
	{
		return INT_NAN;
	}

	int sum = 0;

	std::string line;
	while(std::getline(infile, line))
	{
		std::istringstream iss(line);
		char sign;

		iss >> sign;

		// not a char
		if (iss.fail())
		{
			continue;
		}

		// Not a valid operator
		if (sign != '+' && sign != '-')
			continue;

		int value;
		iss >> value;

		// Not a valid int
		if (iss.fail())
			continue;

		sum += sign == '+' ? value : -value;
	}

	return sum;
}


int CalculateProblemB(const char* fileName)
{
	std::ifstream infile(fileName);

	if (!HumptyDumptyAssert(infile.good(), "Input file not found!"))
	{
		return INT_NAN;
	}

	int result = 0;
	std::vector<int> vecResults;
	vecResults.push_back(result);

	uint iterations = 0;
	std::string line;
	while (std::getline(infile, line) && iterations < MAX_ITERATIONS )
	{
		std::istringstream iss(line);
		char sign;

		iss >> sign;

		// not a char
		if (iss.fail())
		{
			continue;
		}

		// Not a valid operator
		if (sign != '+' && sign != '-')
			continue;

		int value;
		iss >> value;

		// Not a valid int
		if (iss.fail())
			continue;
		
		++iterations;
		result += sign == '+' ? value : -value;
		
		if (std::find(vecResults.begin(), vecResults.end(), result) != vecResults.end())
		{
			return result;
		}

		
		vecResults.push_back(result);

		if (infile.eof())
		{
			infile.clear();
			infile.seekg(0, std::ios::beg);
		}
	}

	return INT_NAN;
}


int main()
{
	const char* fileName = "Input.txt";
	int ansA = CalculateProblemA(fileName);

	if (ansA != INT_NAN)
		std::cout << "The answer to problem A is '" << ansA << "'!" << std::endl;

	int ansB = CalculateProblemB(fileName);
	if (ansB != INT_NAN)
		std::cout << "The answer to problem B is '" << ansB << "'!" << std::endl;

	return 0;
}