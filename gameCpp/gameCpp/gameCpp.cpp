// gameCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>

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

};





GameObject player;
GameObject enemies[3];
GameObject treasures[3];

int mapSize = 10;

void drawMap()
{
	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			if (x == 0 || y == 0 || x == (mapSize - 1) || y == (mapSize - 1))
			{
				cout << " #";
			}
			else
			{
				cout << "  ";

			}
		}
		cout << endl;
	}
}

int main()
{

	while (true)	// petla nieskonczona
	{
		drawMap();
		system("pause");
		system("cls");	// bedzie za kazdym razem czyscil ekran

	}

	system("pause");
    return 0;
}

