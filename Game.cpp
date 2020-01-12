#include "Game.h"

Game::Game(SDL_Surface* screen, SDL_Renderer* renderer, SDL_Texture* scrtex, SDL_Surface* charset) {
	this->screen = screen;
	this->renderer = renderer;
	this->scrtex = scrtex;
	this->charset = charset;
	lives = MAX_LIVES;
	lost = false;
	points = 0;
	level = 1;
	currentLevel = new Level(screen);
	timer = new Timer();
	paused = false;
	highestRow = 1;
}

Game::~Game() {
	delete timer;
	delete currentLevel;
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
}

void Game::Render() {
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Game::LoadLevel() {
	delete currentLevel;
	delete timer;
	currentLevel = new Level(screen);
	timer = new Timer();
	lost = false;
	lives = MAX_LIVES;
}

int Game::LevelUp() {
	level++;
	return level;
}

void Game::LoseLife() {
	lives--;
	//miejsce na animacjê
	//przesuniêcie na pozycjê pocz¹tkow¹
	currentLevel->player->SetPosition({ currentLevel->mapLeftBorder, currentLevel->mapBottomBorder - currentLevel->player->height });
	highestRow = 1;
	timer->worldTime = 0;
	if (lives <= 0) {
		lost = true;
	}
}

void Game::Win() {
	printf("Congratulations!");
}

Option Game::Lose() {
	int red = SDL_MapRGB(screen->format, 0xAA, 0x22, 0x22);
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int w = 300;
	int h = 80;
	char* text = "GAME OVER";

	DrawRectangle(screen, (SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h, red, black);
	DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, (SCREEN_HEIGHT-h)/2 + 4, text, charset);
	text = "Press any key to continue";
	DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, SCREEN_HEIGHT/2, text, charset);
	text = "Press ESC to exit to menu";
	DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, SCREEN_HEIGHT/2 + 16, text, charset);
	Render();

	points = 0;
	while (true) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return Option::Exit;
				else
					return Option::Play;
				break;
			case SDL_QUIT:
				return Option::Exit;
			}
		}
	}
}

void Game::DrawInfo() {
	char text[128];
	int primaryColour = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int secondaryColour = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	int x = currentLevel->mapLeftBorder;
	int y = currentLevel->mapBottomBorder;
	int width = currentLevel->mapRightBorder - currentLevel->mapLeftBorder;
	int height = SCREEN_HEIGHT - currentLevel->mapBottomBorder;
	int textMargin = 8;

	sprintf(text, "Score: %d", points);
	DrawString(screen, x + textMargin, y + textMargin, text, charset);
	sprintf(text, "Lives left: %d", lives);
	DrawString(screen, x + textMargin, y + 2 * textMargin + 8, text, charset);
	int timeLeft = ceil(MAX_TIME - timer->worldTime);
	sprintf(text, "Time: %d", timeLeft);
	DrawString(screen, x + width - textMargin - strlen(text) * 8, y + 2 * textMargin + 8, text, charset);
	DrawTime(x + width - TIME_MAX_WIDTH - textMargin, y + 3 * textMargin + 8, TIME_MAX_WIDTH, 8);
}

void Game::DrawTime(int minX, int y, int maxWidth, int height) {
	int green = SDL_MapRGB(screen->format, 0x00, 0xEE, 0x00);
	int red = SDL_MapRGB(screen->format, 0xEE, 0x00, 0x00);
	int width = (MAX_TIME-timer->worldTime) * maxWidth / MAX_TIME;
	int colour;
	if (timer->worldTime > DANGER_TIME)
		colour = red;
	else
		colour = green;
	int x = minX + maxWidth - width;
	DrawRectangle(screen, x, y, width, height, colour, colour);
}

Option Game::QuitForm() {
	Option chosen = Option::Play;
	char* text;
	int primaryColour = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int secondaryColour = SDL_MapRGB(screen->format, 0x22, 0xFF, 0x22);
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int backgroundW = 400;
	int backgroundH = 100;
	int optionW = 200;
	int optionH = 50;
	while (true) {
		//t³o
		DrawRectangle(screen, (SCREEN_WIDTH - backgroundW) / 2, (SCREEN_HEIGHT - backgroundH) / 2, backgroundW, backgroundH, primaryColour, secondaryColour);
		text = "QUIT GAME?";
		DrawString(screen,
			(SCREEN_WIDTH - strlen(text) * 8) / 2,
			(SCREEN_HEIGHT - backgroundH + optionH) / 2,
			text, charset);
		//przyciski
		if (chosen == Option::Play) {
			DrawRectangle(screen,
				(SCREEN_WIDTH - backgroundW)/2 + optionW, 
				SCREEN_HEIGHT / 2,
				optionW, optionH, secondaryColour, primaryColour); //zaznaczona
			DrawRectangle(screen,
				(SCREEN_WIDTH - backgroundW) / 2,
				SCREEN_HEIGHT / 2,
				optionW, optionH, primaryColour, secondaryColour);
		}
		else {
			DrawRectangle(screen,
				(SCREEN_WIDTH - backgroundW) / 2 + optionW,
				SCREEN_HEIGHT / 2,
				optionW, optionH, primaryColour, secondaryColour);
			DrawRectangle(screen,
				(SCREEN_WIDTH - backgroundW) / 2,
				SCREEN_HEIGHT / 2,
				optionW, optionH, secondaryColour, primaryColour); //zaznaczona
		}
		text = "Yes";
		DrawString(screen,
			(SCREEN_WIDTH - backgroundW) / 2 + optionW/2 - strlen(text) * 8,
			SCREEN_HEIGHT / 2 + (optionH - 8) / 2,
			text, charset);
		text = "No";
		DrawString(screen,
			(SCREEN_WIDTH - backgroundW) / 2 + (int)(optionW*1.5) -strlen(text)*8,
			SCREEN_HEIGHT / 2 + (optionH - 8) / 2,
			text, charset);
		Render();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return Option::Play;
				else if (event.key.keysym.sym == SDLK_y)
					return Option::Exit;
				else if (event.key.keysym.sym == SDLK_n)
					return Option::Play;
				else if (event.key.keysym.sym == SDLK_UP
					|| event.key.keysym.sym == SDLK_w
					|| event.key.keysym.sym == SDLK_LEFT
					|| event.key.keysym.sym == SDLK_a)
					chosen = Option::Exit;
				else if (event.key.keysym.sym == SDLK_DOWN
					|| event.key.keysym.sym == SDLK_s
					|| event.key.keysym.sym == SDLK_RIGHT
					|| event.key.keysym.sym == SDLK_d)
					chosen = Option::Play;
				else if (event.key.keysym.sym == SDLK_RETURN)
					return chosen;
				break;
			case SDL_QUIT:
				return Option::Exit;
			}
		}
	}
}

Option Game::Menu() {
	Option chosen = Option::Play;
	char* text;
	int primaryColour = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int secondaryColour = SDL_MapRGB(screen->format, 0x22, 0xFF, 0x22);
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int backgroundW = 500;
	int backgroundH = 400;
	int optionW = 150;
	int optionH = 50;
	SDL_FillRect(screen, NULL, black);
	while (true) {

		//t³o
		DrawRectangle(screen, (SCREEN_WIDTH - backgroundW) / 2, (SCREEN_HEIGHT - backgroundH) / 2, backgroundW, backgroundH, primaryColour, secondaryColour);
		//przyciski
		if (chosen == Option::Play) {
			DrawRectangle(screen, (SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT - optionH*2) / 2, optionW, optionH, secondaryColour, primaryColour); //zaznaczona
			DrawRectangle(screen, (SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT) / 2, optionW, optionH, primaryColour, secondaryColour);
		}
		else {
			DrawRectangle(screen, (SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT - optionH * 2) / 2, optionW, optionH, primaryColour, secondaryColour); //zaznaczona
			DrawRectangle(screen, (SCREEN_WIDTH - optionW) / 2, (SCREEN_HEIGHT) / 2, optionW, optionH, secondaryColour, primaryColour);
		}
		text = "Play";
		DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, (SCREEN_HEIGHT - optionH - 8) / 2, text, charset);
		text = "Exit";
		DrawString(screen, (SCREEN_WIDTH - strlen(text) * 8) / 2, (SCREEN_HEIGHT + optionH - 8) / 2, text, charset);
		Render();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) 
					return Option::Exit;
				else if (event.key.keysym.sym == SDLK_UP
					|| event.key.keysym.sym == SDLK_w)
					chosen = Option::Play;
				else if (event.key.keysym.sym == SDLK_DOWN
					|| event.key.keysym.sym == SDLK_s)
					chosen = Option::Exit;
				else if (event.key.keysym.sym == SDLK_RETURN)
					return chosen;
				break;
			case SDL_QUIT:
				return Option::Exit;
			}
		}
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

	Render();
	while (paused) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
				paused = false;
		}
	}
}

bool Game::TimeOver() {
	if (timer->worldTime > MAX_TIME)
		return true;
	else
		return false;
}

void Game::DistanceBonus() {
	int delta = currentLevel->RowAdvancement(highestRow);
	if (delta > 0) {
		highestRow += delta;
		points += delta * 10;
	}
}

void Game::Touchdown() {
	char text[32];
	int bonus = 0;
	int receivedP = 50 + 10 * ceil(MAX_TIME - timer->worldTime) + bonus;
	timer->Pause();
	sprintf(text, "+%d", receivedP);
	DrawString(screen, currentLevel->mapLeftBorder + 8, currentLevel->mapBottomBorder - 8, text, charset);
	if (bonus > 0) {
		sprintf(text, "%d", bonus);
		DrawString(screen, currentLevel->player->GetCenter().x - strlen(text) * 4, currentLevel->player->y - 8, text, charset);
	}
	Render();
	timer->Freeze(1000);
	timer->Unpause();
	points += receivedP;
	highestRow = 1;
	currentLevel->player->SetPosition({ currentLevel->mapLeftBorder, currentLevel->mapBottomBorder - currentLevel->player->height });
	timer->worldTime = 0;
}

Option Game::Start() {
	int quit = 0;
	char text[128];
	bool attached, killed;
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	double delta;
	Rectangle water = { currentLevel->mapLeftBorder, currentLevel->mapBottomBorder - ROW_HEIGHT*12, currentLevel->background->w, ROW_HEIGHT * 5 };
	while (!quit) {
		delta = timer->GetDeltaTime();

		//generowanie t³a
		SDL_FillRect(screen, NULL, black);
		DrawSurface(screen, currentLevel->background, SCREEN_WIDTH / 2, currentLevel->background->h / 2);
		currentLevel->DrawWinAreas();
		//ruchy obiektów
		attached = false;
		killed = false;
		currentLevel->MoveCars(killed, delta);
		currentLevel->MoveTurtles(attached, delta);
		currentLevel->MoveLogs(attached, delta);
		//sprawdzanie, czy gracz siê utopi³
		if (!attached && currentLevel->player->IsInside(water))
			killed = true;
		//czarne pasy po bokach ekranu
		DrawRectangle(screen, 0, 0, currentLevel->mapLeftBorder, SCREEN_HEIGHT, black, black);
		DrawRectangle(screen, currentLevel->mapRightBorder, 0, currentLevel->mapLeftBorder, SCREEN_HEIGHT, black, black);

		//poruszanie graczem
		currentLevel->player->ProcessState(delta);
		DistanceBonus();
		//sprawdzanie, czy gracz wyszed³ poza mapê
		if (!currentLevel->player->IsInside({ currentLevel->mapLeftBorder,
			currentLevel->mapTopBorder,
			currentLevel->mapRightBorder - currentLevel->mapLeftBorder,
			currentLevel->mapBottomBorder - currentLevel->mapTopBorder })) {
			killed = true;
		}

		//pasek informacyjny
		DrawInfo();
		//sprawdzanie, czy gracz doszed³ do koñca mapy
		if (currentLevel->player->IsInside(currentLevel->winRow)) {
			if (WinArea::DoesTake(*(currentLevel->player), currentLevel->winAreas)) {
				Touchdown();
			}
			else
				killed = true;
		}
		if (TimeOver())
			killed = true;
		//œmieræ
		if (killed) {
			LoseLife();
			if (lost) {
				return Lose();
			}
		}
		//zwyciêstwo - wyjœcie z poziomu gry, aby j¹ prze³adowaæ
		if (WinArea::IsWon())
			return Option::Play;
		Render();

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP
					|| event.key.keysym.sym == SDLK_w) {
					currentLevel->player->Move(Direction::Up);
				}
				else if (event.key.keysym.sym == SDLK_DOWN
					|| event.key.keysym.sym == SDLK_s) {
					currentLevel->player->Move(Direction::Down);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT
					|| event.key.keysym.sym == SDLK_d) {
					currentLevel->player->Move(Direction::Right);
				}
				else if (event.key.keysym.sym == SDLK_LEFT
					|| event.key.keysym.sym == SDLK_a) {
					currentLevel->player->Move(Direction::Left);
				}
				else if (event.key.keysym.sym == SDLK_p) {
					timer->Pause();
					Pause();
					timer->Unpause();
				}
				else if (event.key.keysym.sym == SDLK_q) {
					timer->Pause();
					if (QuitForm() == Option::Exit)
						return Option::Exit;
					timer->Unpause();
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		timer->frames++;
	};
	return Option::Exit;
}