#include "Animation.h"

Animation::Animation(int frames, SDL_Surface** bmps) {
	this->frames = frames;
	this->bmps = bmps;
	currentFrame = 0;
}

Animation::~Animation() {
	for (int i = 0; i < frames; i++) {
		delete bmps[i];
	}
}

SDL_Surface* Animation::NextFrame() {
	currentFrame++;
	if (currentFrame >= frames)
		currentFrame = 0;
	return bmps[currentFrame];
}

SDL_Surface* Animation::FirstFrame() {
	return bmps[0];
}

SDL_Surface* Animation::End() {
	currentFrame = 0;
	return FirstFrame();
}