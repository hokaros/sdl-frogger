#include "MovingHor.h"

void MovingHor::Move(double deltaTime) {
	Moving::Move(deltaTime);
	if (velocity.direction == Direction::Right) {
		if (x + width >= rightBoundary) {
			x = leftBoundary-width;
		}
	}
	else {
		if (x <= leftBoundary) {
			x = rightBoundary;
		}
	}
}

MovingHor::MovingHor(Area a, Velocity velocity, int leftBoundary, int rightBoundary)
	: Moving(a, velocity) {
	this->leftBoundary = leftBoundary;
	this->rightBoundary = rightBoundary;
}