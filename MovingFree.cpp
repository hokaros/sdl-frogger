#include "MovingFree.h"

MovingFree::MovingFree(Area a, std::string bmpBaseName)
	:MovingFree(a, -1000000, 1000000, 1000000, -1000000, bmpBaseName){
}

MovingFree::MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary, std::string bmpBaseName)
	:Moving(a, ZERO_VECTOR){
	facing = Direction::Up;
	bmpUp = bmp;
	std::string fullName = "graphics/" + bmpBaseName + "Left.bmp";
	bmpLeft = SDL_LoadBMP(fullName.c_str());
	if (bmpLeft == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", SDL_GetError(), fullName.c_str());
		delete(this);
		return;
	}
	fullName = "graphics/" + bmpBaseName + "Down.bmp";
	bmpDown = SDL_LoadBMP(fullName.c_str());
	if (bmpLeft == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", SDL_GetError(), fullName.c_str());
		delete(this);
		return;
	}
	fullName = "graphics/" + bmpBaseName + "Right.bmp";
	bmpRight = SDL_LoadBMP(fullName.c_str());
	if (bmpLeft == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", SDL_GetError(), fullName.c_str());
		delete(this);
		return;
	}
	moving = false;
	targetPos = { x, y };
	moveAxis = NULL;
	nextMove = Direction::None;
	this->topBoundary = topBoundary;
	this->rightBoundary = rightBoundary;
	this->bottomBoundary = bottomBoundary;
	this->leftBoundary = leftBoundary;
}

SDL_Surface* MovingFree::GetBMP(Direction dir) {
	switch (dir) {
	case Direction::Up:
		return bmpUp;
	case Direction::Right:
		return bmpRight;
	case Direction::Down:
		return bmpDown;
	case Direction::Left:
		return bmpLeft;
	default:
		return bmp;
	}
}

void MovingFree::Turn(Direction target) {
	if (target != facing) {
		bmp = GetBMP(target);
		facing = target;
	}
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
		Turn(direction);
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

void MovingFree::SetPosition(VectorInt position) {
	velocity = ZERO_VECTOR;
	moving = false;
	nextMove = Direction::None;
	x = position.x;
	y = position.y;
	targetPos = position;
}