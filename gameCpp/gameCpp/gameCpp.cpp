// gameCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct GameObject
{
	Vector pos;

};

struct Vector
{
	int x, y;
};

enum ObjectType
{
	Player = 0,
	Enemy = 1,
	Treasure = 2
};

GameObject player;
GameObject enemies[3];
GameObject treasures[3];


int main()
{
    return 0;
}

