#include "MovingFree.h"

MovingFree::MovingFree(Area a) 
	:MovingFree(a, -1000000, 1000000, 1000000, -1000000){
}

MovingFree::MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary) 
	:Moving(a, ZERO_VELOCITY){
	facing = Direction::Up;
	moving = false;
	targetPos = 0;
	moveAxis = NULL;
	nextMove = Direction::None;
	this->topBoundary = topBoundary;
	this->rightBoundary = rightBoundary;
	this->bottomBoundary = bottomBoundary;
	this->leftBoundary = leftBoundary;
}

void MovingFree::Move(Direction direction) {
	if (direction == Direction::None)
		return;
	if (!moving) {
		moving = true;
		short factor;
		if (direction == Direction::Right
		|| direction == Direction::Left) {
			moveAxis = &x;
			if (direction == Direction::Right)
				factor = 1;
			else
				factor = -1;
		}
		else {
			moveAxis = &y;
			if (direction == Direction::Down)
				factor = 1;
			else
				factor = -1;
		}
		targetPos = *moveAxis + factor * JUMP_DISTANCE;
		switch (direction) {
		case Direction::Right:
			if (targetPos+width > rightBoundary)
				targetPos = rightBoundary-width;
			break;
		case Direction::Down:
			if (targetPos+height > bottomBoundary)
				targetPos = bottomBoundary-height;
			break;
		case Direction::Left:
			if (targetPos < leftBoundary)
				targetPos = leftBoundary;
			break;
		case Direction::Up:
			if (targetPos < topBoundary)
				targetPos = topBoundary;
			break;
		}
		velocity = { 0, direction };
	}
	else {
		nextMove = direction;
	}
}

void MovingFree::ProcessState(double deltaTime) {
	if (moving) {
		if (targetPos >= *moveAxis)
			velocity.pixelsPerSecond = JUMP_SPEED * (targetPos - *moveAxis);
		else
			velocity.pixelsPerSecond = JUMP_SPEED * (*moveAxis - targetPos);
		Moving::Move(deltaTime);

		if (targetPos == *moveAxis){
			moving = false;
		}
	}
	else if (nextMove != Direction::None) {
		Move(nextMove);
		nextMove = Direction::None;
	}
	else {
		velocity = ZERO_VELOCITY;
		Moving::Move(deltaTime);
	}
}