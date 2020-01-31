#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Pawn
{
	Sprite pionek;
	Texture w1, w2, b1, b2;
public:
	void load()
	{
		w1.loadFromFile("w1.png");
		w2.loadFromFile("w2.png");
		b1.loadFromFile("b1.png");
		b2.loadFromFile("b2.png");
	};
	void set(int x)
	{
		if (x == 1)
			this->pionek.setTexture(w1);
		else if (x == 2)
			this->pionek.setTexture(w2);
		else if (x == 3)
			this->pionek.setTexture(b1);
		else if (x == 4)
			this->pionek.setTexture(b2);
	};
	void setposition(Vector2f coordinates)
	{
		this->pionek.setPosition(coordinates);
	};
	Sprite get()
	{
		return this->pionek;
	};
};