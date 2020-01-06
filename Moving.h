#pragma once
#include "Area.h"

enum class Direction { None, Up, Right, Down, Left };
typedef struct velocity {
	int pixelsPerSecond;
	Direction direction;
} Velocity;

const Velocity ZERO_VELOCITY = { 0, Direction::None };

class Moving :
	public Area
{
protected:
	Velocity velocity;
	/*
	Obiekt nie mo�e si� poruszy� o nieca�kowit� liczb� pikseli,
	dlatego cz�ci po przecinku s� przechowywane w zmiennej  */
	double pixelsToMove; //zmienna przechowuj�ca cz�ci nieca�kowite pixeli
public:
	Moving(Area a, Velocity velocity);
	void Move(double deltaTime);
};

