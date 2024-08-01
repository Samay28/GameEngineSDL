#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "MapObject.h"
#include <list>// dynamic array
#include "InfoBox.h"
#include <fstream>
using namespace std;
class MapScreen
{

public:

	int* items; //to reference items[10] from main

	SDL_Renderer* renderer;

	int map[10][10]; //0 = walls,1= ground
	MapObject heroObj;
	MapObject door;
	list<MapObject> mapObjects;

	SDL_Texture* heroTexture, * doorTexture, * globTexture,*chestTexture;

	bool quit = false;

	InfoBox infoBox;

	MapScreen(SDL_Renderer* renderer, int* items);
	~MapScreen();


	void update();
	void draw();
};

