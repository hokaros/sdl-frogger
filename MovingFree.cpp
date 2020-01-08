#include "MovingFree.h"

MovingFree::MovingFree(Area a) 
	:MovingFree(a, -1000000, 1000000, 1000000, -1000000){
}

MovingFree::MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary) 
	:Moving(a, ZERO_VECTOR){
	facing = Direction::Up;
	moving = false;
	targetPos = { x, y };
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
			targetPos.x = x + factor * JUMP_DISTANCE;
		}
		else {
			moveAxis = &y;
			if (direction == Direction::Down)
				factor = 1;
			else
				factor = -1;
			targetPos.y = y + factor * JUMP_DISTANCE;
		}
		switch (direction) {
		case Direction::Right:
			if (targetPos.x+width > rightBoundary)
				targetPos.x = rightBoundary-width;
			break;
		case Direction::Down:
			if (targetPos.y+height > bottomBoundary)
				targetPos.y = bottomBoundary-height;
			break;
		case Direction::Left:
			if (targetPos.x < leftBoundary)
				targetPos.x = leftBoundary;
			break;
		case Direction::Up:
			if (targetPos.y < topBoundary)
				targetPos.y = topBoundary;
			break;
		}
		velocity = ZERO_VECTOR;
	}
	else {
		nextMove = direction;
	}
}

void MovingFree::MoveByVector(VectorInt vector) {
	x += vector.x;
	y += vector.y;
	targetPos.x += vector.x;
	targetPos.y += vector.y;
}

void MovingFree::ProcessState(double deltaTime) {
	if (moving) {
		velocity.x = JUMP_SPEED * (targetPos.x - x);
		velocity.y = JUMP_SPEED * (targetPos.y - y);
		Moving::Move(deltaTime);

		if (targetPos.x == x && targetPos.y == y){
			moving = false;
		}
	}
	else {
		velocity = ZERO_VECTOR;
		if (nextMove != Direction::None) {
			Move(nextMove);
			nextMove = Direction::None;
		}
		else {
			Moving::Move(deltaTime);
		}
	}
}