#pragma once
#include "Area.h"

class WinArea
{
protected:
	static SDL_Surface* takenBmp;
public:
	static unsigned short count;
	static unsigned short takenCount;
	SDL_Surface* screen;
	Rectangle area;
	Area* bmpArea;
	bool taken;

	//sprawdza, czy obiekt mo�e przej�� pole, na kt�rym si� znajduje
	//je�li tak, to je przejmuje
	static bool DoesTake(Area object, WinArea** winAreas);
	WinArea(Rectangle area, SDL_Surface* screen);
	~WinArea();
	void Take();
	void Draw();
	static bool IsWon();
};

