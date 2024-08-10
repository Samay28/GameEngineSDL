#pragma once
#include "AnimationManager.h"
#include "CharacterType.h"

using namespace std;
class CharacterAnimationSet
{
public:
	int x, y;
	SDL_Renderer* renderer;
	Animation idle, attack, hit;
	AnimationManager animationManager;

	bool doAction; //for anims that play once then return to idle

	void setup(SDL_Renderer* renderer, int x, int y, CharacterType type);
	void doIdle();
	void doAttack();
	void doHit();

	void update(float dt);
	void draw();
};

