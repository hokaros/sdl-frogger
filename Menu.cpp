#include "Menu.h"

Menu::Menu(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset) {
	this->screen = screen;
	this->renderer = renderer;
	this->scrtex = scrtex;
	this->charset = charset;
	optionCount = 3;
	primaryColour = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	secondaryColour = SDL_MapRGB(screen->format, 0x22, 0xFF, 0x22);
}

void Menu::Render() {
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}


Option Menu::GetOption(int num) {
	num = num % optionCount;
	switch (num) {
	case 0:
		return Option::Play;
	case 1:
		return Option::Highscores;
	case 2:
		return Option::Exit;
	}
}

void Menu::DrawButton(int x, int y, int width, int height, char* text, bool chosen) {
	int outlineColour, fillColour;
	int charSize = charset->w / 16;
	if (chosen) {
		outlineColour = secondaryColour;
		fillColour = primaryColour;
	}
	else {
		outlineColour = primaryColour;
		fillColour = secondaryColour;
	}
	DrawRectangle(screen, x, y, width, height, outlineColour, fillColour);
	DrawString(screen, x + (width - strlen(text) * charSize) / 2, y + (height - charSize) / 2, text, charset);
}

Option Menu::MainMenu() {
	Option chosen = Option::Play;
	char* text;
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int backgroundW = 500;
	int backgroundH = 400;
	int optionW = 150;
	int optionH = 50;
	int chosenNum = 0;
	while (true) {

		//t³o
		SDL_FillRect(screen, NULL, black);
		DrawRectangle(screen, (SCREEN_WIDTH - backgroundW) / 2, (SCREEN_HEIGHT - backgroundH) / 2, backgroundW, backgroundH, primaryColour, secondaryColour);
		//przyciski
		text = "Play";
		DrawButton((SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT - optionH * 2) / 2, optionW, optionH, text, chosen == Option::Play);
		text = "Highscores";
		DrawButton((SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT) / 2, optionW, optionH, text, chosen == Option::Highscores);
		text = "Exit";
		DrawButton((SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT + optionH * 2) / 2, optionW, optionH, text, chosen == Option::Exit);
		Render();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return Option::Exit;
				else if (event.key.keysym.sym == SDLK_UP
					|| event.key.keysym.sym == SDLK_w) {
					chosenNum+=optionCount-1;
					chosenNum = chosenNum % optionCount;
					chosen = GetOption(chosenNum);
				}
				else if (event.key.keysym.sym == SDLK_DOWN
					|| event.key.keysym.sym == SDLK_s) {
					chosenNum++;
					chosenNum = chosenNum % optionCount;
					chosen = GetOption(chosenNum);
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					if (chosen == Option::Highscores)
						Highscores();
					else
						return chosen;
				}
				break;
			case SDL_QUIT:
				return Option::Exit;
			}
		}
	}
}

void Menu::Highscores() {
	Highscore** highscores= Highscore::LoadFromFile();
	char text[64];
	int pos;
	int background = secondaryColour;
	SDL_FillRect(screen, NULL, background);
	for (int i = 1; i <= 10; i++) {
		pos = highscores[i-1]->position;
		sprintf(text, "%s", highscores[i - 1]->name);
		sprintf(text, "%d. %s  - %d", pos, highscores[i-1]->name, highscores[i-1]->score);
		DrawString(screen, SCREEN_WIDTH / 2, i * 20, text, charset);
	}
	Render();
	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN)
				return;
		}
	}
}