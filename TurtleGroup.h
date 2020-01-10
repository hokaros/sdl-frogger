#pragma once
#include "Attachable.h"
#define TURTLE_GAP 0
class TurtleGroup 
{
public: 
	int turtleCount;
	Attachable** turtles;

	TurtleGroup();
	TurtleGroup(int turtleCount, Area turtle, Vector velocity, int leftBoundary, int rightBoundary);
	~TurtleGroup();
	int GetWidth();
	VectorInt Move(double deltaTime);
	void MoveByVector(VectorInt distance);
	bool IsAttached(Area object);
};

