#include "Moving.h"

void Moving::Move(double deltaTime) {
	int *axis;
	int factor;
	if (direction == Direction::Right
	|| direction == Direction::Left) {
		axis = &x;
		if (direction == Direction::Right)
			factor = 1; //zwi�kszanie x
		else
			factor = -1; //zmniejszanie x
	}
	else {
		axis = &y;
		if (direction == Direction::Down)
			factor = 1; //o� Y skierowana w d�
		else 
			factor = -1;
	}
	pixelsToMove += factor * pixelsPerSecond * deltaTime;
	*axis += floor(pixelsToMove);
	pixelsToMove -= floor(pixelsToMove);
	this->Draw();
}
