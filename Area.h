#pragma once
#include "Draw.h"
class Area
{
protected:
	int x;
	int y;
	int width;
	int height;
	SDL_Surface* bmp;
	SDL_Surface* screen;
public:
	Area(int x, int y, SDL_Surface* bmp, SDL_Surface* screen);
	void Draw();
};

