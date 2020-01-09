#include "Timer.h"


Timer::Timer() {
	t2 = t1 = SDL_GetTicks();
	frames = 0;
	worldTime = 0;
	fpsTimer = 0;
	fps = 0;
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