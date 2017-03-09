// gameCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <conio.h>

#define KEY_UP 72		// systemowe numery klawiszy
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


enum ObjectType
{
	Player = 0,
	Enemy = 1,
	Treasure = 2
};

struct Vector
{
	int x, y;
};

struct GameObject
{
	Vector pos;
	ObjectType type;
};





GameObject player;
GameObject enemies[3];
GameObject treasures[3];

const int mapSize = 10;
const string borderSymbol = " #";
const string blankSymbol = "  ";
const string playerSymbol = " A";

void drawMap()
{
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			if (player.pos.x == x&& player.pos.y ==y)
			{
				cout << playerSymbol;
			}
			else if (x == 0 || y == 0 || x == (mapSize - 1) || y == (mapSize - 1))
			{
				cout <<borderSymbol;
			}
			else
			{
				cout << blankSymbol;

			}
		}
		cout << endl;
	}
}

void initializeObjects()
{
	player.pos.x = 1;
	player.pos.y = 1;
	player.type = ObjectType::Player;	// pokazuje, ze typ gracza jest playerem
}

Vector getInput()
{
	int input;
	Vector output;
	output.x = 0;
	output.y = 0;	// struktury musza byc przed uzyciem zainicjalizowane
	input = _getch();
	switch (input)
	{
	case KEY_UP:
		output.y = -1;
		break;
	case KEY_DOWN:
		output.y = 1;
		break;
	case KEY_LEFT:
		output.x = -1;
		break;
	case KEY_RIGHT:
		output.x = 1;
		break;
	default:
		break;
	}
	return output;
}
void movePlayer()
{
	Vector input = getInput();
	if (player.pos.x + input.x != 0&& player.pos.x + input.x != (mapSize-1))
	{
		player.pos.x += input.x; // rowna sie ten pierwszy dodac ten drugi
	}
	if (player.pos.y + input.y != 0 && player.pos.y + input.y != (mapSize - 1))
	{
		player.pos.y += input.y;
	}
}
int main()
{
	srand(time(NULL));

	initializeObjects();
	while (true)	// petla nieskonczona
	{
		drawMap();
		movePlayer();
		system("cls");	// bedzie za kazdym razem czyscil ekran

	}

	system("pause");
    return 0;
}

