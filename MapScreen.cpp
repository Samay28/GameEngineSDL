#include "MapScreen.h"

MapScreen::MapScreen(SDL_Renderer* renderer, int* items) {
    this->renderer = renderer;
    this->items = items;

    for (int i = 0; i <= 9; i++) {
        for (int y = 0; y <= 9; y++) {
            map[i][y] = 0;
        }
    }

    std::fstream mapFile("assets/map.txt");
    if (mapFile.is_open()) {
        for (int y = 0; y <= 9; y++) {
            for (int i = 0; i <= 9; i++) {
                char grid;
                mapFile >> grid; // Read into grid, one by one

                if (grid == '0') {
                    map[i][y] = 0; // Wall
                }
                else {
                    map[i][y] = 1; // Land

                    if (grid == 'h') {
                        heroObj.type = 1;
                        heroObj.x = i;
                        heroObj.y = y;
                    }
                    else if (grid == 'd') {
                        door.type = 2;
                        door.x = i;
                        door.y = y;
                    }
                    else if (grid == 'c') {
                        MapObject chest;
                        chest.type = 5;
                        chest.x = i;
                        chest.y = y;
                        mapObjects.push_back(chest);
                    }
                    else if (grid == 'm') {
                        MapObject mimic;
                        mimic.type = 4;
                        mimic.x = i;
                        mimic.y = y;
                        mapObjects.push_back(mimic);
                    }
                    else if (grid == 'g') {
                        MapObject glob;
                        glob.type = 3;
                        glob.x = i;
                        glob.y = y;
                        mapObjects.push_back(glob);
              
                    }
                }
            }
        }
    }
    mapFile.close();

    // Load textures
    heroTexture = IMG_LoadTexture(renderer, "assets/girlTile.png");
    if (!heroTexture) {
        std::cout << "Failed to load hero texture: " << IMG_GetError() << std::endl;
    }

    doorTexture = IMG_LoadTexture(renderer, "assets/doorTile.png");
    if (!doorTexture) {
        std::cout << "Failed to load door texture: " << IMG_GetError() << std::endl;
    }

    globTexture = IMG_LoadTexture(renderer, "assets/globTile.png");
    if (!globTexture) {
        std::cout << "Failed to load glob texture: " << IMG_GetError() << std::endl;
    }

    chestTexture = IMG_LoadTexture(renderer, "assets/chestTile.png");
    if (!chestTexture) {
        std::cout << "Failed to load chest texture: " << IMG_GetError() << std::endl;
    }
}

MapScreen::~MapScreen() {
    SDL_DestroyTexture(heroTexture);
    SDL_DestroyTexture(globTexture);
    SDL_DestroyTexture(doorTexture);
    SDL_DestroyTexture(chestTexture);
}

void MapScreen::draw() {
    SDL_Rect tileRect = { 0, 0, 120, 105 };

    for (int i = 0; i <= 9; i++) {
        for (int y = 0; y <= 9; y++) {
            if (map[i][y] == 1) {
                SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            tileRect.x = i * tileRect.w;
            tileRect.y = y * tileRect.h;

            SDL_RenderFillRect(renderer, &tileRect);
        }
    }

    // Draw hero
    if (heroTexture) {
        tileRect.x = heroObj.x * tileRect.w;
        tileRect.y = heroObj.y * tileRect.h;
        SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);
    }

    // Draw door
    if (doorTexture) {
        tileRect.x = door.x * tileRect.w;
        tileRect.y = door.y * tileRect.h;
        SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
    }

    // Draw other map objects
    for (MapObject mo : mapObjects)
    {   
        if (mo.active)
        {
            tileRect.x = mo.x * tileRect.w;
            tileRect.y = mo.y * tileRect.h;
        }
        if (mo.type == 3)
        {
            SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
        }
        else
        {
            SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}
