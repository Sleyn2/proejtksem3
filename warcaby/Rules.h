#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "Coordinates.h"
#include "Board.h"

class Rules
{
	enum turn {white=0, black=1, whitenext=2, blacknext=3};
	turn game;
	int coords[2];
public:
	bool operator==(int a)
	{
		if(this->game==a)
			return true;
		return false;
	}
	void operator=(int select)
	{
		if (select == 0)
			game = white;
		else if (select == 1)
			game = black;
		else if (select == 2)
			game = whitenext;
		else if (select == 3)
			game = blacknext;
	}
	bool operator<<(string fileName)
	{
		int a;
		ifstream file;
		file.open(fileName);
		if (!file.good())
			return false;
		file >> a >> this->coords[0] >> this->coords[1];
		*this = a;
		return true;
	}
	void operator>>(string fileName)
	{
		ofstream file;
		file.open(fileName, ios::trunc);
		int a = this->game;
		file << a << " ";
		a = this->coords[0];
		if (a > 9 || a < 0)
			a = 10;
		file << a << " ";
		a = this->coords[1];
		if (a > 9 || a < 0)
			a = 10;
		file << a << "\n";
	}
	void nextturn()
	{
		if (this->game == 0)
			this->game = black;
		else if(this->game == 1)
			this->game = white;
	}
	int moveposition(int choose)
	{
		return this->coords[choose];
	}
	void nextposition(int x, int y)
	{
		this->coords[0] = x;
		this->coords[1] = y;
	}
};