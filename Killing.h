#pragma once
#include "MovingHor.h"
class Killing :
	public MovingHor
{
public:
	//�miertelny obszar podany wzgl�dem pozycji obiektu MovingHor
	rectangle lethalArea;
	Killing(rectangle lethalArea, Area a, Vector velocity, int leftBoundary, int rightBoundary);
	bool DoesKill(Area object);
};

