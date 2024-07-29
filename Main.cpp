#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "MapScreen.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);

	SDL_RenderClear(renderer);
		
	//the size graphics are at min, but then scale up to actual window size
	//SDL_RenderSetLogicalSize(renderer, 600, 400);


	SDL_Texture* testImg = IMG_LoadTexture(renderer, "assets/girlIdle.png");
	if (testImg == NULL)
	{
		cout << "Oh no" << IMG_GetError();
	}

	//Items(using arrays..) 0 = no item, 1 = choclate, 2 = grenade, 3 = atk up, 4 = def up
	int items[10];

	for (int i = 0; i <= 9; i++)
	{
		items[i] = 0;
	}
	items[0] = 1;
	//items[1] = 1;
	//items[2] = 3;
	for (int i = 0; i <= 9; i++)
	{
		cout << "items[" << i << "] = " << items[i]<<endl;
	}

	//setup map
	MapScreen mapScreen(renderer, items);

	//the region of the texture we want to draw from
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 107; //ACC. TO IMAGE SIZE
	srcRect.h = 137;

	//destination
	SDL_Rect destRect;
	destRect.x = 70;
	destRect.y = 20;
	destRect.w = 107; //ACC. TO IMAGE SIZE
	destRect.h = 137;

	//render copy renders texture to the window
	SDL_RenderCopy(renderer, testImg, &srcRect, &destRect);

	mapScreen.draw();
	SDL_RenderPresent(renderer);
	
	SDL_Delay(3000);
	SDL_DestroyTexture(testImg);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;


}