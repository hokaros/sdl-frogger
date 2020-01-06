#include "Moving.h"

Moving::Moving(Area a, Velocity velocity) 
	:Area(a){
	this->velocity = velocity;
	this->pixelsToMove = 0;
}

void Moving::Move(double deltaTime) {
	if (velocity.pixelsPerSecond != 0) {
		int* axis;
		int factor;
		Direction direction = velocity.direction;
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
		pixelsToMove += factor * (velocity.pixelsPerSecond * deltaTime);
		*axis += floor(pixelsToMove);
		pixelsToMove -= floor(pixelsToMove);
	}
	this->Draw();
}
