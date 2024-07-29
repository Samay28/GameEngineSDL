#include "MapScreen.h"

MapScreen::MapScreen(SDL_Renderer* renderer, int* items)
{
	this->renderer = renderer;
	this->items = items;

	for (int i = 0; i <= 9; i++)
	{
		for (int y = 0; y<= 9; y++)
		{
			map[i][y] = 0;
		}
	}
	/*p[1][1] = 1;
	map[2][1] = 1;
	map[3][1] = 1;
	map[4][1] = 1;*/

	fstream mapFile("assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y <=9; y++)
		{
			for (int i = 0; i <= 9; i++)
			{
				char grid;
				mapFile >> grid;//read into grid, one by one

				if (grid == '0')
				{
					map[i][y] = 0;//wall
				}
				else
				{
					map[i][y] = 1;//land
				}
			}
		}
	}
	//close file
	mapFile.close();

}

MapScreen::~MapScreen()
{

}

void MapScreen::draw()
{
	SDL_Rect tileRect = { 0,0,64,64 };

	for (int i = 0; i <= 9; i++)
	{
		for (int y = 0; y<= 9; y++)
		{
			if (map[i][y] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
				cout << "black" << endl;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			tileRect.x = i * tileRect.w;
			tileRect.y = y * tileRect.h;
			
			SDL_RenderFillRect(renderer, &tileRect);
		}
	}

}
