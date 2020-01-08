#pragma once
#include "Area.h"

enum class Direction { None, Up, Right, Down, Left };

class Moving :
	public Area
{
protected:
	Vector velocity;
	/*
	Obiekt nie mo¿e siê poruszyæ o nieca³kowit¹ liczbê pikseli,
	dlatego czêœci po przecinku s¹ przechowywane w zmiennej  */
	Vector pixelsToMove; //zmienna przechowuj¹ca czêœci nieca³kowite pixeli
public:
	Moving(Area a, Vector velocity);
	VectorInt Move(double deltaTime);
	void MoveByVector(VectorInt vector);
};

