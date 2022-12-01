#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

int main() {
	std::string caloriesStr;
	std::ifstream inputFile("realData.txt");

	std::vector<int> elfs;
	std::vector<int> oneElf;

	while (std::getline (inputFile, caloriesStr))
	{
		if (caloriesStr.empty())
		{
			int sumOneElf = std::accumulate(oneElf.begin(), oneElf.end(), 0);
			elfs.push_back(sumOneElf);
			oneElf.clear();
		}
		else
		{
			int caloriesNum = stoi(caloriesStr);
			oneElf.push_back(caloriesNum);
		}
	}
	std::cout << "answer 1: " << *max_element(std::begin(elfs), std::end(elfs)) << std::endl;

	std::sort(elfs.begin(), elfs.end(), std::greater<int>());
	elfs.erase(elfs.begin() + 3, elfs.end());
	int sumTopThree = std::accumulate(elfs.begin(), elfs.end(), 0);

	std::cout << "answer 2: " << sumTopThree << std::endl;

	inputFile.close();
}
