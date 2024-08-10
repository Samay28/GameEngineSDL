#include "CharacterAnimationSet.h"

void CharacterAnimationSet::setup(SDL_Renderer* renderer, int x, int y, CharacterType type)
{
	this->renderer = renderer;
	this->y = y;
	this->x = x;

	if (type == heroType)
	{
		//load up hero animation
		idle.setup("assets/girlIdle.png", renderer, 1, 1, 40, 132);
		attack.setup("assets/girlPunch.png", renderer, 3, 0.1f, 69, 155);
		hit.setup("assets/girlHit.png", renderer, 2, 0.1f, 47, 145);
	}
	else if (type == globType)
	{
		idle.setup("assets/globIdle.png", renderer, 1, 1, 36, 105);
		attack.setup("assets/globBite.png", renderer, 3, 0.1f, 93, 123);
		hit.setup("assets/globHit.png", renderer, 2, 0.1f, 62, 115);
	}
	else if (type == mimicType)
	{
		idle.setup("assets/mimicIdle.png", renderer, 1, 1, 53, 65);
		attack.setup("assets/mimicAttack.png", renderer, 4, 0.1f, 151, 113);
		hit.setup("assets/mimicHit.png", renderer, 2, 0.1f, 45, 69);
	}

	doIdle();
}

void CharacterAnimationSet::doIdle()
{
	animationManager.chanegAnimation(&idle);
	animationManager.setAnimationLooping(true);
	doAction = false;
}

void CharacterAnimationSet::doAttack()
{
	animationManager.chanegAnimation(&attack);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void CharacterAnimationSet::doHit()
{
	animationManager.chanegAnimation(&hit);
	animationManager.setAnimationLooping(false);
	doAction = true;
}

void CharacterAnimationSet::update(float dt)
{
	animationManager.update(dt);
	//if running action anim and that anim is finished
	if (animationManager.animationEnded && doAction)
	{
		doIdle();
	}
}

void CharacterAnimationSet::draw()
{
	animationManager.draw(x, y);
}
