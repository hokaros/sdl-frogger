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
	Obiekt nie mo�e si� poruszy� o nieca�kowit� liczb� pikseli,
	dlatego cz�ci po przecinku s� przechowywane w zmiennej  */
	double pixelsToMove; //zmienna przechowuj�ca cz�ci nieca�kowite pixeli
public:
	void Move(double deltaTime);
};

