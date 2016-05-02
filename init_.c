//
// Created by Kringle on 04/04/2016.
//
#include "app.h"

#include <strings.h>


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
    CH->drawFlag = false;

    load(CH, "TETRIS");



    if(!gfxInit(CH))

    {
        fprintf(stderr, "failed to initiate GFX");
        return false;
    }



    return true;
}