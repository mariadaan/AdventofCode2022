#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

/* DEBUGGING UTILS */
void printDups(std::string str)
{
	std::unordered_map<char, int> count;
	for (int i = 0; i < str.length(); i++)
	{
		count[str[i]]++; // increase the count of characters by 1
	}

	for (auto it : count)
	{					   // iterating through the unordered map
		if (it.second > 1) // if the count of characters is greater then 1 then duplicate found
			std::cout << it.first << ", count = " << it.second
					  << "\n";
	}
}

void printMap(std::map<char, int> myMap)
{
	for (auto it = myMap.cbegin(); it != myMap.cend(); ++it)
	{
		std::cout << it->first << " " << it->second << "\n";
	}
}

void printStrVector(std::vector<std::string> myGroup)
{
	for (auto it = myGroup.begin(); it != myGroup.end(); it++)
		std::cout << *it << std::endl;
}

/* ACTUAL CODE */

int getScore(char c)
{
	if (islower(c))
		return c - 'a' + 1;
	return c - 'A' + 27;
}

char findCommonChar(std::string s1, std::string s2)
{
	std::map<char, int> myMap;

	for (int i = 0; i < s1.length(); i++)
		myMap[s1[i]]++;

	for (int i = 0; i < s2.length(); i++)
		if (myMap[s2[i]] > 0)
			return s2[i];
	return 0;
}

char findCommon(std::vector<std::string> group)
{
	std::map<char, int> mapOne;
	std::map<char, int> mapTwo;

	for (int i = 0; i < group[0].length(); i++)
		mapOne[group[0][i]]++;
	for (int j = 0; j < group[1].length(); j++)
		mapTwo[group[1][j]]++;

	for (int k = 0; k < group[2].length(); k++)
	{
		if (mapOne[group[2][k]] > 0 && mapTwo[group[2][k]] > 0)
			return group[2][k];
	}
	return 0;
}

int main()
{
	std::string ruckSack;
	std::ifstream inputFile("realData.txt");
	std::vector<std::string> group;

	int totalScoreOne = 0;
	int totalScoreTwo = 0;

	int i = 0;

	while (std::getline(inputFile, ruckSack))
	{
		// PART 1
		std::string compOne = ruckSack.substr(0, ruckSack.length() / 2);
		std::string compTwo = ruckSack.substr(ruckSack.length() / 2);
		totalScoreOne += getScore(findCommonChar(compOne, compTwo));

		// PART 2
		if (i != 0 && (i % 3 == 0 || inputFile.eof()))
		{
			if (inputFile.eof())
				group.push_back(ruckSack);
			// printStrVector(group);
			// std::cout << "\n";
			totalScoreTwo += getScore(findCommon(group));
			group.clear();
		}
		group.push_back(ruckSack);
		i++;
	}

	std::cout << "answer part 1 : " << totalScoreOne << std::endl;
	std::cout << "answer part 2 : " << totalScoreTwo << std::endl;

	inputFile.close();
}
