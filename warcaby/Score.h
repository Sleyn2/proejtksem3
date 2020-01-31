#pragma once

#include <string>
#include <fstream>

using namespace std;

class Score
{
public:
	string name;
	int points;
	Score(string newname, int value)
	{
		this->name = newname;
		this->points = value;
	}
};

struct element {
	element* next;
	Score pkt;
	element(const Score & current) :pkt(current), next(nullptr) {}
};

class List
{
	element* head;
	int size;
public:
	List() :head(nullptr), size(0) {};
	void operator<<(char* fileName)
	{
		string name;
		ifstream file;
		int i = 0, points;
		file.open(fileName, ios::in);

		if (!file.fail())
		{
			int j;
			file >> j;
			for (int n = 0; n < j; n++)
			{
				file >> name >> points;
				Score* mem = new Score(name, points);
				element* curr = new element(*mem);
				this->operator+=(curr);
			}
		}
		else
			return;
	}
	void operator>>(char* fileName)
	{
		element* temp = this->head;
		ofstream file;
		file.open(fileName, ios::trunc);
		if (!file.fail())
		{
			file << this->size;
			for (int i = 0; i < this->size; i++)
			{
				if (i > 0)
				{
					temp = temp->next;
				}
				file <<"\n" << temp->pkt.name << " " << temp->pkt.points;
			}
		}
	}
	void operator+=(element* newelement)
	{
		if (this->head == nullptr)
		{
			this->head = newelement;
			this->size++;
		}
		else if (this->head->pkt.points <= newelement->pkt.points)
		{
			if (this->size < 10)
			{
				this->size++;
				newelement->next = this->head;
				this->head = newelement;
			}
			else
			{
				element* temp = this->head;
				for (int i = 2; i < 10; i++)
					temp = temp->next;
				temp->next == nullptr;
				newelement->next = this->head;
				this->head = newelement;
			}
		}
		else if (this->head->pkt.points > newelement->pkt.points)
		{
			bool a = true;
			element* temp = this->head;
			while (a)
			{
				if (temp->next == nullptr)
				{
					temp->next = newelement;
					newelement->next = nullptr;
					a = false;
				}
				else if (temp->next->pkt.points <= newelement->pkt.points)
				{
					newelement->next = temp->next;
					temp->next = newelement;
					a = false;
				}
				else if (temp->next->pkt.points > newelement->pkt.points)
				{
					temp = temp->next;
				}
			}
			if (this->size < 10)
				this->size++;
			else
			{
				temp = this->head;
				for (int i = 2; i < 10; i++)
					temp = temp->next;
				temp->next == nullptr;
			}
		}
	}
	int ammount()
	{
		return this->size;
	}
	string name(int i)
	{
		element* temp = this->head;
		for (int j = 0; j < i; j++)
		{
			temp = temp->next;
		}
		return temp->pkt.name;
	}
	int value(int i)
	{
		element* temp = this->head;
		for (int j = 0; j < i; j++)
		{
			temp = temp->next;
		}
		return temp->pkt.points;
	}
};