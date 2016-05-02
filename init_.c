//
// Created by Kringle on 04/04/2016.
//
#include "app.h"

#define AUDIO_PATH "beep.wav"

bool init(CH8 *CH)
{
    CH->window = NULL;
    CH->renderer = NULL;
    strcpy(CH->title,"SDL2 ER PURE KREFT");
    CH->pc = 0x200;
    CH->sp = 0;
    CH->opcode = 0;
    CH->I = 0;
    for(int i = 0; i < 16 ; i++)
        CH->stack[i] = 0;
    for(int i = 0; i < 16 ; i++)
        CH->key[i] = 0;
    for(int i = 0; i < 16 ; i++)
        CH->V[i] = 0;
    for(int i = 0; i < 32*64 ; i++)
        CH->gfx[i] = 0;
    for(int i = 0; i < 0x1000 ; i++)
        CH->Memory[i] = 0;
    CH->drawFlag = true;

    load(CH, "test");


    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return false;
    }



/*
    CH->window = SDL_CreateWindow(
            CH->title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CH->screenWidth,
            CH->screenHeight,
            SDL_WINDOW_OPENGL);

    if(CH->window == NULL)
    {
        printf("SDL failed to create window: %s\n", SDL_GetError());
        return false;
    }

    CH->renderer = SDL_CreateRenderer(CH->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
*/

    return true;
}