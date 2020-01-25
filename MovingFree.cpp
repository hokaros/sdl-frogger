#include "MovingFree.h"

MovingFree::MovingFree(Area a, string bmpBaseName)
	:MovingFree(a, -1000000, 1000000, 1000000, -1000000, bmpBaseName){
}

MovingFree::MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary, string bmpBaseName)
	:Moving(a, ZERO_VECTOR){
	facing = Direction::Up;
	//wczytywanie animacji
	//loading animations
	string fullName;
	SDL_Surface** bmps = new SDL_Surface*[MOVE_ANIMATION_FRAMES];
	int i;
	for (i = 0; i < MOVE_ANIMATION_FRAMES; i++) {
		fullName = "graphics/animations/" + bmpBaseName + "Up" + "/" + bmpBaseName + "Up-" + to_string(i) + ".bmp";
		bmps[i] = SDL_LoadBMP(fullName.c_str());
	}
	moveUp = new Animation(MOVE_ANIMATION_FRAMES, bmps);

	bmps = new SDL_Surface * [MOVE_ANIMATION_FRAMES];
	for (i = 0; i < MOVE_ANIMATION_FRAMES; i++) {
		fullName = "graphics/animations/" + bmpBaseName + "Right" + "/" + bmpBaseName + "Right-" + to_string(i) + ".bmp";
		bmps[i] = SDL_LoadBMP(fullName.c_str());
	}
	moveRight = new Animation(MOVE_ANIMATION_FRAMES, bmps);

	bmps = new SDL_Surface * [MOVE_ANIMATION_FRAMES];
	for (i = 0; i < MOVE_ANIMATION_FRAMES; i++) {
		fullName = "graphics/animations/" + bmpBaseName + "Down" + "/" + bmpBaseName + "Down-" + to_string(i) + ".bmp";
		bmps[i] = SDL_LoadBMP(fullName.c_str());
	}
	moveDown = new Animation(MOVE_ANIMATION_FRAMES, bmps);

	bmps = new SDL_Surface * [MOVE_ANIMATION_FRAMES];
	for (i = 0; i < MOVE_ANIMATION_FRAMES; i++) {
		fullName = "graphics/animations/" + bmpBaseName+"Left" + "/" + bmpBaseName + "Left-" + to_string(i) + ".bmp";
		bmps[i] = SDL_LoadBMP(fullName.c_str());
	}
	moveLeft = new Animation(MOVE_ANIMATION_FRAMES, bmps);

	moving = false;
	targetPos = { x, y };
	moveAxis = NULL;
	nextMove = Direction::None;
	this->topBoundary = topBoundary;
	this->rightBoundary = rightBoundary;
	this->bottomBoundary = bottomBoundary;
	this->leftBoundary = leftBoundary;
}

Animation* MovingFree::GetMove(Direction dir) {
	switch (dir) {
	case Direction::Up:
		return moveUp;
	case Direction::Right:
		return moveRight;
	case Direction::Down:
		return moveDown;
	case Direction::Left:
		return moveLeft;
	default:
		return moveUp;
	}
}

void MovingFree::Turn(Direction target) {
	facing = target;
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
			bmp = GetMove(facing)->End();
		}
		else {
			bmp = GetMove(facing)->NextFrame();
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
	bmp = moveUp->FirstFrame();
}