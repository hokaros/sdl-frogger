#pragma once
extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

class Timer
{
public:
	int t1;
	int t2;
	int frames;
	double worldTime;
	double fpsTimer;
	double fps;

	int pauseT;

	Timer();
	//zwraca czas w sekundach up³yniêty od ostatniego wywo³ania funkcji
	double GetDeltaTime();
	double GetFps(double deltaTime);
	void Pause();
	void Unpause();
};

