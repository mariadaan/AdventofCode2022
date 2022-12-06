#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include "Move.hpp"

void printStack(std::stack<char> s)
{
	// If stack is empty then return
	if (s.empty())
		return;

	char x = s.top();

	// Pop the top element of the stack
	s.pop();

	// Recursively call the function PrintStack
	printStack(s);

	// Print the stack element starting
	// from the bottom
	std::cout << x << " ";

	// Push the same element onto the stack
	// to preserve the order
	s.push(x);
}

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

void makeMove(std::vector< std::stack<char> > &crateMap, Move &move)
{
	for (int i = 0; i < move.amount; i++)
	{
		char crate = crateMap[move.fromPos].top();
		crateMap[move.fromPos].pop();
		crateMap[move.toPos].push(crate);
	}
}

void makeMove2(std::vector< std::stack<char> > &crateMap, Move &move)
{
	for (int i = 0; i < move.amount; i++)
	{
		char crate = crateMap[move.fromPos].top();
		crateMap[move.fromPos].pop();
		crateMap[0].push(crate);
	}
	for (int j = 0; j < move.amount; j++)
	{
		char crate = crateMap[0].top();
		crateMap[0].pop();
		crateMap[move.toPos].push(crate);
	}
}

std::string getFinalStr(int numStacks, std::vector< std::stack<char> > crateMap)
{
	std::string finalStr;
	for (int index = 1; index < numStacks + 1; index++)
	{
		finalStr.push_back(crateMap[index].top());
		// std::cout << index << ": ";
		// std::cout << crateMap[index].top();
		// std::cout << std::endl;
	}
	return finalStr;
}

int main()
{
	std::string line;
	std::vector<std::string> crateMapStr;

	// std::ifstream inputFile("exampleData.txt");
	std::ifstream inputFile("realData.txt");

	// parse map
	while (std::getline(inputFile, line))
	{
		if (line.empty())
			break;
		crateMapStr.push_back(line);
	}
	int numStacks = (crateMapStr.back().length() + 1) / 4;
	std::vector< std::stack<char> > crateMap;

	// initiate array of stacks
	std::stack<char> myStack;
	for (int j = 0; j < numStacks + 1; j++)
		crateMap.push_back(myStack);

	std::vector<std::string>::reverse_iterator it = ++crateMapStr.rbegin();
	std::string stacksPos = crateMapStr.back();
	while (it != crateMapStr.rend())
	{
		for (int i = 0; i < (*it).length(); i++)
			if (isupper((*it)[i]))
			{
				int pos = stacksPos[i] - '0';
				(crateMap[pos]).push((*it)[i]);
			}
		it++;
	}

	// for (int k = 0; k < numStacks + 1; k++)
	// {
	// 	std::cout << k << ": ";
	// 	printStack(crateMap[k]);
	// 	std::cout << std::endl;
	// }
	// for(int i = 1; i < numStacks; i++)
	// {
	// }
	// printStrVector(crateMapStr);

	// parse moves
	while (std::getline(inputFile, line))
	{
		// std::cout << line << std::endl;
		std::vector<std::string> splitted;
		splitted = splitStr(line, " ");
		Move move(stoi(splitted[1]), stoi(splitted[3]), stoi(splitted[5]));
		makeMove2(crateMap, move);
		// printStrVector(splitted);
		// std::cout << std::endl;
	}
	std::string answerOne = getFinalStr(numStacks, crateMap);
	// for (int index = 0; index < numStacks + 1; index++)
	// {
	// 	std::cout << index << ": ";
	// 	printStack(crateMap[index]);
	// 	std::cout << std::endl;
	// }
	std::cout << "answer part 1 : " << answerOne << std::endl;

	inputFile.close();
}
