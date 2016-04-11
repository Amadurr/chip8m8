//
// Created by Kringle on 04/04/2016.
//
#include "app.h"
bool init(CH8 *CH)
{
    CH->window = NULL;
    CH->renderer = NULL;
    strcpy(CH->title,"SDL2 ER PURE KREFT");
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return false;
    }

    CH->window = SDL_CreateWindow(
            CH->title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CH->screenWidth,
            CH->screenHeight,
            SDL_WINDOW_OPENGL
    );
    return true;
}