#include "Timer.h"
#include <iostream>


Timer::Timer() {
	t2 = t1 = SDL_GetTicks();
	frames = 0;
	worldTime = 0;
	fpsTimer = 0;
	fps = 0;
	pauseT = 0;
}

double Timer::GetDeltaTime() {
	t2 = SDL_GetTicks();
	double delta = (t2 - t1)*0.001;
	t1 = t2;
	worldTime += delta;
	return delta;
}

double Timer::GetFps(double deltaTime) {
	fpsTimer += deltaTime;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};
	return fps;
}

void Timer::Pause() {
	pauseT = SDL_GetTicks();
}

void Timer::Unpause() {
	int unpauseT = SDL_GetTicks();
	t1 += unpauseT-pauseT;
}

void Timer::Freeze(int time) {
	//tc - czas obecny, delta - czas up³yniêty
	int tc, delta;
	//czas pocz¹tkowy
	int t0 = SDL_GetTicks();
	do {
		tc = SDL_GetTicks();
		delta = tc - t0;
	} while (delta <= time);
}