#include "Area.h"
#include "Draw.h"
#include <iostream>

Area::Area(int x, int y, SDL_Surface* bmp, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = bmp->w;
	this->height = bmp->h;
	this->bmp = bmp;
	this->screen = screen;
}

void Area::Draw() {
	int centerX = x + (width / 2);
	int centerY = y + (height / 2);
	DrawSurface(screen, bmp, centerX, centerY);
}
