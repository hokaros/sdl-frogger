#pragma once
#include "Moving.h"
#include "Animation.h"
#include <sstream>
#define JUMP_DISTANCE 32
#define JUMP_SPEED 100
#define DIRECTIONS 4
#define MOVE_ANIMATION_FRAMES 10
using namespace std;
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
	Animation* GetMove(Direction moveDirection);
	Animation* moveUp;
	Animation* moveRight;
	Animation* moveDown;
	Animation* moveLeft;
	void Turn(Direction target);

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
public:
	//po zainicjowaniu ruchu pozycja d��y do docelowej
	VectorInt targetPos;

	MovingFree(Area a, string bmpBaseName);
	MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary, string bmpBaseName);
	void Move(Direction direction);
	void MoveByVector(VectorInt vector);
	void SetPosition(VectorInt position);
	void ProcessState(double deltaTime);
};

