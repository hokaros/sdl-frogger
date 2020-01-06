#pragma once
#include "Area.h"

enum class Direction { None, Up, Right, Down, Left };
typedef struct velocity {
	int pixelsPerSecond;
	Direction direction;
} Velocity;

const Velocity ZERO_VELOCITY = { 0, Direction::None };

class Moving :
	public Area
{
protected:
	Velocity velocity;
	/*
	Obiekt nie mo¿e siê poruszyæ o nieca³kowit¹ liczbê pikseli,
	dlatego czêœci po przecinku s¹ przechowywane w zmiennej  */
	double pixelsToMove; //zmienna przechowuj¹ca czêœci nieca³kowite pixeli
public:
	Moving(Area a, Velocity velocity);
	void Move(double deltaTime);
};

