#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Rules.h"
#include "Board.h"

using namespace std;

struct game{
	Board* locations;
	Rules* turn;
};

class Save
{
public:
	game* current;
	char nameArray[10][12] = {"save1.data", "save2.data", "save3.data", "save4.data" ,
	"save5.data", "save6.data" ,"save7.data", "save8.data", "save9.data", "save10.data" };
};

class QuickSave : public Save
{
public:
	QuickSave(game* save)
	{
		this->current = save;
	}
	void save()
	{
		this->current->turn->operator>>(this->nameArray[0]);
		this->current->locations->operator>>(this->nameArray[0]);
		return;
	}
	void discard()
	{
		remove(this->nameArray[0]);
	}
};
class MultiSave : public Save
{
public:
	MultiSave(game* save)
	{
		this->current = save;
	}

};