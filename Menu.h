#pragma once
#include "Draw.h"
#include "Highscore.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define MENU_WIDTH 500
#define MENU_HEIGHT 400

enum class Option { Play, Exit, Highscores };

class Menu
{
protected:
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;
	SDL_Surface* charset;
	SDL_Event event;
	int optionCount;
	int primaryColour;
	int secondaryColour;

	void Render();
public:
	Menu(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset);
	Option GetOption(int optNum);
	void DrawButton(int x, int y, int width, int height, char* text, bool chosen);
	Option MainMenu();
	void Highscores();
};

