#include "MapScreen.h"



MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{	

	//Note: computer code random is pseudorandom
	//setting a seed value for the random algo will generate a set of numbers which appear random
	//seed value to be different each time we run the game
	
	srand(time(NULL));

	this->renderer = renderer;
	this->hero = hero;
	this->items = items;

	//loop through map using nested loop and clear all values out to be zero(walls)
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			map[x][y] = 0;
		}

	}
	//manual room building
	map[1][1] = 1;
	map[2][1] = 1;
	map[3][1] = 1;
	map[1][2] = 1;

	 
	//Open map text file
	fstream mapFile("assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y <= 9; y++)
		{
			for (int x = 0; x <= 9; x++)
			{
				//read in a single character from where we are up to in the file
				char grid;
				mapFile >> grid;
				if (grid == '0')
				{
					map[x][y] = 0; //wall
				}
				else
				{
					map[x][y] = 1;//land

					//TODO was it a hero, glob, chest or mimic???
					if (grid == 'h')
					{
						heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
					}
					else if (grid == 'd')
					{
						door.type = 2;
						door.x = x;
						door.y = y;
					}
					else if (grid == 'c')
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
					}
					else if (grid == 'g')
					{
						MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
					}
					else if (grid == 'm')
					{
						MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
					}
				}
			}
		}
	}
	//close file
	mapFile.close();

	//LOAD UP TILE TEXTURES
	heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
	doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
	globTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
	chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");

	//setup info box
	infoBox.setup(renderer);
	infoBox.setText("Welcome to the Dungeon!");
}


MapScreen::~MapScreen()
{
	//CLEANUP TEXTURE MEMORY
	SDL_DestroyTexture(heroTexture);
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(globTexture);
	SDL_DestroyTexture(chestTexture);
}

void MapScreen::itemFound()
{
	//randomly pick an item bw 1-4
	int item = rand()% 4 + 1; //rand gets next number out of random num set

	//try find a free slot for this item
	bool freeSlotFound = false;

	//once found free slot, set it to item and exit the loop
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == 0)
		{
			freeSlotFound = true;
			items[i] = item;
			break;
		}
	}

	if (freeSlotFound)
	{
		if (item == 1)
			infoBox.setText("Found Yummy Chocolate!");
		else if(item==2)
			infoBox.setText("Found a demolishing grenade!");
		else if (item == 3)
			infoBox.setText("Found an ATK Boost!");
		else if (item == 4)
			infoBox.setText("Found a DEF Boost");
	}
	else
	{
		infoBox.setText("Your Bag is Full!");
	}

	infoBox.visible = true;
}

void MapScreen::update()
{
	//read user inputs including keyboard, mouse, gamepads, screen resize/close, touchscreens etc
	SDL_Event sdlEvent;
	//loop through input events and copy their details one by one into our sdlEvent variable
	while (SDL_PollEvent(&sdlEvent))
	{
		//event when user clicks close window button
		if (sdlEvent.type == SDL_QUIT)
		{
			quit = true;
		}
		//if a button was pressed
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			//then check which button
			//did they press ESC key?
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				quit = true;
			}
			//hide infobox when space is pressed
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox.visible = false;
			}


			if (infoBox.visible == false && hero->getHP() > 0)
			{
				//player movement
				int hx = heroObj.x;
				int hy = heroObj.y;
				//right dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					hx++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					hx--;
				}
				//down dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					hy++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					hy--;
				}
				//if hx and hy are within the grid
				//AND is land we can walk on (map value of 1)
				if (hx >= 0 && hx <= 9 && hy >= 0 && hy <= 9 && map[hx][hy] == 1)
				{
					//set heroObj.x and y to hx and hy
					heroObj.x = hx;
					heroObj.y = hy;


					if (!doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
					{
						infoBox.setText("You Escaped!");
						infoBox.visible = true;
						escaped = true;
					}
					//if we walked onto a map object
					for (list<MapObject>::iterator mo = mapObjects.begin(); mo!=mapObjects.end(); mo++) 
					{	
						//iterator is a special pointer pointing to a position in a list
						// dereferencing iterator gives you access to the item at that point in that list
		
						//only interact wit active
						if (mo->active)
						{
							//is hero x,y overlapping with this objects x,y?
							if (heroObj.x == mo->x && heroObj.y == mo->y)
							{
								mo->active = false;

								//check that object's type
								if (mo->type == 5)
								{
									itemFound();
								}
							}
						}
					}
				}
				else
				{
					//invalid move, dont need to do anything here
				}
			}
		}
	}

	//check if mapobjects all inactive and if we should unlock the door
	if (!infoBox.visible && doorLocked)
	{
		bool monstersAlive = false;
		for (MapObject mo : mapObjects)
		{
			//if a monster
			if (mo.type == 3 || mo.type == 4)
			{
				if (mo.active)
				{
					monstersAlive = true;
					break;
				}
			}
		}
		if (!monstersAlive)
		{
			doorLocked = false;
			infoBox.setText("The Door is Unlocked");
			infoBox.visible = true;
		}
	}

	//once user closes infobox quit the game
	if (!infoBox.visible && (escaped || hero->getHP()<=0))
	{
		quit = true;
	}

}

void MapScreen::draw() {
	//MAP DRAWING
	//tile representing size of 1 grid thing from map
	SDL_Rect tileRect = { 0,0,120,120 };
	//loop through and draw each grid value from map array
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			//IF is ground, set draw colour to ground colour
			//ELSE set to wall colour
			if (map[x][y] == 1)
			{
				//ground
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}
			else
			{
				//walls
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			//MOVE rectangle to grid position with regards to tile width/height
			tileRect.x = x * tileRect.w;
			tileRect.y = y * tileRect.h;
			//draw rectangle to screen using current draw colour
			SDL_RenderFillRect(renderer, &tileRect);
		}
	}

	//DRAW MAP OBJECTS
	//draw hero
	tileRect.x = heroObj.x * tileRect.w; //e.g hero x = 4, y = 6. tile w = 32 h = 32
	tileRect.y = heroObj.y * tileRect.h;
	SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);
	//draw door
	tileRect.x = door.x * tileRect.w;
	tileRect.y = door.y * tileRect.h;
	SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
	//DRAW MAP OBJECTS IN LIST
	//loop through list and draw each object
	for (MapObject mo : mapObjects)
	{
		//NOTE: mo is a mapObject copy from mapObjects and is not a direct reference to the mapObject in the list
		if (mo.active)
		{
			tileRect.x = mo.x * tileRect.w;
			tileRect.y = mo.y * tileRect.h;
			if (mo.type == 3)//glob
			{
				SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
			}
			else//mimic or chest
			{
				SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
			}
		}
	}


	//draw info box on top
	infoBox.draw();
}