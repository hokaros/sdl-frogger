#pragma once
#include "Killing.h"
#include "TurtleGroup.h"
#include "MovingFree.h"
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define ROW_HEIGHT 32
class Level
{
public:
	SDL_Surface* background;
	SDL_Surface* screen;
	int mapTopBorder;
	int mapRightBorder;
	int mapBottomBorder;
	int mapLeftBorder;

	//przeszkody
	unsigned short cars1Count;
	Killing** cars1;
	unsigned short cars2Count;
	Killing** cars2;
	unsigned short cars3Count;
	Killing** cars3;
	unsigned short cars4Count;
	Killing** cars4;
	unsigned short cars5Count;
	Killing** cars5;

	unsigned short turtleGroups1Count;
	TurtleGroup** turtleGroups1;
	unsigned short turtleGroups2Count;
	TurtleGroup** turtleGroups2;

	unsigned short logs1Count;
	Attachable** logs1;
	unsigned short logs2Count;
	Attachable** logs2;
	unsigned short logs3Count;
	Attachable** logs3;

	MovingFree* player;

	Level(SDL_Surface* screen);
	~Level();
	void LoadPlayer();
	//wczytuje tablic� samochod�w na row rz�dzie ulicy w liczbie count, pr�dko�ci velocity i odst�pie gap
	void LoadCars(unsigned short row, unsigned short count, Vector velocity, int gap);
	void LoadTurtleGroups(unsigned short riverRow, unsigned short count, Vector velocity, int gap);
	void LoadLogs(unsigned short riverRow, unsigned short count, Vector velocity, int gap);
	//poruszanie przeszkodami
	void MoveLogs(bool& attached, double deltaTime);
	void MoveCars(bool& killed, double deltaTime);
};

