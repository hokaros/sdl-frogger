#pragma once
#include "Draw.h"
#include "Level.h"
#define MAX_LIVES 5
#define LAST_LEVEL 6

class Game
{
protected:
	int lives;
	int points;
	int level;
	Level currentLevel;

	bool paused;

	void LevelUp();
	void Win();
	void Lose();
	void LoadLevel();
public:
	Game();
	void ShowMenu();
	void LoseLife();
	void ProcessState();

};