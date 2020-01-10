#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include "Draw.h"
#include "MovingFree.h"
#include "Attachable.h"
#include "Game.h"
#include "Timer.h"
#include "Killing.h"
#include "TurtleGroup.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define TURTLE1_COUNT 3
#define TURTLE2_COUNT 2

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	Game game;
	int quit, rc;
	double distance, etiSpeed, delta;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *eti;
	SDL_Surface* background;
	SDL_Surface* froggerSf, *longLogSf, *car1Sf, *turtleSf;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	//wczytanie t³a
	background = SDL_LoadBMP("graphics/background1.bmp");
	if (background == NULL) {
		printf("SDL_LoadBMP(graphics/background1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};


	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(background);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	eti = SDL_LoadBMP("eti.bmp");
	if(eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	froggerSf = SDL_LoadBMP("graphics/frogger.bmp");
	if (froggerSf == NULL) {
		printf("SDL_LoadBMP(graphics/frogger.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_FreeSurface(eti);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	longLogSf = SDL_LoadBMP("graphics/logLong.bmp");
	if (longLogSf == NULL) {
		printf("SDL_LoadBMP(graphics/logLong.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(froggerSf);
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_FreeSurface(eti);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	car1Sf = SDL_LoadBMP("graphics/car1.bmp");
	if (car1Sf == NULL) {
		printf("SDL_LoadBMP(graphics/car1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(longLogSf);
		SDL_FreeSurface(froggerSf);
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_FreeSurface(eti);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	turtleSf = SDL_LoadBMP("graphics/turtle.bmp");
	if (turtleSf == NULL) {
		printf("SDL_LoadBMP(graphics/turtle.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(car1Sf);
		SDL_FreeSurface(longLogSf);
		SDL_FreeSurface(froggerSf);
		SDL_FreeSurface(background);
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_FreeSurface(eti);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	const int ROW_HEIGHT = froggerSf->h;

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	Timer timer;

	quit = 0;
	distance = 0;
	etiSpeed = 1;
	//obiekty poruszaj¹ce siê w lewo maj¹ ujemn¹ wspó³rzêdn¹ x wektora prêdkoœci
	Vector movableSpeed = {100, 0};
	Vector car1Speed = { -150, 0 };
	Vector turtle1Speed = { -130, 0 };
	Vector turtle2Speed = { -160, 0 };

	const int MAP_BOTTOM_BORDER = background->h;
	const int MAP_LEFT_BORDER = (SCREEN_WIDTH - background->w) / 2;
	const int MAP_TOP_BORDER = MAP_BOTTOM_BORDER - ROW_HEIGHT*13;
	const int MAP_RIGHT_BORDER = MAP_LEFT_BORDER + background->w;

	Rectangle water = { MAP_LEFT_BORDER, MAP_TOP_BORDER + ROW_HEIGHT, background->w, ROW_HEIGHT * 5 };

	Area rect(0, 0, eti, screen);
	Area frogger(MAP_LEFT_BORDER, MAP_BOTTOM_BORDER - froggerSf->h, froggerSf, screen);
	Area longLogA(MAP_LEFT_BORDER, MAP_BOTTOM_BORDER - ROW_HEIGHT * 10, longLogSf, screen);

	/*******************************PRZESZKODY*********************************/
	//pojazdy
	int car1Count = 5; //liczba pojazdów na 1. pasie ulicy
	Area car1A(MAP_LEFT_BORDER, MAP_BOTTOM_BORDER - ROW_HEIGHT * 2, car1Sf, screen);
	int car1Gap = 3 * car1A.width;

	Killing** car1 = new Killing * [car1Count];
	for (int i = 0; i < car1Count; i++) {
		car1[i] = new Killing({ 0,0,car1A.width, car1A.height }, //œmiercionoœny na ca³ej powierzchni
			car1A, car1Speed, MAP_LEFT_BORDER - background->w, MAP_RIGHT_BORDER);
		car1[i]->x += i*(car1[i]->width + car1Gap);
	}

	//¿ó³wie
	Area turtle(MAP_LEFT_BORDER, MAP_BOTTOM_BORDER - ROW_HEIGHT * 8, turtleSf, screen);
	int turtleGroup1Count = 3; //liczba grup ¿ó³wi na 1. pasie rzeki
	int turtleGroup1Gap = turtle.width * 3;

	TurtleGroup** turtleGroup1 = new TurtleGroup * [turtleGroup1Count];
	for (int i = 0; i < turtleGroup1Count; i++) {
		turtleGroup1[i] = new TurtleGroup(TURTLE1_COUNT, turtle, turtle1Speed, MAP_LEFT_BORDER - background->w, MAP_RIGHT_BORDER);
		turtleGroup1[i]->MoveByVector({ i*(turtleGroup1Gap + turtleGroup1[i]->GetWidth()), 0 });
	}
	//3. pas rzeki
	turtle.y -= ROW_HEIGHT * 3;
	int turtleGroup2Count = 5;
	int turtleGroup2Gap = turtle.width * 1.5;

	TurtleGroup** turtleGroup2 = new TurtleGroup * [turtleGroup2Count];
	for (int i = 0; i < turtleGroup2Count; i++) {
		turtleGroup2[i] = new TurtleGroup(TURTLE2_COUNT, turtle, turtle2Speed, MAP_LEFT_BORDER - background->w, MAP_RIGHT_BORDER);
		turtleGroup2[i]->MoveByVector({ i * (turtleGroup2Gap + turtleGroup2[i]->GetWidth()), 0 });
	}


	MovingHor movable(rect, movableSpeed, MAP_LEFT_BORDER, MAP_RIGHT_BORDER+background->w);
	Attachable longLog(longLogA, movableSpeed, MAP_LEFT_BORDER, MAP_RIGHT_BORDER + background->w);

	MovingFree userFrog(frogger, MAP_TOP_BORDER, MAP_RIGHT_BORDER, MAP_BOTTOM_BORDER, MAP_LEFT_BORDER);

	bool attached; //wskazuje, czy gracz porusza siê na jakiejœ przeszkodzie

	while(!quit) {

		delta = timer.GetDeltaTime();

		distance += etiSpeed * delta;


		//generowanie t³a
		SDL_FillRect(screen, NULL, czarny);
		DrawSurface(screen, background, SCREEN_WIDTH / 2, background->h / 2);

		//ruchy obiektów
		attached = false;
		movable.Move(delta);
		if (longLog.IsAttached(userFrog)) {
			attached = true;
			userFrog.MoveByVector(longLog.Move(delta));
		}
		else
			longLog.Move(delta);
		for (int i = 0; i < car1Count; i++) {
			car1[i]->Move(delta);
			if (car1[i]->DoesKill(userFrog)) {
				userFrog.MoveByVector({ 200,0 });
			}
		}
		for (int i = 0; i < turtleGroup1Count; i++) {
			if (!attached && turtleGroup1[i]->IsAttached(userFrog)) {
				attached = true;
				userFrog.MoveByVector(turtleGroup1[i]->Move(delta));
			}
			else
				turtleGroup1[i]->Move(delta);
		}
		for (int i = 0; i < turtleGroup2Count; i++) {
			if (!attached && turtleGroup2[i]->IsAttached(userFrog)) {
				attached = true;
				userFrog.MoveByVector(turtleGroup2[i]->Move(delta));
			}
			else
				turtleGroup2[i]->Move(delta);
		}

		if (!attached && userFrog.IsInside(water)) {
			game.LoseLife();
		}
		//czarne pasy po bokach ekranu
		DrawRectangle(screen, 0, 0, MAP_LEFT_BORDER, SCREEN_HEIGHT, czarny, czarny);
		DrawRectangle(screen, MAP_RIGHT_BORDER, 0, MAP_LEFT_BORDER, SCREEN_HEIGHT, czarny, czarny);



		DrawSurface(screen, eti,
		            SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3,
			    SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3);

		userFrog.ProcessState(delta);
		if (!userFrog.IsInside({ MAP_LEFT_BORDER, MAP_TOP_BORDER, MAP_RIGHT_BORDER - MAP_LEFT_BORDER,MAP_BOTTOM_BORDER - MAP_TOP_BORDER })) {
			game.LoseLife();
		}

		// tekst informacyjny / info text
		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", timer.worldTime, timer.GetFps(delta));
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				else if (event.key.keysym.sym == SDLK_UP) {
					etiSpeed = 2.0;
					userFrog.Move(Direction::Up);
				}
				else if(event.key.keysym.sym == SDLK_DOWN) {
					etiSpeed = 0.3;
					userFrog.Move(Direction::Down);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					userFrog.Move(Direction::Right);
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					userFrog.Move(Direction::Left);
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP //sprawdza,czy konkretne przyciski zosta³y puszczone
				|| event.key.keysym.sym == SDLK_DOWN) {
					etiSpeed = 1.0;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		timer.frames++;
	};

	//zwolnienie przeszkód
	for (int i = 0; i < car1Count; i++) {
		delete(car1[i]);
	}
	for (int i = 0; i < turtleGroup1Count; i++) {
		delete(turtleGroup1[i]);
	}
	for (int i = 0; i < turtleGroup1Count; i++) {
		delete(turtleGroup2[i]);
	}
	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(longLogSf);
	SDL_FreeSurface(turtleSf);
	SDL_FreeSurface(background);
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(froggerSf);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
