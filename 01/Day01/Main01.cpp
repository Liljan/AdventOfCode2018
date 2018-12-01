#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef unsigned int uint;

const int INT_NAN = INT_MIN;
const uint MAX_ITERATIONS = 999999999;

// Prints an error message if the parameter bool is false
bool MySTDAssert(bool b, const char* msg)
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

	if(!MySTDAssert(infile.good(), "Input file not found!"))
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

	if(!MySTDAssert(infile.good(), "Input file not found!"))
	{
		return INT_NAN;
	}

	std::vector<int> values;
	std::vector<int> frequencies;	

	uint iterations = 0;
	std::string line;

	// read from file
	while (std::getline(infile, line)  )
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
		
		int resultingValue = sign == '+' ? value : -value;
		values.push_back(resultingValue);
	}

	int currentFrequency = 0;
	frequencies.push_back(currentFrequency);

	// find the first repeating frequency
	while (iterations < MAX_ITERATIONS)
	{
		for (const int value : values)
		{
			currentFrequency += value;
			++iterations;

			if (std::find(frequencies.begin(), frequencies.end(), currentFrequency) != frequencies.end())
			{
				return currentFrequency;
			}

			frequencies.push_back(currentFrequency);
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