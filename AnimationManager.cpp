#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	currentAnimation = NULL;
	currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;
	loopAnimation = true;
}

void AnimationManager::chanegAnimation(Animation* animation)
{
	currentAnimation = animation;
	resetAnimation();
}

void AnimationManager::setAnimationLooping(bool loopAnimation)
{
	this->loopAnimation = loopAnimation;
}

void AnimationManager::resetAnimation()
{
	currentFrame = 0;
	frameTimer = 0;
	animationEnded = false;
}

void AnimationManager::update(float dt)
{
	if (currentAnimation != NULL)
	{
		//update frametimer
		frameTimer += dt;

		//if this frame has been shown long enough
		if (frameTimer >= currentAnimation->frameTime)
		{
			//moveon to next frame
			currentFrame++;
			frameTimer = 0;

			if (currentFrame >= currentAnimation->numberOfFrames) //checking if currentframe is past the last frame of our anim
			{
				if (loopAnimation)
				{	
					//go back to first frame to loop again
					currentFrame = 0;
				}
				else
				{
					animationEnded = true;

					//make the current frame the last one in the set
					currentFrame = currentAnimation->numberOfFrames - 1;
				}
			}
		}
	}
}

void AnimationManager::draw(int x, int y)
{
	if (currentAnimation != NULL)
		currentAnimation->draw(currentFrame, x, y);
}
