#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "Coordinates.h"
#include "Board.h"
#include "Rules.h"
#include "Score.h"

using namespace sf;
using namespace std;

void menutexts(RenderWindow& okno);
void drag(Coordinates& draganddrop, Rules* zasady, Board* pionki);
void selecttexts(RenderWindow& okno, bool error);
void manualtexts(RenderWindow& okno);
void scoretexts(RenderWindow& okno, List* scoreboard);
void gametexts(RenderWindow& okno, Rules tura);
void savetexts(RenderWindow& okno, bool white, string name);
void preparation(RenderWindow& okno, bool error);
void gamedisplay(Board plansza, Board pionki, Rules zasady);
void menu(bool win, bool white, int points);
