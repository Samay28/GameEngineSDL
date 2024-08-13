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
#include "CharacterAnimationSet.h"
#include "CharacterType.h"
#include "HPBar.h"
#include "BattleButton.h"
#include "BattleEffects.h"
#include "ItemMenu.h"
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
	bool heroesTurn = true;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;

	CharacterAnimationSet heroAnimationsSet;
	CharacterAnimationSet enemyAnimationSet;

	HPBar heroHP;
	HPBar enemyHP;

	BattleButton fightButton;
	BattleButton itemButton;

	int heroDmg = 0, enemyDmg = 0;

	BattleEffects battleEffects;
	

	ItemMenu itemMenu;

	BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType);
	~BattleScreen();
	bool animationsPlaying();
	void update();
	void draw();
};

