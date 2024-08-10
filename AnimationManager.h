#pragma once
#include "Animation.h"


class AnimationManager
{

public:	
	Animation* currentAnimation;
	int currentFrame;
	float frameTimer;
	bool animationEnded;
	bool loopAnimation;


	AnimationManager();

	void chanegAnimation(Animation* animation);
	void setAnimation(bool loopAnimation);
	void resetAnimation();
	void update(float dt); //need deltatime to work out frame timer
	void draw(int x, int y);
};

