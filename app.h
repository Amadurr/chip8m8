//
// Created by Kringle on 04/04/2016.
//

#ifndef CHIP8_TEMP_APP_H
#define CHIP8_TEMP_APP_H

#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct{
    char title[200];
    unsigned short pc;
    unsigned short sp;
    unsigned short opcode;
    unsigned short I;
    unsigned short stack[12];

    unsigned char Memory[0x1000];
    unsigned char key[16];
    unsigned char gfx[64 * 32];
    unsigned char V[16];
    unsigned char delay_timer;
    unsigned char sound_timer;

    int screenWidth;
    int screenHeight;

    SDL_Window* window;
    SDL_Renderer* renderer;
}CH8;


bool init(CH8 *CH);

#endif //CHIP8_TEMP_APP_H
