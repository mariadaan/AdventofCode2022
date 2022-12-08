#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
void print(const T toPrint)
{
	std::cout << toPrint << std::endl;
}

void printStrVector(const std::vector<std::string> strlist)
{
	for (std::vector<std::string>::const_iterator it = strlist.begin(); it != strlist.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl;
}

void printMap(const std::map<std::string, int>& map)
{
	for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); it++)
		std::cout << it->first << " = " << it->second << "; ";
	std::cout << std::endl;
}

std::vector<std::string> getInput(const std::string filename)
{
	std::ifstream inputFile(filename);
	std::vector<std::string> allLines;
	std::string line;

	while (std::getline(inputFile, line))
		allLines.push_back(line);
	inputFile.close();
	return allLines;
}

std::vector<std::string> splitStr(std::string str, const std::string delimiter)
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

std::map<std::string, int> getDirSizes(const std::vector<std::string> &terminalInput)
{
	std::map<std::string, int> dirSizes;
	std::vector<std::string> dirList;
	std::ostringstream fullPath;
	int size = 0;

	for (std::vector<std::string>::const_iterator itLine = terminalInput.begin(); itLine < terminalInput.end(); itLine++)
	{
		std::vector<std::string> splitLine = splitStr(*itLine, " ");
		if (*itLine == "$ cd ..")
		{
			dirList.pop_back();
		}
		else if ((*itLine).substr(0, 5) == "$ cd ")
		{
			dirList.push_back(splitLine[2]);
		}
		else if (isdigit((*itLine)[0]))
		{
			size = stoi(splitLine[0]);
			for (std::vector<std::string>::iterator itDirs = dirList.begin(); itDirs < dirList.end(); itDirs++)
			{
				// works like a join function, found this on stackoverflow lol
				std::copy(dirList.begin(), itDirs + 1, std::ostream_iterator<std::string>(fullPath, "-"));
				dirSizes[fullPath.str()] += size; // save path in dict and add size of files in current folder
				fullPath.str(std::string()); // clear fullpath
			}
		}
	}
	return dirSizes;
}

int findSmallDirs(const std::map<std::string, int> dirSizes)
{
	int total = 0;
	for (std::map<std::string, int>::const_iterator it = dirSizes.begin(); it != dirSizes.end(); it++)
	{
		if (it->second < 100000)
			total += it->second;
	}
	return total;
}

int findDirToDel(std::map<std::string, int> dirSizes)
{
	int usedSize = dirSizes["/-"];
	int freeSize = 70000000 - usedSize;
	int requiredDel = 30000000 - freeSize;
	int smallestDirToDel = usedSize;
	for (std::map<std::string, int>::iterator it = dirSizes.begin(); it != dirSizes.end(); it++)
	{
		if(it->second > requiredDel && it->second < smallestDirToDel)
			smallestDirToDel = it->second;
	}
	return smallestDirToDel;
}

int main()
{
	std::string filename = "realData.txt";
	std::vector<std::string> terminalInput = getInput(filename);
	std::map<std::string, int> dirSizes = getDirSizes(terminalInput);
	// printMap(dirSizes);
	int answerPartOne = findSmallDirs(dirSizes);
	print(answerPartOne);

	int answerPartTwo = findDirToDel(dirSizes);
	print(answerPartTwo);

	return (0);
}