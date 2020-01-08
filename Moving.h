#pragma once
#include "Area.h"

enum class Direction { None, Up, Right, Down, Left };

class Moving :
	public Area
{
protected:
	Vector velocity;
	/*
	Obiekt nie mo�e si� poruszy� o nieca�kowit� liczb� pikseli,
	dlatego cz�ci po przecinku s� przechowywane w zmiennej  */
	Vector pixelsToMove; //zmienna przechowuj�ca cz�ci nieca�kowite pixeli
public:
	Moving(Area a, Vector velocity);
	VectorInt Move(double deltaTime);
	void MoveByVector(VectorInt vector);
};

