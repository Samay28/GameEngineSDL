#include "HPBar.h"

HPBar::HPBar()
{
	hp = hpMax = 100;
}

void HPBar::setup(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;
}

void HPBar::draw()
{
	SDL_Rect back = { x,y,102,12 };

	//draw white part
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &back);

	//draw black border
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &back);

	int hpBarWidth = ((1.0*hp) / hpMax) * 100; //100 is width of pixel of full health bar.. used 1.0*  for decimal points

	if (hpBarWidth < 0)
		hpBarWidth = 0;

	SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255); //red pinky
	SDL_Rect hpColorBar = { x + 1, y + 1, hpBarWidth, 10 };

	SDL_RenderFillRect(renderer, &hpColorBar);
}
