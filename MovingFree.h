#pragma once
#include "Moving.h"
#define JUMP_DISTANCE 32
#define JUMP_SPEED 20
/*
Klasa, kt�rej obiekty
poruszaj� si� we wszystkie strony
i poruszaj� si� skokami o sta��
odleg�o��
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
	//zmienna zwracaj�ca prawd� po zainicjowaniu ruchu
	bool moving;
	int* moveAxis;
	//zapami�tywanie drugiego ruchu w kolejce
	Direction nextMove;
	//po zainicjowaniu ruchu pozycja d��y do docelowej
	int targetPos;
public:
	MovingFree(Area a);
	MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary);
	void Move(Direction direction);
	void ProcessState(double deltaTime);
};
