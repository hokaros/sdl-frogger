#pragma once
#include "Draw.h"
#include "Level.h"
#include "Timer.h"
#include <string>
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define MAX_LIVES 5
#define LAST_LEVEL 1

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
	int points;
	int level;
	Level *currentLevel;

	bool paused;
	SDL_Event event;

	void Render();
	Option Lose();
	Option QuitForm();
public:
	Game(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset);
	~Game();
	Option Menu();
	void LoseLife();
	void Pause();
	int LevelUp();
	void LoadLevel();
	Option Start();
	void Win();

};