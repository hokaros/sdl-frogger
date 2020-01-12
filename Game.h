#pragma once
#include "Draw.h"
#include "Level.h"
#include "Timer.h"
#include <string>
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define MAX_LIVES 5
#define LAST_LEVEL 1
#define MAX_TIME 50
#define DANGER_TIME 40
#define TIME_MAX_WIDTH 200

enum class Option {Play, Exit};

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
	int points;
	short highestRow;
protected:
	void Render();
	Option Lose();
	//wy�wietla informacje o �yciach, czasie i punktach
	void DrawInfo();
	void DrawTime(int x, int y, int maxWidth, int height);
public:
	Game(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset);
	~Game();
	//wywo�ywane przy pokonaniu ostatniego poziomu
	void Win();
	Option Menu();
	Option QuitForm();
	void LoseLife();
	void Pause();
	bool TimeOver();
	//punktacja
	void DistanceBonus();
	void Touchdown();
	//zwraca nr poziomu po wej�ciu na kolejny
	int LevelUp();
	void LoadLevel();
	//przetwarzanie gry
	Option Start();
};