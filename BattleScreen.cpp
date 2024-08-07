#include "BattleScreen.h"

BattleScreen::BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{
	this->hero = hero;
	this->items = items;
	this->renderer = renderer;

	backgroundTexture = IMG_LoadTexture(renderer, "assets/bg.png");
}

BattleScreen::~BattleScreen()
{
	SDL_DestroyTexture(backgroundTexture);
}

void BattleScreen::update()
{
	while (!battleFinished)
	{	
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			//event when user clicks close window button
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			//if a button was pressed
			if (sdlEvent.type == SDL_KEYDOWN)
			{
				//then check which button
				//did they press ESC key?
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
			}
		}
		if (quit)
		{
			battleFinished = true;
		}
		draw();
	}
}

void BattleScreen::draw()
{
	//clear screen
	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	SDL_RenderPresent(renderer);
}
