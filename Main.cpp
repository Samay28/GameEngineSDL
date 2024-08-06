#include <iostream> //input output stream
#include <string> 
#include "Puzzles.h"
#include "Character.h"
#include "Hero.h"
#include "Glob.h"
#include "Mimic.h"
#include "MapScreen.h"
//SDL Libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

int main(int argc, char* argv[])
{		
	//cout = console out
	cout << "Hello there..." << endl; //endl = end line
	cout << "What is your name?" << endl;
	//variable to hold name of user/player
	//format of declaring a variable: datatype variableName;
	string name;
	//read name into name variable from keyboard
	//cin = console in ff
	cin >> name;

	cout << "Welcome to the dungeon " << name << ", muahahahaha!!!" << endl;

	cout << "How old are you?" << endl;
	int age;
	cin >> age;
	cout << "So you are " << age << " years old!" << endl;

	cout << "What is your favourite number: " << endl;
	int favNum;
	cin >> favNum;
	cout << "Well you are now stuck in this dungeon for " << favNum << " years! Muahahaha!" << endl;

	//working out the new age
	int newAge = age + favNum;
	cout << "Its time to escape before you turn " << newAge << " years old!" << endl;

	//output warning if they'll be 80 or older
	if (newAge >= 80)
	{
		cout << "You might not even live to this age!" << endl;
	}

	//if favNum is equal to 64 then output message
	if (favNum == 64) {
		cout << "Nice favourite number by the way!" << endl;
	}

	//hero stats
	int hp = 0, str = 0, def = 0, agi = 0;

	bool characterSetup = false;

	while (characterSetup == false)
	{
		cout << "What type of character are you?" << endl;
		cout << "1 - Beserker" << endl;
		cout << "2 - Buff Nut" << endl;
		cout << "3 - Speedy Ninja" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			hp = 60;
			str = 10;
			def = 2;
			agi = 3;
		}
		else if (choice == 2) {
			hp = 100;
			str = 4;
			def = 5;
			agi = 1;
		}
		else if (choice == 3) {
			hp = 80;
			str = 3;
			def = 1;
			agi = 10;
		}
		else
		{
			cout << "Invalid choice! Try again...." << endl;
		}

		if (choice >= 1 && choice <= 3)
		{
			characterSetup = true;
		}
	}

	cout << "Stats" << endl;
	cout << "hp: " << hp << endl;
	cout << "strength: " << str << endl;
	cout << "defense: " << def << endl;
	cout << "agility: " << agi << endl;

	cout << "The first gate is opening, counting down..." << endl;
	//   setup;    condition; incrementer/decrementer
	for (int i = 10; i >= 0; i--) {
		cout << i << "..." << endl;
	}

	//intro to functions
	cout << "In the first room stands a tall slender figure in a cloak." << endl;
	cout << "Totally skull faced. He speaks:" << endl;
	cout << "I will ask you 3 questions with various punishments if you get them wrong..." << endl;
	int dmg = puzzle1() + puzzle2(str, agi) + puzzle3(name);

	hp = hp - dmg;
	cout << "You are inflicted " << dmg << " points of damage! Your HP is now " << hp << endl;

	//build an object of class type Character
	Character testCharacter;
	testCharacter.setupStats(hp, str, def, agi);
	testCharacter.displayStats();

	Character testCharacter2;
	testCharacter2.setupStats(2343, 23, 34, 23);
	testCharacter2.displayStats();

	//testCharacter2.hp = 22;
	Hero hero;
	hero.setName(name);
	hero.setupStats(hp, str, def, agi);

	Glob glob1;//calls constructor and fills in base stats

	hero.takeDamage(glob1.getDamage());
	glob1.takeDamage(hero.getDamage());

	hero.displayStats();
	glob1.displayStats();
	glob1.makeDumbNoise();

	//class object pointers
	Glob* globPtr = new Glob();
	(*globPtr).displayStats();
	globPtr->takeDamage(3453);
	globPtr->displayStats();
	globPtr->makeDumbNoise();

	delete globPtr;
	globPtr = NULL;

	if (globPtr != NULL)
		cout << "glob ptr pointing to something" << endl;
	else
		cout << "glob is dead!!!" << endl;

	//POLYMORPHISM
	//reference glob as a character(treat child like parent)
	Character* charPtr = &glob1;
	charPtr->takeDamage(-5678);
	charPtr->displayStats();
	//casting - re-reference child type as another type in the family tree
	Glob* globPtr2 = (Glob*)charPtr;
	globPtr2->makeDumbNoise();

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//if init not return 0, then initialisation failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;

	}
	//initialise subsystems we need e.g sdl image, mixer, ttf
	//TODO: look up C++ bitwise logic
	//image- being able to deal with other image types other then bmp. Also lets you play with surface pixel data
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout << "SDL IMG Init Error: " << IMG_GetError() << endl;
		system("pause");
		return 1;
	}
	//ttf - text to font, for rendering text to screen
	if (TTF_Init() != 0)
	{
		cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
		system("pause");
		return 1;
	}
	//mixer- sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
		system("pause");
		return 1;
	}
	bool keeplooping = true;
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_Window* window = SDL_CreateWindow("GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);

		SDL_RenderClear(renderer);

		//the size graphics are at min, but then scale up to actual window size
		//SDL_RenderSetLogicalSize(renderer, 600, 400);


		SDL_Texture* testImg = IMG_LoadTexture(renderer, "assets/girlIdle.png");
		if (testImg == NULL)
		{
			cout << "Oh no" << IMG_GetError();
		}

		//Items(using arrays..) 0 = no item, 1 = choclate, 2 = grenade, 3 = atk up, 4 = def up
		int items[10];

		for (int i = 0; i <= 9; i++)
		{
			items[i] = 0;
		}
		items[0] = 1;

		for (int i = 0; i <= 9; i++)
		{
			cout << "items[" << i << "] = " << items[i] << endl;
		}

		if (TTF_Init() != 0)
		{
			cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
			system("pause");
			return 1;
		}

		//setup map
		MapScreen mapScreen(renderer, &hero, items);

		while (keeplooping)
	{
		//the region of the texture we want to draw from
		SDL_Rect srcRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 107; //ACC. TO IMAGE SIZE
		srcRect.h = 137;

		//destination
		SDL_Rect destRect;
		destRect.x = 70;
		destRect.y = 20;
		destRect.w = 107; //ACC. TO IMAGE SIZE
		destRect.h = 137;

		//render copy renders texture to the window
		SDL_RenderCopy(renderer, testImg, &srcRect, &destRect);

		//update mapscreen
		mapScreen.update();
		if (mapScreen.quit)
		{
			keeplooping = false;
		}
		mapScreen.draw();
		SDL_RenderPresent(renderer);



	}
	SDL_DestroyTexture(testImg);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;


}