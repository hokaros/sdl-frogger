#pragma once
#include "Area.h"
enum DirectionHor {left = -1, right = 1};
class MovingHor :
	public Area
{
protected:
	int pixelsPerSecond;
	double pixelsToMove;
	enum DirectionHor direction;
	int leftBoundary; //granice ruchu
	int rightBoundary;
public:
	MovingHor(Area a, int pixelsPerSecond, DirectionHor direction, int leftBoundary, int rightBoundary);
	void Move(double deltaTime);
};

