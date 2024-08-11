#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;

class BattleButton
{
public:	
	SDL_Renderer* renderer;
	SDL_Rect buttonRect;
	SDL_Texture* textTexture;
	SDL_Rect textRect;

	bool selected;

	~BattleButton();

	void setup(SDL_Renderer* renderer, SDL_Rect buttonRect, string text);
	void draw();
	void drawInactive(); //WHAT BUTTONS LOOK LIKE when user cannot choose options
};

