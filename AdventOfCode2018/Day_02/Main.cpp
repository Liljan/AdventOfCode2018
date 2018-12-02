#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

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

bool CountExactAppearences(const std::string& str, int appearances)
{
	std::map<char, uint> charFrequencies;

	for(char c : str)
	{	
		auto it = charFrequencies.find(c);

		if(it != charFrequencies.end())
			charFrequencies[c]++;
		else
			charFrequencies.emplace(c, 1);			
	}

	for (auto it = charFrequencies.begin(); it != charFrequencies.end(); it++)
	{
		if (it->second == appearances)
		{
			std::cout << it->first << " was found " << it->second << " times in " << str << "." << std::endl;
			return true;
		}
	}

	return false;
}


uint SolveProblemA(const char* fileName)
{
	std::ifstream infile(fileName);

	if (!MySTDAssert(infile.good(), "Input file not found!"))
	{
		return INT_NAN;
	}

	uint amount2s = 0;
	uint amount3s = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		if (CountExactAppearences(line, 2))
			amount2s++;
		if (CountExactAppearences(line, 3))
			amount3s++;
	}

	std::cout << amount2s << " (2) and " << amount3s << " (3) were found" << std::endl;

	return amount2s * amount3s;
}


int main()
{
	const char* fileName = "Input.txt";
	int ansA = SolveProblemA(fileName);
	std::cout << "The checksum of Problem A is " << ansA << std::endl;
	
	return 0;
}