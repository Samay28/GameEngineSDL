#include "Animation.h"

void Animation::setup(string spriteSheetFile, SDL_Renderer* renderer, int numberOfFrames, float frameTime, int offsetX, int offsetY)
{
	this->renderer = renderer;
	this->spriteSheet = IMG_LoadTexture(renderer, spriteSheetFile.c_str());

	//temp variables
	int w, h;
	SDL_QueryTexture(spriteSheet, NULL, NULL, &w, &h);

	//cam calculate framewidth and height 
	frameWidth = w / numberOfFrames;
	frameHeight = h;

	this->numberOfFrames = numberOfFrames;
	this->frameTime = frameTime;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

Animation::~Animation()
{
	if (!spriteSheet != NULL)
		SDL_DestroyTexture(spriteSheet);
}

void Animation::draw(int frame, int x, int y)
{
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = frame * frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	//where frame whould be drawn 
	SDL_Rect dest = { x - offsetX, y - offsetY, frameWidth, frameHeight };
	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);
}
