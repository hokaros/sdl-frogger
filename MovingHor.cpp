#include "MovingHor.h"

MovingHor::MovingHor(Area a, Vector velocity, int leftBoundary, int rightBoundary)
	: Moving(a, velocity) {
	this->leftBoundary = leftBoundary;
	this->rightBoundary = rightBoundary;
}

VectorInt MovingHor::Move(double deltaTime) {
	VectorInt pixelsMoved = Moving::Move(deltaTime);
	if (velocity.x > 0) {
		if (x + width >= rightBoundary) {
			x = leftBoundary-width;
		}
	}
	else {
		if (x <= leftBoundary) {
			x = rightBoundary;
		}
	}
	return pixelsMoved;
}