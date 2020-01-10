#include "Game.h"

Game::Game(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset) {
	this->screen = screen;
	this->renderer = renderer;
	this->scrtex = scrtex;
	this->charset = charset;
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

void Game::Pause() {
	paused = true;
	char* text = "PAUSED";
	int innerColour = SDL_MapRGB(screen->format, 0xCC, 0xCC, 0x11);
	int outerColour = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int w = 150;
	int h = 50;
	DrawRectangle(screen, (SCREEN_WIDTH-w) / 2, (SCREEN_HEIGHT-h) / 2, w, h, outerColour, innerColour);
	DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, (SCREEN_HEIGHT - 8) / 2, text, charset);

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
	while (paused) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
				paused = false;
		}
	}
}