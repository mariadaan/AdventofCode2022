#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

/*
A rock
B paper
C scissors

Bij A moet ik wel B gekozen hebben
bij B moet ik wel C gekozen hebben
bij C moet ik wel A gekozen hebben

Bij A moet ik wel C gekozen hebben
bij B moet ik wel A gekozen hebben
bij C moet ik wel B gekozen hebben

+ 1 of - 2

X rock
Y paper
Z scissors

A == X
B == Y
C == Z

X - A = 23

X - B = 22 lose
X - C = 21 win

Y - C = 22 lose
Y - A = 24 win

Z - A = 25 lose
Z - B = 24 win

X means you need to lose,
Y means you need to end the round in a draw,
and Z means you need to win.

X = lose
Y = draw
Z = win

 */

int main()
{
	std::string oneRound;
	std::ifstream inputFile("realData.txt");

	int totalScoreOne = 0;
	int totalScoreTwo = 0;

	while (std::getline(inputFile, oneRound))
	{
		char opponent = oneRound[0];
		char me = oneRound[2];
		totalScoreOne += me - 'W';
		if (me - opponent == 'X' - 'A') // draw 1
			totalScoreOne += 3;
		else if (me - opponent == 21 || me - opponent == 24) // win 1
			totalScoreOne += 6;
		if (me == 'Y') // draw 2
		{
			totalScoreTwo += opponent - 64;
			totalScoreTwo += 3;
		}
		else if (me == 'Z') // win 2
		{
			if (opponent == 'A')
				totalScoreTwo += 2;
			else if (opponent == 'B')
				totalScoreTwo += 3;
			else if (opponent == 'C')
				totalScoreTwo += 1;
			totalScoreTwo += 6;
		}
		else if (me == 'X') // lose 2
		{
			if (opponent == 'A')
				totalScoreTwo += 3;
			else if (opponent == 'B')
				totalScoreTwo += 1;
			else if (opponent == 'C')
				totalScoreTwo += 2;
		}
	}

	std::cout << "answer part 1 : " << totalScoreOne << std::endl;
	std::cout << "answer part 2 : " << totalScoreTwo << std::endl;

	inputFile.close();
}
