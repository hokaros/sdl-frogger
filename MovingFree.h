#pragma once
#include "Moving.h"
#define JUMP_DISTANCE 32
#define JUMP_SPEED 100
#define DIRECTIONS 4
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
	SDL_Surface* bmpUp;
	SDL_Surface* bmpRight;
	SDL_Surface* bmpDown;
	SDL_Surface* bmpLeft;
	SDL_Surface* GetBMP(Direction moveDirection);
	void Turn(Direction target);

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

	MovingFree(Area a, std::string bmpBaseName);
	MovingFree(Area a, int topBoundary, int rightBoundary, int bottomBoundary, int leftBoundary, std::string bmpBaseName);
	void Move(Direction direction);
	void MoveByVector(VectorInt vector);
	void SetPosition(VectorInt position);
	void ProcessState(double deltaTime);
};

