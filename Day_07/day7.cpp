#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class Directory
{
public:
	int myFilesSize;
	std::vector<Directory> myDirectories;
};
 
void printMap(std::string_view comment, const std::map<std::string, int>& map)
{
	std::cout << comment;

 for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); it++)
	 std::cout << it->first << " = " << it->second << "; ";
	std::cout << '\n';
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

std::string getDirName(std::string line)
{
	return splitStr(line, " ")[2];
}

int getFileSize(std::string line)
{
	return stoi(splitStr(line, " ")[0]);
}

int getDirSize(std::string line, std::string currentDir, std::map<std::string, int> &dirSizes)
{
	int dirSize;
	std::string dirToAdd = splitStr(line, " ")[1];
	return dirSizes[dirToAdd];
}

std::map<std::string, int> saveFiles(std::vector<std::string> terminalInput)
{
	std::string line;
	std::map<std::string, int> dirSizes;
	std::string currentDir = "/";
	int fileSize = 0;


	for (int i = 0; i < terminalInput.size(); i++)
	{
		line = terminalInput[i];
		if (line == "$ cd ..")
			continue;
		if (line.compare(0,5,"$ cd ") == 0)
			currentDir = getDirName(line);
		else if (isdigit(line[0]))
		{
			fileSize = getFileSize(line);
			dirSizes[currentDir] += fileSize;
		}
	}
	printMap("my map: ", dirSizes);
	return dirSizes;
}

// void dirInDir(std::vector<std::string> terminalInput, std::map<std::string, int> &dirSizes)
// {
// 	std::string line;
// 	std::string currentDir = "/";
// 	int dirSize = 0;

// 	for (int i = 0; i < terminalInput.size(); i++)
// 	{
// 		line = terminalInput[i];
// 		if (line == "$ cd ..")
// 			continue;
// 		if (line.compare(0,5,"$ cd ") == 0)
// 			currentDir = getDirName(line);
// 		else if (line.compare(0,4,"dir ") == 0)
// 		{
// 			dirSize = getDirSize(line, currentDir, dirSizes);
// 			dirSizes[currentDir] += dirSize;
// 		}
// 	}
// 	printMap("my map: ", dirSizes);
// }


// void dirInDir(std::string line, std::string currentDir, std::map<std::string, int> &dirSizes)
// {
// 	std::string currentDir = "/";
// 	int dirSize = 0;

// 	if (line == "$ cd ..")
// 		continue;
// 	if (line.compare(0,5,"$ cd ") == 0)
// 		currentDir = getDirName(line);
// 	else if (line.compare(0,4,"dir ") == 0)
// 	{
// 		dirSize = getDirSize(line, currentDir, dirSizes);
// 		dirSizes[currentDir] += dirSize;
// 	}
// }

int getMaxDepth(std::vector<std::string> terminalInput)
{
	std::string line;
	std::string currentDir = "/";
	int depth = 0;
	int maxDepth = 0;

	for (int i = 0; i < terminalInput.size(); i++)
	{
		line = terminalInput[i];
		if (line != "$ cd .." &&  line.compare(0,5,"$ cd ") == 0)
		{
			currentDir = getDirName(line);
			depth++;
			maxDepth = depth > maxDepth ? depth : maxDepth;
		}
		else if (line == "$ cd ..")
			depth--;
	}
	std::cout << "maxDepth: " << maxDepth << std::endl;
	return maxDepth;
}

/* 
go most deep
save maxDepth
dir in dir toepassen depthlevel van onder naar boven
 */

std::vector<std::string> getInput(std::string filename)
{
	std::ifstream inputFile(filename);
	std::vector<std::string> allLines;
	std::string line;

	while (std::getline(inputFile, line))
	{
		allLines.push_back(line);
	}
	inputFile.close();
	return allLines;
}

void fillDirs(std::vector<std::string> terminalInput, std::map<std::string, int> &dirSizes)
{
	std::string line;
	std::string currentDir = "/";
	int depth = 0;
	int maxDepth = 0;

	for (int i = 0; i < terminalInput.size(); i++)
	{
		line = terminalInput[i];
		if (line != "$ cd .." &&  line.compare(0,5,"$ cd ") == 0)
		{
			currentDir = getDirName(line);
			depth++;
			// if (depth == maxDepth - 1)
			// {
			// 	dirInDir()
			// }
		}
		else if (line == "$ cd ..")
			depth--;
	}
}


int main()
{
	std::string filename = "testData.txt";
	std::vector<std::string> terminalInput = getInput(filename);
	std::map<std::string, int> dirSizes;

	dirSizes = saveFiles(terminalInput);
	fillDirs(terminalInput, dirSizes);
	// dirInDir(filename, dirSizes);
	getMaxDepth(terminalInput);
}

// 	// Create a map of three (string, int) pairs
// 	std::map<std::string, int> map;

// 	map["huh"] = 8;

// 	map.insert ( std::pair<std::string,int>("hallo",100) );
// 	map.insert ( std::pair<std::string,int>("jaa",200) );

	
// 	// map = {{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
 
// 	printMap("1) Initial map: ", map);
 
// 	map["CPU"] = 25; // update an existing value
// 	map["SSD"] = 30; // insert a new value
// 	printMap("2) Updated map: ", map);
 
// 	// using operator[] with non-existent key always performs an insert
// 	std::cout << "3) map[UPS] = " << map["UPS"] << '\n';
// 	printMap("4) Updated map: ", map);
 
// 	map.erase("GPU");
// 	printMap("5) After erase: ", map);
 
 
// 	map.clear();
// 	std::cout << std::boolalpha << "8) Map is empty: " << map.empty() << '\n';
// }