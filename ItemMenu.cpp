#include "ItemMenu.h"

SDL_Texture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color color, string text)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	return textTexture;
}

ItemMenu::~ItemMenu()
{
	SDL_DestroyTexture(noItem);
	SDL_DestroyTexture(chocolate);
	SDL_DestroyTexture(grenade);
	SDL_DestroyTexture(atkBoost);
	SDL_DestroyTexture(defboost);
	SDL_DestroyTexture(cancel);
}

void ItemMenu::setup(SDL_Renderer* renderer, int* items, int x, int y)
{
	this -> renderer = renderer;
	this->items = items;
	this->x = x;
	this->y = y;

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0, 0, 0, 255 };

	//generate all text textures
	noItem = generateTextTexture(font, textColor, "--");
	chocolate = generateTextTexture(font, textColor, "Chocolate");
	grenade = generateTextTexture(font, textColor, "Grenade");
	atkBoost = generateTextTexture(font, textColor, "Atk Boost");
	defboost = generateTextTexture(font, textColor, "Def Boost");
	cancel = generateTextTexture(font, textColor, "Cancel");

	TTF_CloseFont(font);
}

void ItemMenu::moveUp()
{
	selectedItemIndex--;
	if (selectedItemIndex < 0)
		selectedItemIndex = 0;
}

void ItemMenu::moveDown()
{
	selectedItemIndex++;
	if (selectedItemIndex > 10)
		selectedItemIndex = 10;
}

void ItemMenu::draw()
{
	if (!visible)
		return;

	SDL_Rect itemButton = { x,y,100,20 };

	//lop thru 10 items for drawing
	for (int i = 0; i < 10; i++)
	{	
		//put button beneath prev button
		itemButton.y = y + (i * itemButton.h);

		//set item button bg color based on selected
		if (selectedItemIndex == i)
		{
			SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		//render button back color
		SDL_RenderFillRect(renderer, &itemButton);

		//setup texture pointer and work out which text txture we need for this item we are rendering
		SDL_Texture* tmpTexture = noItem;
		if (items[i] == 1)
			tmpTexture = chocolate;
		else if (items[i] == 2)
			tmpTexture = grenade;
		else if (items[i] == 3)
			tmpTexture = atkBoost;
		else if (items[i] == 4)
			tmpTexture = defboost;

		SDL_Rect textRect;
		textRect.x = itemButton.x + 2;
		textRect.y = itemButton.y + 2;

		//get width of this text we are pointing at
		SDL_QueryTexture(tmpTexture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, tmpTexture, NULL, &textRect);
	}
	//and also do cancel button too
	if (selectedItemIndex == 10)
	{
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	itemButton.y = y + (10 * itemButton.h);
	SDL_RenderFillRect(renderer, &itemButton);

	SDL_Rect textRect;
	textRect.x = itemButton.x + 2;
	textRect.y = itemButton.y + 2;

	//get width of this text we are pointing at
	SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, cancel, NULL, &textRect);

}
