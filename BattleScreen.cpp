#include "BattleScreen.h"
#include <iostream>
using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType)
{
    if (enemyType != globType && enemyType!= mimicType)//just casual error prevention
    {
        enemyType = globType;
    }

    this->renderer = renderer;
    this->hero = hero;
    this->items = items;

    // Load background texture
    backgroundTexture = IMG_LoadTexture(renderer, "assets/bg.png");
    if (!backgroundTexture) {
        cout << "Failed to load background texture: " << IMG_GetError() << endl;
    }

    // Create Name Texture
    TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
    else {
        SDL_Color textColor = { 0, 0, 0, 255 };
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, hero->getName().c_str(), textColor);
        if (!textSurface) {
            cout << "Failed to create text surface: " << TTF_GetError() << endl;
        }
        else {
            nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (!nameTexture) {
                cout << "Failed to create texture from surface: " << SDL_GetError() << endl;
            }
            else {
                SDL_FreeSurface(textSurface);
                // Setup name texture drawing destination rectangle
                nameRect.x = 90;
                nameRect.y = 180;
                SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);

                heroAnimationsSet.setup(renderer, 47, 181, heroType);
                enemyAnimationSet.setup(renderer, 246, 114, enemyType);

                if (enemyType == globType)
                    enemy = new Glob();
                else if (enemyType == mimicType)
                    enemy = new Mimic();


                //setup health bars
                heroHP.setup(renderer, 90, 194);
                enemyHP.setup(renderer, 190, 10);

                //setup buttons
                fightButton.setup(renderer, { 0,180,80,30 }, "Fight");
                fightButton.selected = true;
                itemButton.setup(renderer, { 0,210,80,30 }, "Item");
            }
        }
        TTF_CloseFont(font);
    }
}

BattleScreen::~BattleScreen() {
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (nameTexture) SDL_DestroyTexture(nameTexture);
}

void BattleScreen::update() 
{   

    //deltatime
    float dt = 0;
    //last time we worked out deltatime
    Uint32 lastUpdate = SDL_GetTicks();

    while (!battleFinished) 
    {   
        Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
        dt = timeDiff / 1000.0f;
        lastUpdate = SDL_GetTicks(); //update this so we get correct diff

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) 
        {
            if (sdlEvent.type == SDL_QUIT) 
            {
                quit = true;
            }
            if (sdlEvent.type == SDL_KEYDOWN)
            {
                if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) 
                {
                    quit = true;
                }
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
                {
                    if (heroesTurn)
                    {
                        fightButton.selected = true;
                        itemButton.selected = false;
                    }
                }
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
                {
                    if (heroesTurn)
                    {
                        fightButton.selected = false;
                        itemButton.selected = true;
                    }
                }
            }
        }
        if (quit)
            battleFinished = true;

        //update animation
        heroAnimationsSet.update(dt);
        enemyAnimationSet.update(dt);

        //update health bars
        heroHP.hp = hero->getHP();
        heroHP.hpMax = hero->getHPMax();
        enemyHP.hp = enemy->getHP();
        enemyHP.hpMax = enemy->getHPMax();

        draw();
    }
}

void BattleScreen::draw() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
    SDL_RenderClear(renderer);

    // Draw background
    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    enemyAnimationSet.draw();

    heroAnimationsSet.draw();

    // UI bottom bar
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect bottomUIBar = { 0, 180, 320, 60 }; // x, y, w, h
    SDL_RenderFillRect(renderer, &bottomUIBar);
    // Draw border too
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bottomUIBar);

    // Draw name
    if (nameTexture) {
        SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);
        
    }
    else {
        cout << "Name texture is NULL" << endl;
    }
    heroHP.draw();
    enemyHP.draw();

    fightButton.draw();
    itemButton.draw();
    // Present frame to screen
    SDL_RenderPresent(renderer);

}
