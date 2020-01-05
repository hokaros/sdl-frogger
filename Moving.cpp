#include "Moving.h"

void Moving::Move(double deltaTime) {
	int *axis;
	int factor;
	if (direction == Direction::Right
	|| direction == Direction::Left) {
		axis = &x;
		if (direction == Direction::Right)
			factor = 1; //zwiêkszanie x
		else
			factor = -1; //zmniejszanie x
	}
	else {
		axis = &y;
		if (direction == Direction::Down)
			factor = 1; //oœ Y skierowana w dó³
		else 
			factor = -1;
	}
	pixelsToMove += factor * pixelsPerSecond * deltaTime;
	*axis += floor(pixelsToMove);
	pixelsToMove -= floor(pixelsToMove);
	this->Draw();
}
