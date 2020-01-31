#pragma once

#include <iostream>

using namespace std;

class Coordinates
{
	int read[4];
	int counted[4];
public:
	void preset()
	{
		for (int i = 0; i < 4; i++)
		{
			this->counted[i] = 0;
			this->read[i] = 1000;
		}
	};
	void set(int x, int value)
	{
		this->read[x] = value;
	};
	void count()
	{
		while (read[0] > 80)
		{
			read[0] -= 80;
			this->counted[0]++;
		}
		while (read[1] > 80)
		{
			read[1] -= 80;
			this->counted[1]++;
		}
		while (read[2] > 80)
		{
			read[2] -= 80;
			this->counted[2]++;
		}
		while (read[3] > 80)
		{
			read[3] -= 80;
			this->counted[3]++;
		}
	};
	int get(int x, int y)
	{
		if (x == 0)
			return read[y];
		else if (x == 1)
			return counted[y];
		else
			return NULL;
	};
};
