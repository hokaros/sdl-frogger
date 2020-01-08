#pragma once
#include "MovingHor.h"

class Attachable :
	public MovingHor
{
public:
	Attachable(Area a, Vector velocity, int leftBoundary, int rightBoundary);
	bool IsAttached(Area object);
};

