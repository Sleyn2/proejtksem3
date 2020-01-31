#pragma once
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class My_Font
{
	Text style;
	Font menu;
public:
	void operator=(string text)
	{
		style.setString(text);
	}
	void operator=(int number)
	{
		char buffer[10];
		style.setString(itoa(number, buffer, 10));
	}
	void preset()
	{
		menu.loadFromFile("menu.ttf");
		style.setFont(menu);
		style.setCharacterSize(50);
		style.setColor(Color::Black);
	};
	void setsize(int size)
	{
		this->style.setCharacterSize(size);
	};
	void setposition(Vector2f position)
	{
		style.setPosition(position);
	};
	Text get()
	{
		return this->style;
	};
};