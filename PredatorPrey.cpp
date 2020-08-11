//
//  
//  
//
//  Created by James Day on 4/11/17.
//  Copyright � 2017 James Day. All rights reserved.
//
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <random>
#include "Organism.h"
using namespace std;

void populateWorld(Organism *matrix[22][22]);
void populateAnts(Organism *matrix[22][22]);
void populateDoodleBugs(Organism *matrix[22][22]);
void playGame(Organism *matrix[22][22]);
void print(Organism *matrix[22][22]);
void border(Organism *matrix[22][22]);
void popCount(Organism *matrix[22][22]);

int main() {

	srand(time(nullptr));
	Organism *world[22][22];

	populateWorld(world);
	border(world);
	populateAnts(world); //100 ants
	populateDoodleBugs(world); //5 doodlebugs

	while (true)
	{
		playGame(world);
	}
	return 0;
}

void populateWorld(Organism *matrix[22][22])
{
	for (int x = 0; x < 22; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			matrix[x][y] = new Organism;
		}
	}
}

void populateAnts(Organism *matrix[22][22])
{
	for (int i = 0; i < 100; i++) //make 100 ants
	{
		int randomX = 1 + ((int)rand() % 20);
		int randomY = 1 + ((int)rand() % 20);
		while (matrix[randomX][randomY]->symb == 'O') //Duplicate check
		{
			randomX = 1 + ((int)rand() % 20);
			randomY = 1 + ((int)rand() % 20);
		}
		matrix[randomX][randomY] = new Ants;
	}
}

void populateDoodleBugs(Organism *matrix[22][22])
{
	for (int i = 0; i < 5; i++) //make 5 doodlebugs
	{
		int randomX = 1 + (rand() % 20);
		int randomY = 1 + (rand() % 20);
		while ((matrix[randomX][randomY]->symb == 'O') || (matrix[randomX][randomY]->symb == 'X')) //Duplicate Check
		{
			randomX = 1 + ((int)rand() % 20);
			randomY = 1 + ((int)rand() % 20);
		}
		matrix[randomX][randomY] = new DoodleBugs;
	}
}

void playGame(Organism *matrix[22][22])
{
	print(matrix);
	//cout << "Press \"Enter\" to continue... \n";
	cin.ignore();

	for (int x = 1; x < 22; x++) //Ants Move
	{
		for (int y = 1; y < 22; y++)
		{
			int direction = 1 + (rand() % 4);

			matrix[x][y]->move(matrix, x, y, direction);
		}
	}


	//cout << "--------------------" << endl;
}

void print(Organism *matrix[22][22])
{
	for (int x = 0; x < 22; x++) //print
	{
		for (int y = 0; y < 22; y++)
		{
			char bleh = ' ';
			bleh = matrix[x][y]->symb;
			cout << bleh;
			matrix[x][y]->moveOnce = false;
		}
		cout << endl;
	}
	popCount(matrix);
}

void border(Organism *matrix[22][22])
{
	for (int x = 0; x < 22; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			if ((x == 0) || (x == 21) || (y == 0) || (y == 21))
			{
				matrix[x][y] = new Blank;
			}
		}
	}
}

void popCount(Organism *matrix[22][22])
{
	int antPop = 0;
	int doodPop = 0;
	for (int x = 0; x < 22; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			if (matrix[x][y]->symb == 'O')
			{
				antPop++;
			}
			else if (matrix[x][y]->symb == 'X')
			{
				doodPop++;
			}
		}
	}
	cout << "Ant Pop: " << antPop << endl;
	cout << "DoodleBugs Pop: " << doodPop << endl;
}
