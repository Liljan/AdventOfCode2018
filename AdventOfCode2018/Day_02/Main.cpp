#include <iostream>
#include <fstream>
#include <string>
#include <map>
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

bool HasAmountOfDiffs(const std::string& str1, const std::string& str2, const uint DIFFS)
{
	if(str1.length() != str2.length())
		false;

	int currentDiff = 0;
	for(uint i = 0; i < str1.length(); ++i)
	{
		if (str1[i] != str2[i])
			currentDiff++;
	}

	return currentDiff == DIFFS;
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


const std::string SolveProblemB(const char* fileName)
{
	std::ifstream infile(fileName);

	if (!MySTDAssert(infile.good(), "Input file not found!"))
	{
		return nullptr;
	}

	std::vector<std::string> tokens;

	std::string line;
	while (std::getline(infile, line))
	{
		tokens.push_back(line);
	}

	const uint DIFFS = 1;

	for (const std::string& str1 : tokens)
	{
		for (const std::string& str2 : tokens)
		{
			if (HasAmountOfDiffs(str1, str2, DIFFS))
			{
				std::string result;
				for (uint i = 0; i < str1.length(); ++i)
				{
					if (str1[i] == str2[i])
						result += str1[i];
				}
				return result;
			}
		}
	}

	return "";
}


int main()
{
	const char* fileName = "Input.txt";
	int ansA = SolveProblemA(fileName);
	std::cout << "The checksum of Problem A is " << ansA << std::endl;
	
	std::string ansB = SolveProblemB(fileName);
	if(!ansB.empty())
		std::cout << "The answer to problem B is " << ansB << std::endl;

	return 0;
}