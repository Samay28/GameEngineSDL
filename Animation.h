#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Animation
{
public:

	int numberOfFrames;
	int frameWidth, frameHeight;
	int offsetX, offsetY;

	float frameTime;

	SDL_Texture* spriteSheet;
	SDL_Renderer* renderer;

	void setup(string spriteSheetFile, SDL_Renderer* renderer, int numberOfFrames, float frameTime, int offsetX, int offsetY);
	~Animation();

	void draw(int frame, int x, int y);
};

