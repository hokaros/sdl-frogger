#pragma once
#include "MovingHor.h"
class Killing :
	public MovingHor
{
public:
	//œmiertelny obszar podany wzglêdem pozycji obiektu MovingHor
	rectangle lethalArea;
	Killing(rectangle lethalArea, Area a, Vector velocity, int leftBoundary, int rightBoundary);
	bool DoesKill(Area object);
};

