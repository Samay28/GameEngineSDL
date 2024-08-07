#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"

using namespace std;

class BattleScreen
{
public:	

	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Hero* hero;
	int* items;

	Character* enemy;

	bool battleFinished;
	bool quit;
	bool herosTurn;

	BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items);
	~BattleScreen();

	void update();
	void draw();
};

