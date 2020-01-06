#pragma once
#include "Moving.h"

class MovingHor :
	public Moving
{
protected:
	int leftBoundary; //granice ruchu
	int rightBoundary;
public:
	MovingHor(Area a, Velocity velocity, int leftBoundary, int rightBoundary);
	void Move(double deltaTime);
};

