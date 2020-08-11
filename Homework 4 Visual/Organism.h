#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <random>
using namespace std;

class Organism
{
public:
	Organism()
	{
		symb = '~';
	}
	virtual void move(Organism *matrix[22][22], int x, int y, int direction) {}
	virtual void breed(Organism *matrix[22][22], int row, int col) {}
	virtual bool starve(Organism *matrix[22][22], int row, int col) { return false;  }
	int moveCount;
	char symb;
	bool moveOnce;
	bool hasEaten;

	int x;
	int y;
};

class Ants : public Organism
{
public:
	Ants()
	{
		symb = 'O';
		moveCount = 0;
		moveOnce = false;
	}
	virtual void move(Organism *matrix[22][22], int row, int col, int direction)
	{
		if (this->moveOnce == true) // check if it has moved already
		{
			return;
		}
		this->moveOnce = true;


		switch (direction)
		{
		case 1:
		{
			if (matrix[row - 1][col]->symb == '~') //up
			{
				matrix[row - 1][col] = matrix[row][col];
				matrix[row][col] = new Organism;
				row = row - 1;
			}
			break;
		}
		case 2:
		{
			if (matrix[row][col + 1]->symb == '~') //right
			{
				matrix[row][col + 1] = matrix[row][col];
				matrix[row][col] = new Organism;
				col = col + 1;
			}
			break;
		}
		case 3:
		{
			if (matrix[row + 1][col]->symb == '~') //down
			{
				matrix[row + 1][col] = matrix[row][col];
				matrix[row][col] = new Organism;
				row = row + 1;
			}
			break;
		}
		case 4:
		{
			if (matrix[row][col - 1]->symb == '~') //left
			{
				matrix[row][col - 1] = matrix[row][col];
				matrix[row][col] = new Organism;
				col = col - 1;
			}
			break;
		}
		};

		if (this->moveCount++ >= 3) {
			breed(matrix, row, col);
		}
	}
	virtual void breed(Organism *matrix[22][22], int row, int col)
	{
		if (matrix[row - 1][col]->symb == '~') //up
		{
			matrix[row - 1][col] = new Ants;
		}
		else if (matrix[row][col + 1]->symb == '~') //right
		{
			matrix[row][col + 1] = new Ants;
		}
		else if (matrix[row + 1][col]->symb == '~') //down
		{
			matrix[row + 1][col] = new Ants;
		}
		else if (matrix[row][col - 1]->symb == '~') //left
		{
			matrix[row][col - 1] = new Ants;
		}
		matrix[row][col]->moveCount = 0;
	}
	
};

class DoodleBugs : public Organism
{
public:
	DoodleBugs()
	{
		symb = 'X';
		moveCount = 0;
		moveOnce = false;
		hasEaten = false;
	}
	virtual void move(Organism *matrix[22][22], int row, int col, int direction)
	{

		if (this->moveOnce == true) // check if doodlebug has moved already
		{
			return;
		}
		
		this->hasEaten = false;

		if (matrix[row - 1][col]->symb == 'O') // check up if there is an ant around it to eat
		{
			direction = 1;
			this->hasEaten = true;
		}
		else if (matrix[row][col + 1]->symb == 'O') // check right  if there is an ant around it to eat
		{
			direction = 2;
			this->hasEaten = true;
		}
		else if (matrix[row + 1][col]->symb == 'O') // check down if there is an ant around it to eat
		{
			direction = 3;
			this->hasEaten = true;
		}
		else if (matrix[row][col - 1]->symb == 'O') // check left if there is an ant around it to eat
		{
			direction = 4;
			this->hasEaten = true;
		}

		switch (direction)
		{
		case 1:
		{
			if ((matrix[row - 1][col]->symb == '~') || (matrix[row - 1][col]->symb == 'O')) //up
			{
				matrix[row - 1][col] = matrix[row][col];
				matrix[row][col] = new Organism;
				row = row - 1;
			}
			break;
		}
		case 2:
		{
			if ((matrix[row][col + 1]->symb == '~') || (matrix[row][col + 1]->symb == 'O')) //right
			{
				matrix[row][col + 1] = matrix[row][col];
				matrix[row][col] = new Organism;
				col = col + 1;
			}
			break;
		}
		case 3:
		{
			if ((matrix[row + 1][col]->symb == '~') || (matrix[row + 1][col]->symb == 'O')) //down
			{
				matrix[row + 1][col] = matrix[row][col];
				matrix[row][col] = new Organism;
				row = row + 1;
			}
			break;
		}
		case 4:
		{
			if ((matrix[row][col - 1]->symb == '~') || (matrix[row][col - 1]->symb == 'O')) //left
			{
				matrix[row][col - 1] = matrix[row][col];
				matrix[row][col] = new Organism;
				col = col - 1;
			}
			break;
		}

		};

		matrix[row][col]->moveCount++;
		matrix[row][col]->moveOnce = true;

		//cout << this->moveCount << endl;

		if (this->moveCount >= 8)
		{
			breed(matrix, row, col);
		}
		else if (this->hasEaten == false && this->moveCount > 0 && this->moveCount % 3 == 0)
		{
			starve(matrix, row, col);
		}
	}
	virtual void breed(Organism *matrix[22][22], int row, int col)
	{
		//cout << "bredding 1" << endl;
		if (matrix[row - 1][col]->symb == '~') //up
		{
			matrix[row - 1][col] = new DoodleBugs; // breed a new doodle bug 
		}
		else if (matrix[row][col + 1]->symb == '~') //right
		{
			matrix[row][col + 1] = new DoodleBugs; // breed a new doodle bug 
		}
		else if (matrix[row + 1][col]->symb == '~') //down
		{
			matrix[row + 1][col] = new DoodleBugs; // breed a new doodle bug 
		}
		else if (matrix[row][col - 1]->symb == '~') //left
		{
			matrix[row][col - 1] = new DoodleBugs; // breed a new doodle bug 
		}
		this->moveCount = 0; // reset orginal bug 
		this->hasEaten = false; // reset orginal bug 
	}
	virtual bool starve(Organism *matrix[22][22], int row, int col)
	{
		//cout << "starting starve" << endl;
		//cout << "should be dying" << endl;
		matrix[row][col] = new Organism;
		return true;
	}
};

class Blank : public Organism
{
public:
	Blank()
	{
		symb = ' ';
	}
	virtual void move(Organism *matrix[22][22], int x, int y){}
	virtual void breed() {}
	virtual void starve() {}
};
