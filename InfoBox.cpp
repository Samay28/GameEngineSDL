#include "InfoBox.h"
#include <iostream>
using namespace std;

InfoBox::InfoBox() {
	// Load font with size
	Font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	if (!Font) {
		cout << "Failed to load font: " << TTF_GetError() << endl;
	}
	else {
		cout << "Font loaded successfully" << endl;
	}
}

InfoBox::~InfoBox()
{
	if (textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
	}

	TTF_CloseFont(Font);
}

void InfoBox::setup(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void InfoBox::setText(string text)
{
	//only change text if its diff from before and not empty string
	if (this->text != text && text != "")
	{	
		//destroy old textTexture before creating new ones
		if (textTexture != NULL)
		{
			SDL_DestroyTexture(textTexture);
		}

		this->text = text;

		//build texture
		SDL_Color textColor = { 0,0,0,0 };//black
		//create surface out of our text
		SDL_Surface* textSurface = TTF_RenderText_Blended(Font, text.c_str(), textColor);
		//convt surface to texture
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//delete surface (free)
		SDL_FreeSurface(textSurface);

		//workout width and height of generated texture
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

		//work out how to center the text in the screen..
		textRect.x = 1200 / 2 - textRect.w / 2; //half screen - half width
		textRect.y = 800 / 2 - textRect.h / 2;
		
		//workout our box rectangle with some padding
		boxRect.x = textRect.x - 4;
		boxRect.y = textRect.y - 4;
		boxRect.w = textRect.w + 8; //maths of fencing and perimeter
		boxRect.h = textRect.h + 8;
	}
}

void InfoBox::draw()
{
	if (visible)
	{
		if (textTexture != NULL)
		{

			if (text != "")
			{
				SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
				SDL_RenderFillRect(renderer, &boxRect);

				//draw border
 
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, &boxRect);

				//draw text
				SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
			}
		}
	}
}
