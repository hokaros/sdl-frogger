#include "TurtleGroup.h"
#include <iostream>

TurtleGroup::TurtleGroup() {
	turtleCount = 0;
	turtles = NULL;
}

TurtleGroup::TurtleGroup(int turtleCount, Area turtle, Vector velocity, int leftBoundary, int rightBoundary) {
	this->turtleCount = turtleCount;
	turtles = new Attachable * [turtleCount];
	for (int i = 0; i < turtleCount; i++) {
		turtles[i] = new Attachable(turtle, velocity, leftBoundary, rightBoundary);
		turtle.x += turtle.width + TURTLE_GAP;
	}
}

TurtleGroup::~TurtleGroup() {
	delete(turtles);
}

int TurtleGroup::GetWidth() {
	if (turtleCount == 0)
		return 0;
	int width = turtleCount * turtles[0]->width + (turtleCount - 1) * TURTLE_GAP;
	return width;
}

VectorInt TurtleGroup::Move(double deltaTime) {
	for (int i = 0; i < turtleCount-1; i++) {
		turtles[i]->Move(deltaTime);
	}
	return turtles[turtleCount - 1]->Move(deltaTime);
}

void TurtleGroup::MoveByVector(VectorInt distance) {
	for (int i = 0; i < turtleCount; i++) {
		turtles[i]->MoveByVector(distance);
	}
}

bool TurtleGroup::IsAttached(Area object) {
	for (int i = 0; i < turtleCount; i++) {
		if (turtles[i]->IsAttached(object))
			return true;
	}
	return false;
}