#pragma once
#include "Area.h"
enum class Direction { Up, Right, Down, Left };
class Moving :
	public Area
{
protected:
	int pixelsPerSecond;
	Direction direction;
	/*
	Obiekt nie mo¿e siê poruszyæ o nieca³kowit¹ liczbê pikseli,
	dlatego czêœci po przecinku s¹ przechowywane w zmiennej  */
	double pixelsToMove; //zmienna przechowuj¹ca czêœci nieca³kowite pixeli
public:
	void Move(double deltaTime);
};

