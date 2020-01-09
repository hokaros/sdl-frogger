#include "Game.h"

Game::Game() {
	lives = MAX_LIVES;
	points = 0;
	level = 1;
	paused = false;
}

void Game::LevelUp() {
	level++;
	if (level > LAST_LEVEL) {
		Win();
	}
	else {
		LoadLevel();
	}
}

void Game::Win() {

}

void Game::Lose() {
	paused = true;
	//TO DO: wypisywanie komunikatu o pora¿ce na ekranie
}

void Game::ShowMenu() {

}

void Game::LoadLevel() {

}

void Game::LoseLife() {
	lives--;
	if (lives == 0) {
		Lose();
	}
}

void Game::ProcessState() {
	if (!paused) {

	}
}