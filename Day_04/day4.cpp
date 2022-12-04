#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void printStrVector(std::vector<std::string> myGroup)
{
	for (auto it = myGroup.begin(); it != myGroup.end(); it++)
		std::cout << *it << std::endl;
}

void printIntVector(std::vector<int> myGroup)
{
	for (auto it = myGroup.begin(); it != myGroup.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl;
}

std::vector<int> strToIntVector(std::vector<std::string> strVector)
{
	std::vector<int> intVector;
	for (auto it = strVector.begin(); it != strVector.end(); it++)
		intVector.push_back(stoi(*it));
	return intVector;
}

std::vector<std::string> splitStr(std::string str, std::string delimiter)
{
	std::vector<std::string> splitted;
	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		splitted.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	splitted.push_back(str);
	return splitted;
}

int checkRangesPart1(std::vector<int> section)
{
	if ((section[0] <= section[2] && section[1] >= section[3]) || (section[2] <= section[0] && section[3] >= section[1]))
		return 1;
	return 0;
}

int checkRangesPart2(std::vector<int> section)
{
	if ((section[1] < section[2]) || (section[0] > section[3]))
		return 0;
	return 1;
}

int main()
{
	std::string line;
	std::vector<std::string> splitLine;
	std::vector<int> section;

	std::ifstream inputFile("realData.txt");

	int totalScoreOne = 0;
	int totalScoreTwo = 0;

	while (std::getline(inputFile, line))
	{
		// PART 1
		line.replace(line.find(","), 1, "-");
		section = strToIntVector(splitStr(line, "-"));
		totalScoreOne += checkRangesPart1(section);
		totalScoreTwo += checkRangesPart2(section);
	}

	std::cout << "answer part 1 : " << totalScoreOne << std::endl;
	std::cout << "answer part 2 : " << totalScoreTwo << std::endl;

	inputFile.close();
}
