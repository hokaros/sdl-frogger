#include "Game.h"

Game::Game() {
	lives = MAX_LIVES;
	points = 0;
	level = 1;
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
}

void Game::ShowMenu() {

}

void Game::LoadLevel() {

}