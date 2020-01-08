#include "Moving.h"

Moving::Moving(Area a, Vector velocity) 
	:Area(a){
	this->velocity = velocity;
	this->pixelsToMove = ZERO_VECTOR;
}

VectorInt Moving::Move(double deltaTime) {
	if (velocity.x != 0 || velocity.y != 0) {
		pixelsToMove.x += (velocity.x * deltaTime);
		pixelsToMove.y += (velocity.y * deltaTime);
		VectorInt pixelsMoved = { floor(pixelsToMove.x), floor(pixelsToMove.y) };
		MoveByVector(pixelsMoved);
		pixelsToMove.x -= pixelsMoved.x;
		pixelsToMove.y -= pixelsMoved.y;
		this->Draw();
		return pixelsMoved;
	}
	this->Draw();
}

void Moving::MoveByVector(VectorInt vector) {
	x += (vector.x);
	y += (vector.y);
}
