#include "Attachable.h"

Attachable::Attachable(Area a, Vector velocity, int leftBoundary, int rightBoundary) 
	:MovingHor(a, velocity, leftBoundary, rightBoundary) {

}

bool Attachable::IsAttached(Area object) {
	return object.IsCenterInside({ x,y,width,height });
}