#pragma once
#include "Draw.h"
#include "Level.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Highscore.h"
#include <string>
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define MAX_LIVES 5
#define LAST_LEVEL 1
#define MAX_TIME 50
#define DANGER_TIME 40
#define TIME_MAX_WIDTH 200
#define PROMPT_WIDTH 400
#define PROMPT_HEIGHT 100

class Game
{
protected:
	SDL_Surface* screen;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;
	SDL_Surface* charset;
	Timer* timer;

	int lives;
	bool lost;
	int level;
	Level *currentLevel;

	bool paused;
	SDL_Event event;
	//punktacja
public:
	Menu* menu;
	int points;
	short highestRow;
protected:
	void Render();
	Option Lose();
	//wyœwietla informacje o ¿yciach, czasie i punktach
	void DrawInfo();
	void DrawTime(int x, int y, int maxWidth, int height);
public:
	Game(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset);
	~Game();
	//wywo³ywane przy pokonaniu ostatniego poziomu
	void Win();
	char* GetName();
	Option QuitForm();
	void LoseLife();
	void Pause();
	bool TimeOver();
	//punktacja
	void DistanceBonus();
	void Touchdown();
	//zwraca nr poziomu po wejœciu na kolejny
	int LevelUp();
	void LoadLevel();
	//przetwarzanie gry
	Option Start();
};