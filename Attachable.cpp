#include "Attachable.h"

Attachable::Attachable(Area a, Vector velocity, int leftBoundary, int rightBoundary) 
	:MovingHor(a, velocity, leftBoundary, rightBoundary) {

}

bool Attachable::IsAttached(Area object) {
	return object.IsCenterInside({ x,y,width,height });
	/*if (object.x < x)
		return false;
	if (object.y < y)
		return false;
	if (object.x > x + width)
		return false;
	if (object.y > y + height)
		return false;
	return true;*/
}

void Attachable::MoveWith(double deltaTime, void (*mover)(VectorInt)) {
	VectorInt pixelsMoved = Move(deltaTime);
	mover(pixelsMoved);
}