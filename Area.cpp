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

VectorInt Area::GetCenter() {
	int centerX = x + (width / 2);
	int centerY = y + (height / 2);
	return { centerX, centerY };
}

void Area::Draw() {
	VectorInt center = GetCenter();
	DrawSurface(screen, bmp, center.x, center.y);
}

bool IsPointInside(VectorInt p, Rectangle r) {
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

//bool Area::IsInside(Rectangle r) {
//	if (IsPointInside({ x,y }, r)
//		&& IsPointInside({ x,y + height }, r)
//		&& IsPointInside({ x + width,y }, r)
//		&& IsPointInside({ x + width,y + height }, r))
//		return true;
//	else
//		return false;
//}
