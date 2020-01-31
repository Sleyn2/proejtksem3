#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <cstdio>
#include "My_Font.h"
#include "Pawn.h"
#include "functions.h"
#include "Rules.h"
#include "Score.h"
#include "Save.h"


using namespace sf;
using namespace std;


void drag(Coordinates &draganddrop, Rules *zasady, Board *pionki)
{
	draganddrop.count();
	pionki->move(draganddrop, zasady);
	draganddrop.preset();
}

void selecttexts(RenderWindow& okno, bool error)
{
	My_Font napis;
	napis.preset();
	napis="Starting a new game will";
	napis.setposition(Vector2f(120, 30));
	okno.draw(napis.get());
	napis="overwrite an existing one.";
	napis.setposition(Vector2f(120, 100));
	okno.draw(napis.get());
	napis="New Game";
	napis.setposition(Vector2f(150, 400));
	okno.draw(napis.get());
	if (error == false)
		napis="Load";
	else if (error == true)
		napis="No file";
	napis.setposition(Vector2f(700, 400));
	okno.draw(napis.get());
}

void menutexts(RenderWindow& okno)
{
	My_Font napis;
	napis.preset();
	napis="MAIN MENU";
	napis.setposition(Vector2f(330, 75));
	okno.draw(napis.get());
	napis="START";
	napis.setposition(Vector2f(400, 275));
	okno.draw(napis.get());
	napis="MANUAL";
	napis.setposition(Vector2f(370, 350));
	okno.draw(napis.get());
	napis="HIGH SCORE";
	napis.setposition(Vector2f(315, 425));
	okno.draw(napis.get());
	napis="EXIT";
	napis.setposition(Vector2f(420, 500));
	okno.draw(napis.get());
}

void manualtexts(RenderWindow& okno)
{
	My_Font napis;
	napis.preset();
	okno.clear(Color(100, 123, 230));
	napis="Game rules:";
	napis.setposition(Vector2f(100, 60));
	okno.draw(napis.get());
	napis="back to menu";
	napis.setposition(Vector2f(100, 500));
	okno.draw(napis.get());
	napis.setsize(30);
	napis = "White starts, every player makes 1 move, except a";
	napis.setposition(Vector2f(50, 130));
	okno.draw(napis.get());
	napis = "situation when someone take down other player's";
	napis.setposition(Vector2f(50, 170));
	okno.draw(napis.get());
	napis = "pawn, then he can make next hit when it's available.";
	napis.setposition(Vector2f(50, 210));
	okno.draw(napis.get());
	napis = "Game ends when some player has no more moves, or";
	napis.setposition(Vector2f(50, 250));
	okno.draw(napis.get());
	napis = "pawns available.";
	napis.setposition(Vector2f(50, 290));
	okno.draw(napis.get());

	okno.display();
}

void scoretexts(RenderWindow& okno, List* scoreboard)
{
	My_Font napis;
	napis.preset();
	okno.clear(Color(100, 123, 230));
	napis = "High Score:";
	napis.setposition(Vector2f(350, 10));
	okno.draw(napis.get());
	napis = "back to menu";
	napis.setposition(Vector2f(100, 500));
	okno.draw(napis.get());
	for (int i = 0; i < scoreboard->ammount(); i++)
	{
		switch (i)
		{
		case 0:
			napis = "1: ";
			napis.setposition(Vector2f(150, 80));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 80));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 80));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 80));
			okno.draw(napis.get());
			break;
		case 1:
			napis = "2: ";
			napis.setposition(Vector2f(150, 120));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 120));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 120));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 120));
			okno.draw(napis.get());
			break;
		case 2:
			napis = "3: ";
			napis.setposition(Vector2f(150, 160));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 160));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 160));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 160));
			okno.draw(napis.get());
			break;
		case 3:
			napis = "4: ";
			napis.setposition(Vector2f(150, 200));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 200));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 200));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 200));
			okno.draw(napis.get());
			break;
		case 4:
			napis = "5: ";
			napis.setposition(Vector2f(150, 240));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 240));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 240));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 240));
			okno.draw(napis.get());
			break;
		case 5:
			napis = "6: ";
			napis.setposition(Vector2f(150, 280));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 280));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 280));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 280));
			okno.draw(napis.get());
			break;
		case 6:
			napis = "7: ";
			napis.setposition(Vector2f(150, 320));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 320));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 320));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 320));
			okno.draw(napis.get());
			break;
		case 7:
			napis = "8: ";
			napis.setposition(Vector2f(150, 360));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 360));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 360));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 360));
			okno.draw(napis.get());
			break;
		case 8:
			napis = "9: ";
			napis.setposition(Vector2f(150, 400));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 400));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 400));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 400));
			okno.draw(napis.get());
			break;
		case 9:
			napis = "10: ";
			napis.setposition(Vector2f(150, 440));
			okno.draw(napis.get());
			napis = scoreboard->name(i);
			napis.setposition(Vector2f(210, 440));
			okno.draw(napis.get());
			napis = scoreboard->value(i);
			napis.setposition(Vector2f(580, 440));
			okno.draw(napis.get());
			napis = "    points";
			napis.setposition(Vector2f(600, 440));
			okno.draw(napis.get());
			break;
		}
	}
	okno.display();
}

void gametexts(RenderWindow& okno, Rules tura)
{
	My_Font napis;
	napis.preset();
	if (tura == 0)
		napis="White's turn";
	else if (tura == 1)
		napis="Black's turn";
	else if (tura == 2)
		napis="White's next turn";
	else if (tura == 3)
		napis="Black's next turn";
	napis.setposition(Vector2f(320, 25));
	okno.draw(napis.get());
	napis="back to menu";
	napis.setposition(Vector2f(150, 930));
	okno.draw(napis.get());
	napis = "exit";
	napis.setposition(Vector2f(700, 930));
	okno.draw(napis.get());
}

void savetexts(RenderWindow& okno, bool white, string name)
{
	My_Font napis;
	napis.preset();
	napis = "submit";
	napis.setposition(Vector2f(370, 450));
	okno.draw(napis.get());
	if (white == true)
		napis = "White player wins!";
	else if (white == false)
		napis = "Black player wins!";
	napis.setposition(Vector2f(150, 50));
	okno.draw(napis.get());
	napis = "Write your name for scoreboard:";
	napis.setposition(Vector2f(50, 130));
	okno.draw(napis.get());
	napis = name;
	napis.setposition(Vector2f(200, 300));
	okno.draw(napis.get());
}

void preparation(RenderWindow& okno, bool error)
{
	Event key;
	while (okno.isOpen())
	{
		while (okno.pollEvent(key))
		{
			if (key.type == Event::KeyPressed && key.key.code == Keyboard::Escape)
				okno.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (key.mouseButton.x < 455 && key.mouseButton.x>150 && key.mouseButton.y < 450 && key.mouseButton.y>400)
			{
				okno.close();
				Board plansza, pionki;
				Rules current;
				current = 0;
				plansza.set();
				pionki.setzero();
				pionki.starting(plansza);
				gamedisplay(plansza, pionki, current);
			}
			else if (key.mouseButton.x < 850 && key.mouseButton.x>700 && key.mouseButton.y < 450 && key.mouseButton.y>400)
			{					
				Rules current;				
				Board plansza, pionki;
				char fileName[10] = "save.data";
				pionki.setzero();
				if (current << (fileName) == false)
					preparation(okno, true);
				pionki << (fileName);
				okno.close();
				plansza.set();
				gamedisplay(plansza, pionki, current);
			}
		}
		okno.clear(Color(100, 123, 230));
		selecttexts(okno, error);
		okno.display();
	}

}

void menu(bool win, bool white, int points)
{
	Event key, last;
	string name;
	bool open = true, gotone = false;
	RenderWindow okno(VideoMode(1000, 600), "Draughts game");
	while (okno.isOpen())
	{
		if (win == true)
		{
			char fileName[16] = "scoreboard.data";
			List scoreboard;
			scoreboard << (fileName);
			open = true;
			while (open)
			{
				
				okno.pollEvent(key);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (key.mouseButton.x < 530 && key.mouseButton.x>370 && key.mouseButton.y < 500 && key.mouseButton.y>450)
						open = false;
				}
				if (key.type == sf::Event::TextEntered)
				{
					if (gotone == false)
					{
						name += key.text.unicode;
						last = key;
						gotone = true;
					}
					if (last.text.unicode != key.text.unicode && gotone == true)
					{
						gotone = false;
					}
				}
				okno.clear(Color(100, 123, 230));
				savetexts(okno, white, name);
				okno.display();
			}
			win = false;
			Score* mem = new Score(name, points);
			element* temp = new element(*mem);
			scoreboard += temp;
			scoreboard >> (fileName);
		}
		while (okno.pollEvent(key))
		{
			if (key.type == Event::KeyPressed && key.key.code == Keyboard::Escape)
				okno.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (key.mouseButton.x < 570 && key.mouseButton.x>400 && key.mouseButton.y < 325 && key.mouseButton.y>275)
			{
				preparation(okno, false);
			}
			else if (key.mouseButton.x < 610 && key.mouseButton.x>370 && key.mouseButton.y < 400 && key.mouseButton.y>350)
			{
				open = true;
				while (open)
				{
					okno.pollEvent(key);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						if (key.mouseButton.x < 500 && key.mouseButton.x>100 && key.mouseButton.y < 550 && key.mouseButton.y>500)
							open = false;
					}
					manualtexts(okno);
				}
			}
			else if (key.mouseButton.x < 700 && key.mouseButton.x>315 && key.mouseButton.y < 480 && key.mouseButton.y>425)
			{
				char fileName[16] = "scoreboard.data";
				List scoreboard;
				scoreboard << (fileName);
				open = true;
				while (open)
				{
					okno.pollEvent(key);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						if (key.mouseButton.x < 500 && key.mouseButton.x>100 && key.mouseButton.y < 550 && key.mouseButton.y>500)
							open = false;
					}
					scoretexts(okno, &scoreboard);
				}
				scoreboard >> (fileName);
			}
			else if (key.mouseButton.x < 560 && key.mouseButton.x>420 && key.mouseButton.y < 550 && key.mouseButton.y>500)
			{
				okno.close();
			}
		}
		okno.clear(Color(100, 123, 230));
		menutexts(okno);
		okno.display();
	}
}

void gamedisplay(Board plansza, Board pionki, Rules zasady)
{
	Pawn pionek;
	Coordinates draganddrop;
	RectangleShape kwadrat(Vector2f(80, 80));
	bool a, dragging = false, checked = false;
	RenderWindow okno(VideoMode(1000, 1000), "warcaby");
	okno.setPosition(Vector2i(460, 0));
	pionek.load();
	char fileName[10] = "save.data";
	while (okno.isOpen())
	{
		Event key;
		if (checked == false)
		{
			a = pionki.checkifstuck(true);
			if (a == true)
			{				
				remove(fileName);
				int points = pionki.countpoints(true);
				(true, pionki.countcolor(true));
				okno.close();
				menu(true, true, points);
			}
			a = pionki.checkifstuck(false);
			if (a == true)
			{		
				remove(fileName);
				int points = pionki.countpoints(false);
				(true, pionki.countcolor(false));
				okno.close();
				menu(true, false, points);
			}
			checked = true;
		}
		while (okno.pollEvent(key))
		{
			if (key.type == Event::KeyPressed && key.key.code == Keyboard::Escape)
			{
				zasady >> (fileName);
				pionki >> (fileName);
				okno.close();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (key.mouseButton.x < 560 && key.mouseButton.x>150 && key.mouseButton.y < 990 && key.mouseButton.y>930)
				{
					okno.close();
					zasady >> (fileName);
					pionki >> (fileName);
					menu(false, false, 0);
				}
				else if (key.mouseButton.x < 810 && key.mouseButton.x>700 && key.mouseButton.y < 990 && key.mouseButton.y>930)
				{
					okno.close();
					zasady >> (fileName);
					pionki >> (fileName);
				}
			}
			switch (key.type)
			{
			case Event::MouseButtonPressed:
				if (key.mouseButton.button == Mouse::Left)
				{
					draganddrop.preset();
					draganddrop.set(0, key.mouseButton.x - 100);
					draganddrop.set(1, key.mouseButton.y - 100);
					dragging = true;
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (key.mouseButton.button == Mouse::Left)
				{
					if (dragging)
					{
						draganddrop.set(2, key.mouseButton.x - 100);
						draganddrop.set(3, key.mouseButton.y - 100);
						dragging = false;
						checked = false;
						if (draganddrop.get(0, 0) < 900 && draganddrop.get(0, 1) < 900 && draganddrop.get(0, 1) < 900 && draganddrop.get(0, 1) < 900)
							drag(draganddrop, &zasady, &pionki);
					}
				}
				break;
			};
		}

		okno.clear(Color(0, 123, 230));
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				kwadrat.setPosition(Vector2f((i + 1) * 80 + 20, (j + 1) * 80 + 20));
				if (plansza.value(i, j) == 0)
					kwadrat.setFillColor(Color(255, 229, 180));
				else if (plansza.value(i, j) == 1)
					kwadrat.setFillColor(Color(99, 51, 9));
				okno.draw(kwadrat);
				if (pionki.value(i, j) != 0)
				{
					pionek.setposition(Vector2f((i + 1) * 80 + 20, (j + 1) * 80 + 20));
					pionek.set(pionki.value(i, j));
					okno.draw(pionek.get());
				}
			}
		}
		gametexts(okno, zasady);
		okno.display();
	}
}