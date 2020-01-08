#pragma once
#include "Moving.h"

class MovingHor :
	public Moving
{
protected:
	int leftBoundary; //granice ruchu
	int rightBoundary;
public:
	MovingHor(Area a, Vector velocity, int leftBoundary, int rightBoundary);
	/*podczas ruchu dodatkowo sprawdzane jest,
	czy obiekt nie wyszed³ poza granice*/
	VectorInt Move(double deltaTime);
};

