#include "MovingHor.h"

void MovingHor::Move(double deltaTime) {
	pixelsToMove += direction*pixelsPerSecond*deltaTime;
	x += floor(pixelsToMove);
	pixelsToMove -= floor(pixelsToMove);
	if (direction == right) {
		if (x + width >= rightBoundary) {
			x = leftBoundary-width;
		}
	}
	else {
		if (x <= leftBoundary) {
			x = rightBoundary;
		}
	}
	this->Draw();
}

MovingHor::MovingHor(Area a, int pixelsPerSecond, DirectionHor direction, int leftBoundary, int rightBoundary)
	: Area(a) {
	this->pixelsPerSecond = pixelsPerSecond;
	this->direction = direction;
	this->leftBoundary = leftBoundary;
	this->rightBoundary = rightBoundary;
	pixelsToMove = 0;
}