#pragma once

#include <fstream>
#include <iostream>
#include <cmath>
#include "Coordinates.h"
#include "Rules.h"

using namespace std;


class Board
{
	int pole[10][10];
public:
	bool operator<<(string fileName)
	{
		ifstream file;
		int i=0, j=0, a=0;
		file.open(fileName, ios::in);
		while (true)
		{
			if (!file.fail())
			{
				if (a < 3)
				{
					file >> this->pole[0][0];
					a++;
				}
				else
				{
					file >> this->pole[i][j];
					if (i == 9)
					{
						if (j == 9)
							return true;
						j++;
						i = 0;
					}
					else if (i < 9)
						i++;
				}
			}
			else
				return false;
		}
	}
	bool operator>>(string fileName)
	{
		ofstream file;
		int i = 0, j = 0;
		file.open(fileName, ios::app);
		file.clear();
		file.seekp(file.end);
		while (true)
		{
			if (!file.fail())
			{
				file << this->pole[i][j]<<" ";
				if (i == 9)
				{
					if (j == 9)
						return true;
					j++;
					i = 0;
					file << "\n";
				}
				else if (i < 9)
					i++;
			}
			else
				return false;
		}
	}
	void set()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
						pole[i][j] = 1;
					else
						pole[i][j] = 0;
				}
				else
				{
					if (j % 2 == 0)
						pole[i][j] = 0;
					else
						pole[i][j] = 1;
				}
			}
		}
	};
	void setzero()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				pole[i][j] = 0;
			}
		}
	};
	int value(int x, int y)
	{
		return pole[x][y];
	};
	void starting(Board& plansza)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j < 4)
				{
					if (plansza.value(i, j) == 1)
						pole[i][j] = 1;
				}
				else if (j > 5)
				{
					{
						if (plansza.value(i, j) == 1)
							pole[i][j] = 3;
					}
				}
			}
		}
	};
	void change(int x, int y, int value)
	{
		this->pole[x][y] = value;
	};
	void move(Coordinates& draganddrop, Rules* tura)
	{
		int hitx, hity, x, y, diffx, diffy, type;
		x = draganddrop.get(1, 0);
		y = draganddrop.get(1, 1);
		type = this->value(x, y);
		diffx = x - draganddrop.get(1, 2);
		diffy = y - draganddrop.get(1, 3);
		if (type == 1)
		{
			if (*tura==0 || *tura==2)
			{
				if (*tura == 2 && (tura->moveposition(0) != x || tura->moveposition(1) != y))
					return;
				if (abs(diffx) == 1 && abs(diffy) == 1)
				{
					if (this->value(x - diffx, y - diffy) == 0)
					{
						if (*tura == 2)
							return;
						if (diffy < 0)
						{
							this->change(x - diffx, y - diffy, type);
							if (y - diffy == 9)
								this->change(x - diffx, y - diffy, 2);
							this->change(x, y, 0);
							tura->nextturn();
						}
					}
				}
				else if (abs(diffx) == 2 && abs(diffy) == 2)
				{
					if (this->value(x - diffx / 2, y - diffy / 2) == 3 || this->value(x - diffx / 2, y - diffy / 2) == 4)
					{
						if (this->value(x - diffx, y - diffy) == 0)
						{
							this->change(x - diffx, y - diffy, type);
							if (y - diffy == 9)
								this->change(x - diffx, y - diffy, 2);
							this->change(x - diffx / 2, y - diffy / 2, 0);
							this->change(x, y, 0);
							*tura=this->checknext(x - diffx, y - diffy);
							tura->nextposition(x - diffx, y - diffy);
						}
					}
				}
			}
		}
		else if (type == 2)
		{
			if (*tura == 0 || *tura == 2)
			{
				if (*tura == 2 && (tura->moveposition(0) != x || tura->moveposition(1) != y))
					return;
				if (abs(diffx) == abs(diffy))
				{
					if (diffx == 0)
						return;
					if (x - diffx > 9 || x - diffx < 0 || y - diffy>9 || y - diffy < 0)
						return;
					int a, b;
					bool hit = false;
					if (diffx > 0)
						a = -1;
					else
						a = 1;
					if (diffy > 0)
						b = -1;
					else
						b = 1;
					for (int i = 1; i <= abs(diffx); i++)
					{
						if (this->value(x + i * a, y + i * b) == 3 || this->value(x + i * a, y + i * b) == 4)
						{
							if (hit == true)
								return;
							hit = true;
							hitx = x + i * a;
							hity = y + i * b;
							if (hitx == x - diffx)
								return;
						}
						if (this->value(x + i * a, y + i * b) == 1 || this->value(x + i * a, y + i * b) == 2)
							return;
					}

					if (hit == false)
					{
						if (*tura == 2)
							return;
						this->change(x, y, 0);
						this->change(x - diffx, y - diffy, type);
						tura->nextturn();
						return;
					}
					else
					{
						this->change(hitx, hity, 0);
						this->change(x, y, 0);
						this->change(x - diffx, y - diffy, type);
						*tura=this->checknext(x - diffx, y - diffy);
						tura->nextposition(x - diffx, y - diffy);
					}

				}
			}
		}
		else if (type == 3)
		{
			if (*tura == 1 || *tura == 3)
			{
				if (*tura == 3 && (tura->moveposition(0) != x || tura->moveposition(1) != y))
					return;
				if (abs(diffx) == 1 && abs(diffy) == 1)
				{
					if (this->value(x - diffx, y - diffy) == 0)
					{
						if (*tura == 3)
							return;
						if (diffy > 0)
						{
							this->change(x - diffx, y - diffy, type);
							if (y - diffy == 0)
								this->change(x - diffx, y - diffy, 4);
							this->change(x, y, 0);
							tura->nextturn();
						}
					}
				}
				else if (abs(diffx) == 2 && abs(diffy) == 2)
				{
					if (this->value(x - diffx / 2, y - diffy / 2) == 1 || this->value(x - diffx / 2, y - diffy / 2) == 2)
					{
						if (this->value(x - diffx, y - diffy) == 0)
						{
							this->change(x - diffx, y - diffy, type);
							if (y - diffy == 0)
								this->change(x - diffx, y - diffy, 4);
							this->change(x - diffx / 2, y - diffy / 2, 0);
							this->change(x, y, 0);
							*tura=this->checknext(x - diffx, y - diffy);
							tura->nextposition(x - diffx, y - diffy);
						}
					}
				}
			}
		}
		else if (type == 4)
		{
			if (*tura == 1 || *tura == 3)
			{
				if (*tura == 3 && (tura->moveposition(0) != x || tura->moveposition(1) != y))
					return;
				if (abs(diffx) == abs(diffy))
				{
					if (diffx == 0)
						return;
					if (x - diffx > 9 || x - diffx < 0 || y - diffy>9 || y - diffy < 0)
						return;
					int a, b;
					bool hit = false;
					if (diffx > 0)
						a = -1;
					else
						a = 1;
					if (diffy > 0)
						b = -1;
					else
						b = 1;
					for (int i = 1; i <= abs(diffx); i++)
					{
						if (this->value(x + i * a, y + i * b) == 1 || this->value(x + i * a, y + i * b) == 2)
						{
							if (hit == true)
								return;
							hit = true;
							hitx = x + i * a;
							hity = y + i * b;
							if (hitx == x - diffx)
								return;
						}
						if (this->value(x + i * a, y + i * b) == 3 || this->value(x + i * a, y + i * b) == 4)
							return;
					}

					if (hit == false)
					{
						if (*tura == 3)
							return;
						this->change(x, y, 0);
						this->change(x - diffx, y - diffy, type);
						tura->nextturn();
						return;
					}
					else
					{
						this->change(hitx, hity, 0);
						this->change(x, y, 0);
						this->change(x - diffx, y - diffy, type);
						*tura=this->checknext(x - diffx, y - diffy);
						tura->nextposition(x - diffx, y - diffy);
					}

				}
			}
		}
	};
	int countpoints(bool white) 
	{
		int a, b, c, d, number = 0;
		if (white == true)
		{
			a = 1;
			b = 2;
			c = 3;
			d = 4;
		}
		else if (white == false)
		{
			a = 3;
			b = 4;
			c = 1;
			d = 2;
		}
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (this->value(x, y) == a)
					number++;
				else if (this->value(x, y) == b)
					number += 2;
				else if (this->value(x, y) == c)
					number -= 1;
				else if (this->value(x, y) == d)
					number -= 2;
			}
		}
		return number;
	}
	int checknext(int x, int y)
	{
		for (int i = 1; i < 6; i++)
		{
			if (this->value(x, y) == 1)
			{
				switch (i)
				{
				case 1:
					if (x > 1 && y < 8)
					{
						if (this->value(x - 1, y + 1) == 3 || this->value(x - 1, y + 1) == 4)
						{
							if (this->value(x - 2, y + 2) == 0)
								return 2;
						}
					}
					break;
				case 2:
					if (x < 8 && y < 8)
					{
						if (this->value(x + 1, y + 1) == 3 || this->value(x + 1, y + 1) == 4)
						{
							if (this->value(x + 2, y + 2) == 0)
								return 2;
						}
					}
					break;
				case 3:
					if (x < 8 && y>1)
					{
						if (this->value(x + 1, y - 1) == 3 || this->value(x + 1, y - 1) == 4)
						{
							if (this->value(x + 2, y - 2) == 0)
								return 2;
						}
					}
					break;
				case 4:
					if (x > 1 && y > 1)
					{
						if (this->value(x - 1, y - 1) == 3 || this->value(x - 1, y - 1) == 4)
						{
							if (this->value(x - 2, y - 2) == 0)
								return 2;
						}
					}
					break;
				case 5:
					return 1;
					break;
				}
			}	
			else if (this->value(x, y) == 2)
			{
				bool hit;
				int a, b;
				switch (i)
				{
				case 1:
					hit = false;
					for (int j = 1; j < 10; j++)
					{
						a = 1 * j;
						b = 1 * j;
						if (x + a > 9 || y + b > 9)
							break;
						if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						{
							if (hit == true)
								break;
							hit = true;
						}
						else if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
							break;
						else if (this->value(x + a, y + b) == 0)
							if (hit == true)
								return 2;
					}
					break;
				case 2:
					hit = false;
					for (int j = 1; j < 10; j++)
					{
						a = -1 * j;
						b = 1 * j;
						if (x + a < 0 || y + b > 9)
							break;
						if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						{
							if (hit == true)
								break;
							hit = true;
						}
						else if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
							break;
						else if (this->value(x + a, y + b) == 0)
							if (hit == true)
								return 2;
					}
					break;
				case 3:
					hit = false;
					for (int j = 1; j < 10; j++)
					{
						a = 1 * j;
						b = -1 * j;
						if (x + a > 9 || y + b < 0)
							break;
						if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						{
							if (hit == true)
								break;
							hit = true;
						}
						else if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
							break;
						else if (this->value(x + a, y + b) == 0)
							if (hit == true)
								return 2;
					}
					break;
				case 4:
					hit = false;
					for (int j = 1; j < 10; j++)
					{
						a = -1 * j;
						b = -1 * j;
						if (x + a < 0 || y + b < 0)
							break;
						if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						{
							if (hit == true)
								break;
							hit = true;
						}
						else if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
							break;
						else if (this->value(x + a, y + b) == 0)
							if (hit == true)
								return 2;
					}
					break;
				case 5:
					return 1;
					break;
				}
			}
			else if (this->value(x, y) == 3)
			{
				switch (i)
				{
				case 1:
					if (x > 1 && y < 8)
					{
						if (this->value(x - 1, y + 1) == 1 || this->value(x - 1, y + 1) == 2)
						{
							if (this->value(x - 2, y + 2) == 0)
								return 3;
						}
					}
					break;
				case 2:
					if (x < 8 && y < 8)
					{
						if (this->value(x + 1, y + 1) == 1 || this->value(x + 1, y + 1) == 2)
						{
							if (this->value(x + 2, y + 2) == 0)
								return 3;
						}
					}
					break;
				case 3:
					if (x < 8 && y > 1)
					{
						if (this->value(x + 1, y - 1) == 1 || this->value(x + 1, y - 1) == 2)
						{
							if (this->value(x + 2, y - 2) == 0)
								return 3;
						}
					}
					break;
				case 4:
					if (x > 1 && y > 1)
					{
						if (this->value(x - 1, y - 1) == 1 || this->value(x - 1, y - 1) == 2)
						{
							if (this->value(x - 2, y - 2) == 0)
								return 3;
						}
					}
					break;
				case 5:
					return 0;
					break;
				}
			}
			else if (this->value(x, y) == 4)
			{
			bool hit;
			int a, b;
			switch (i)
			{
			case 1:
				hit = false;
				for (int j = 1; j < 10; j++)
				{
					a = 1 * j;
					b = 1 * j;
					if (x + a > 9 || y + b > 9)
						break;
					if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
					{
						if (hit == true)
							break;
						hit = true;
					}
					else if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						break;
					else if (this->value(x + a, y + b) == 0)
						if (hit == true)
							return 3;
				}
				break;
			case 2:
				hit = false;
				for (int j = 1; j < 10; j++)
				{
					a = -1 * j;
					b = 1 * j;
					if (x + a < 0 || y + b > 9)
						break;
					if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
					{
						if (hit == true)
							break;
						hit = true;
					}
					else if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						break;
					else if (this->value(x + a, y + b) == 0)
						if (hit == true)
							return 3;
				}
				break;
			case 3:		
				hit = false;
				for (int j = 1; j < 10; j++)
				{
					a = 1 * j;
					b = -1 * j;
					if (x + a > 9 || y + b < 0)
						break;
					if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
					{
						if (hit == true)
							break;
						hit = true;
					}
					else if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						break;
					else if (this->value(x + a, y + b) == 0)
						if (hit == true)
							return 3;
				}
				break;
			case 4:
				hit = false;
				for (int j = 1; j < 10; j++)
				{
					a = -1 * j;
					b = -1 * j;
					if (x + a < 0 || y + b < 0)
						break;
					if (this->value(x + a, y + b) == 1 || this->value(x + a, y + b) == 2)
					{
						if (hit == true)
							break;
						hit = true;
					}
					else if (this->value(x + a, y + b) == 3 || this->value(x + a, y + b) == 4)
						break;
					else if (this->value(x + a, y + b) == 0)
						if (hit == true)
							return 3;
				}
				break;
			case 5:
				return 0;
				break;
			}
			}
		}
	}
	int countcolor(bool white)
	{
		int a, b, number=0;
		if (white == true)
		{
			a = 1;
			b = 2;
		}
		else if (white == false)
		{
			a = 3;
			b = 4;
		}
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (this->value(x, y) == a || this->value(x, y) == b)
					number++;
			}
		}
		return number;
	}
	bool checkifstuck(bool white)
	{
		int all, stuck = 0;
		all = this->countcolor(white);
		if (all == 0)
			return true;
		bool a = false;
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				a = false;
				if (this->value(x, y) == 1)
				{
					if ((x < 9 && x > 0) && y < 9)
					{
						if ((this->value(x + 1, y + 1) == 0 || this->value(x - 1, y + 1) == 0) && a == false)
							a = true;
					}
					else if (x == 0 && y < 9)
					{
						if (this->value(x + 1, y + 1) == 0 && a == false)
							a = true;
					}
					else if (x == 9 && y < 9)
					{
						if (this->value(x - 1, y + 1) == 0 && a == false)
							a = true;
					}
					if (2 == this->checknext(x, y) && a == false)
					{
						a = true;
					}
					if (a == false)
						stuck++;
				}
				else if (this->value(x, y) == 2)
				{
					a = false;

					if ((x < 9 && x > 0) && (y < 9 && y > 0))
					{
						if ((this->value(x + 1, y + 1) == 0 || this->value(x - 1, y + 1) == 0 || this->value(x + 1, y - 1) == 0 || this->value(x - 1, y - 1) == 0) && a == false)
							a = true;
					}
					else if (x == 0 && (y < 9 && y > 0))
					{
						if ((this->value(x + 1, y + 1) == 0 || this->value(x + 1, y - 1) == 0) && a == false)
							a = true;
					}
					else if (x == 9 && (y < 9 || y > 0))
					{
						if ((this->value(x - 1, y + 1) == 0 || this->value(x - 1, y - 1) == 0) && a == false)
							a = true;
					}
					else if (y == 9 && (x < 9 || x > 0))
					{
						if ((this->value(x - 1, y - 1) == 0 || this->value(x + 1, y - 1) == 0) && a == false)
							a = true;
					}
					else if (y == 0 && (x < 9 && x > 0))
					{
						if ((this->value(x - 1, y + 1) == 0 || this->value(x + 1, y + 1) == 0) && a == false)
							a = true;
					}
					else if (x == 0 && y == 0)
					{
						if (this->value(x + 1, y + 1) == 0 && a == false)
							a = true;
					}
					else if (x == 0 && y == 9)
					{
						if (this->value(x + 1, y - 1) == 0 && a == false)
							a = true;
					}
					else if (x == 9 && y == 0)
					{
						if (this->value(x - 1, y + 1) == 0 && a == false)
							a = true;
					}
					else if (x == 9 && y == 9)
					{
						if (this->value(x - 1, y - 1) == 0 && a == false)
							a = true;
					}
					if (2 == this->checknext(x, y) && a == false)
					{
						a = true;
					}
					if (a == false)
						stuck++;
				}
				else if (this->value(x, y) == 3)
				{
					if ((x < 9 && x>0) && y > 0)
					{
						if ((this->value(x + 1, y - 1) == 0 || this->value(x - 1, y - 1) == 0) && a == false)
							a = true;
					}
					else if (x == 0 && y > 0)
					{
						if (this->value(x + 1, y - 1) == 0 && a == false)
							a = true;
					}
					else if (x == 9 && y > 0)
					{
						if (this->value(x - 1, y - 1) == 0 && a == false)
							a = true;
					}
					if (3 == this->checknext(x, y) && a == false)
					{
						a = true;
					}
					if (a == false)
						stuck++;
				}
				else if (this->value(x, y) == 4)
				{
				a = false;

				if ((x < 9 && x > 0) && (y < 9 && y > 0))
				{
					if ((this->value(x + 1, y + 1) == 0 || this->value(x - 1, y + 1) == 0 || this->value(x + 1, y - 1) == 0 || this->value(x - 1, y - 1) == 0) && a == false)
						a = true;
				}
				else if (x == 0 && (y < 9 && y > 0))
				{
					if ((this->value(x + 1, y + 1) == 0 || this->value(x + 1, y - 1) == 0) && a == false)
						a = true;
				}
				else if (x == 9 && (y < 9 || y > 0))
				{
					if ((this->value(x - 1, y + 1) == 0 || this->value(x - 1, y - 1) == 0) && a == false)
						a = true;
				}
				else if (y == 9 && (x < 9 || x > 0))
				{
					if ((this->value(x - 1, y - 1) == 0 || this->value(x + 1, y - 1) == 0) && a == false)
						a = true;
				}
				else if (y == 0 && (x < 9 && x > 0))
				{
					if ((this->value(x - 1, y + 1) == 0 || this->value(x + 1, y + 1) == 0) && a == false)
						a = true;
				}
				else if (x == 0 && y == 0)
				{
					if (this->value(x + 1, y + 1) == 0 && a == false)
						a = true;
				}
				else if (x == 0 && y == 9)
				{
					if (this->value(x + 1, y - 1) == 0 && a == false)
						a = true;
				}
				else if (x == 9 && y == 0)
				{
					if (this->value(x - 1, y + 1) == 0 && a == false)
						a = true;
				}
				else if (x == 9 && y == 9)
				{
					if (this->value(x - 1, y - 1) == 0 && a == false)
						a = true;
				}
				if (3 == this->checknext(x, y) && a == false)
				{
					a = true;
				}
				if (a == false)
					stuck++;
				}
			}
		}
		if (stuck == all)
			return true;
		else
			return false;
	}
};