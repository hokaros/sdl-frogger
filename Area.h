#pragma once
#include "Draw.h"
typedef struct vector {
	double x;
	double y;
} Vector;

typedef struct vectorInt {
	int x;
	int y;
} VectorInt;

typedef struct rectangle {
	int x;
	int y;
	int width;
	int height;
} Rectangle;

const Vector ZERO_VECTOR = { 0, 0 };


class Area
{
public:
	int x;
	int y;
	int width;
	int height;
protected:
	SDL_Surface* bmp;
	SDL_Surface* screen;
public:
	Area();
	Area(int x, int y, SDL_Surface* bmp, SDL_Surface* screen);
	void Draw();
	VectorInt GetCenter();
	static bool IsPointInside(VectorInt p, Rectangle rectangle);
	bool IsCenterInside(Rectangle rectangle);
	//sprawdza, czy obiekt jest ca³kowicie w polu rectangle
	bool IsInside(Rectangle rectangle);
	//sprawdza, czy obiekt przecina pole
	bool DoesCross(Rectangle rectangle);
};

