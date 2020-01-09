#include "Area.h"
#include "Draw.h"
#include <iostream>

Area::Area() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	bmp = NULL;
	screen = NULL;
}

Area::Area(int x, int y, SDL_Surface* bmp, SDL_Surface* screen) {
	this->x = x;
	this->y = y;
	this->width = bmp->w;
	this->height = bmp->h;
	this->bmp = bmp;
	this->screen = screen;
}

VectorInt Area::GetCenter() {
	int centerX = x + (width / 2);
	int centerY = y + (height / 2);
	return { centerX, centerY };
}

void Area::Draw() {
	VectorInt center = GetCenter();
	DrawSurface(screen, bmp, center.x, center.y);
}

bool Area::IsPointInside(VectorInt p, Rectangle r) {
	if (p.x >= r.x
		&& p.x <= r.x + r.width
		&& p.y >= r.y
		&& p.y <= r.y + r.height)
		return true;
	else
		return false;
}

bool Area::IsCenterInside(Rectangle r) {
	VectorInt center = GetCenter();
	return IsPointInside(center, r);
}

bool Area::IsInside(Rectangle r) {
	if (IsPointInside({ x,y }, r)
		&& IsPointInside({ x,y + height }, r)
		&& IsPointInside({ x + width,y }, r)
		&& IsPointInside({ x + width,y + height }, r))
		return true;
	else
		return false;
}

bool Area::DoesCross(Rectangle r) {
	VectorInt corner = { x, y };  //lewy, górny róg
	if (IsPointInside(corner, r) 
		&& corner.y != r.y+r.height
		&& corner.x != r.x+r.width)
		return true;
	corner = { x, y + height }; //lewy, dolny róg
	if (IsPointInside(corner, r)
		&& corner.y != r.y
		&& corner.x != r.x + r.width)
		return true;
	corner = { x + width, y }; //prawy, górny róg
	if (IsPointInside(corner, r)
		&& corner.y != r.y + r.height
		&& corner.x != r.x)
		return true;
	corner = { x + width, y + height }; //prawy, dolny róg
	if (IsPointInside(corner, r)
		&& corner.y != r.y
		&& corner.x != r.x)
		return true;
	return false;
}
