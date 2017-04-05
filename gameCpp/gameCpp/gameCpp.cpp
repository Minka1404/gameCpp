// gameCpp.cpp : Defines the entry point for the console application.
//zmiana: mowic i tlumaczyc i czy dobrze


#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <conio.h>
#include <vector>
#include<windows.h>

using namespace std;


#define KEY_UP 72		// systemowe numery klawiszy
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define pi 3.14

using namespace std;


enum ObjectType
{
	Player = 0,
	Enemy = 1,
	Treasure = 2
};

struct Point
{
	int x, y;
};

struct GameObject
{
	GameObject(int x, int y, ObjectType type)	// zmiana - po co to wlasciwie?
	{
		pos.x = x;
		pos.y = y;
		this->type = type;
	}
	Point pos;
	ObjectType type;
};

vector<GameObject> gameObjects;

#pragma region initialized data

const int mapSize = 12;
const int enemyNumber = 2;
const int treasureNumber = 2;

const string borderSymbol = " #";
const string blankSymbol = "  ";
const string playerSymbol = " P";
const string enemySymbol = " !";
const string treasureSymbol = " X";

#pragma endregion


#pragma region switch drawMap

void drawMap()
{
	string mapa[mapSize][mapSize];
	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			if (x == 0 || y == 0 || x == (mapSize - 1) || y == (mapSize - 1))
				mapa[x][y] = borderSymbol;
			else
				mapa[x][y] = blankSymbol;
		}
	}

	for (int w = 0; w < gameObjects.size(); w++)	// zmiana: czy jesli chce miec 2 skarby na mapie to musze zainicjowac skarb1, skarb2? czy moge da liczbe skarbow do zainicjowania, ewentualnie zrobic wektor skarbow(?)
	{
		switch (gameObjects[w].type)
		{
		case ObjectType::Enemy:
			mapa[gameObjects[w].pos.x][gameObjects[w].pos.y] = enemySymbol;
			break;
		case ObjectType::Player:
			mapa[gameObjects[w].pos.x][gameObjects[w].pos.y] = playerSymbol;
			break;
		case ObjectType::Treasure:
			mapa[gameObjects[w].pos.x][gameObjects[w].pos.y] = treasureSymbol;	//zmiana
			break;
		}
	}
	
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			cout << mapa[x][y];
		}
		cout << endl;
	}
}
#pragma endregion


void initializeObjects()
{		//zmiana: jak sprawdzac czy wspolrzedne sa juz zajete
	gameObjects.push_back(GameObject(1,1, ObjectType::Player));
	
	for (int i = 0; i < enemyNumber; i++)	//zmiana	trzeba zrobic strukture, do ktorej bede sie odwolywac, zeby sprawdzic ilosc obiektow, zeby nie robic zmiennych globalnych
	{
		int a, b;
		a = rand() % (mapSize - 3) + 2;		// jak tutaj odwolac sie do punktu (Enemy.pos.x; Enemy.pos.y) zamiast tworzyc nowe zmienne i jakim cudem w drawMap tak czy tak rysuje odwolujac sie do Enemy.pos.x/y
		b = rand() % (mapSize - 3) + 2;

		gameObjects.push_back(GameObject(a, b, ObjectType::Enemy));
		cout << a << " " << b << endl;	//zmiana: dlaczego znowu na odwrot to robi, skoro drawMap jest ok, jednak x pierwszy, dlaczego?? wtf
		Sleep(2000);
	}
//zmiana - dlaczego nie moge tak zrobic:
//		gameObjects[3].pos.x = rand() % (mapSize - 3) + 3;
//		gameObjects[3].pos.y = rand() % (mapSize - 3) + 3;
	gameObjects.push_back(GameObject(8/*gameObjects[3].pos.x*/, 2/*gameObjects[3].pos.y*/, ObjectType::Treasure));	// zmiana: dlaczego nie Treasure.pos.x np


}

Point getInput()
{
	int input;
	Point output;
	output.x = 0;
	output.y = 0;	// struktury musza byc przed uzyciem zainicjalizowane
	input = _getch(); // jesli nie wiem jaka wartosc ma klawisz to robie input = _getch() i wywalam input na ekran

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
	Point input = getInput();
	if (gameObjects[0].pos.x + input.x != 0 && gameObjects[0].pos.x + input.x != (mapSize - 1))
	{
		gameObjects[0].pos.x += input.x; // rowna sie ten pierwszy dodac ten drugi
	}
	if (gameObjects[0].pos.y + input.y != 0 && gameObjects[0].pos.y + input.y != (mapSize - 1))
	{
		gameObjects[0].pos.y += input.y;
	}
	if (gameObjects[0].pos.x == gameObjects[1].pos.x && gameObjects[0].pos.y == gameObjects[1].pos.y)
	{
		cout << "Padles" << endl;
		Sleep(1000);
		//zmiana: jak zrobic, zeby tutaj program sie konczyl

	}
	if (gameObjects[0].pos.x == gameObjects[3].pos.x && gameObjects[0].pos.y == gameObjects[3].pos.y)
	{
		cout << "Zebrales skarb" << endl;
		Sleep(1000);
	//	gameObjects[2].pos.x = -100;
	//	gameObjects[2].pos.y = -100;  // zlo sie dzieje
		//zmiana: jak zrobic, zeby skarb znikal, czy da sie nadac tej pozycji jakies wartosc spoza skali (nie da), np mapSize+10, zeby tego w ogole nie wyswietlalo
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



// zeby nie stawaly na tym samym miejscu jesli pozycje takie same to losuj jeszcze raz (i--)