#pragma once
#include "Draw.h"

class Animation
{
protected:
	int frames;
	int currentFrame;
	SDL_Surface** bmps;
public:
	Animation(int frames, SDL_Surface** bmps);
	~Animation();
	SDL_Surface* NextFrame();
	SDL_Surface* FirstFrame();
	SDL_Surface* End();
};

