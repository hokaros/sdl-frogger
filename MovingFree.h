#pragma once
#include "Moving.h"
#define JUMP_DISTANCE 32
#define JUMP_SPEED 30
/*
Klasa, której obiekty
poruszaj¹ siê we wszystkie strony
i poruszaj¹ siê skokami o sta³¹
odleg³oœæ
*/
class MovingFree :
	public Moving
{
protected:
	Direction facing;
	//granice ruchu
	int leftBoundary;
	int rightBoundary;
	int topBoundary;
	int bottomBoundary;
	//zmienna zwracaj¹ca prawdê po zainicjowaniu ruchu
	bool moving;
	int* moveAxis;
	//zapamiêtywanie drugiego ruchu w kolejce
	Direction nextMove;
public:
	//po zainicjowaniu ruchu pozycja d¹¿y do docelowej
	VectorInt targetPos;

	MovingFree(Area a);
	MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary);
	void Move(Direction direction);
	void MoveByVector(VectorInt vector);
	void ProcessState(double deltaTime);
};

