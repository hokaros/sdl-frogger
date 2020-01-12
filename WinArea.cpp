#include "WinArea.h"

unsigned short WinArea::count = 0;
unsigned short WinArea::takenCount = 0;
SDL_Surface* WinArea::takenBmp = SDL_LoadBMP("graphics/endFrog.bmp");

WinArea::WinArea(Rectangle area, SDL_Surface* screen) {
	this->area = area;
	this->screen = screen;
	taken = false;
	bmpArea = new Area(area.x, area.y, takenBmp, screen);
	count++;
}

WinArea::~WinArea() {
	delete bmpArea;
}

void WinArea::Take() {
	taken = true;
	takenCount++;
}

void WinArea::Draw() {
	if (taken) {
		bmpArea->Draw();
	}
}

bool WinArea::IsWon() {
	if (takenCount!=0 && takenCount >= count)
		return true;
	else
		return false;
}

bool WinArea::DoesTake(Area object, WinArea** winAreas) {
	for (unsigned short i = 0; i < count; i++) {
		if (object.IsCenterInside(winAreas[i]->area)
			&& !(winAreas[i]->taken)) {
			winAreas[i]->Take();
			return true;
		}
	}
	return false;
}