#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"
//TODO MORE

using namespace std;

class BattleScreen
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Hero* hero;
	int* items;//pointer for our items array

	Character* enemy;

	bool battleFinished = false;
	bool quit;
	bool heroesTurn;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;
	//TODO add lots more

	BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items);
	~BattleScreen();
	void update();
	void draw();
};

