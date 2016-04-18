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
    unsigned short stack[16];

    unsigned char Memory[0x1000];
    unsigned char key[16];
    unsigned char gfx[64 * 32];
    unsigned char V[16];
    unsigned char delay_timer;
    unsigned char sound_timer;

    int screenWidth;
    int screenHeight;
    bool run;
    bool drawFlag;

    SDL_Window* window;
    SDL_Renderer* renderer;
}CH8;

bool(*opcodes[16])(CH8 *CH,unsigned short opcode);
bool(*arit[16])(CH8 *CH,unsigned short opcode);

bool load(CH8* CH,const char *filename);

bool init(CH8 *CH);
/*
bool (*p[16]) (CH8 CH,unsigned short x);
bool (*a[9]) (CH8 CH,unsigned short x);*/

bool op0(CH8 *CH,unsigned short opcode);
bool op1(CH8 *CH,unsigned short opcode);
bool op2(CH8 *CH,unsigned short opcode);
bool op3(CH8 *CH,unsigned short opcode);
bool op4(CH8 *CH,unsigned short opcode);
bool op5(CH8 *CH,unsigned short opcode);
bool op6(CH8 *CH,unsigned short opcode);
bool op7(CH8 *CH,unsigned short opcode);
bool op8(CH8 *CH,unsigned short opcode);
bool op9(CH8 *CH,unsigned short opcode);/*
bool opA(CH8 *CH,unsigned short opcode);
bool opB(CH8 *CH,unsigned short opcode);
bool opC(CH8 *CH,unsigned short opcode);
bool opD(CH8 *CH,unsigned short opcode);
bool opE(CH8 *CH,unsigned short opcode);
bool opF(CH8 *CH,unsigned short opcode);*/

bool arit0(CH8 *CH,unsigned short opcode);
bool arit1(CH8 *CH,unsigned short opcode);
bool arit2(CH8 *CH,unsigned short opcode);
bool arit3(CH8 *CH,unsigned short opcode);
bool arit4(CH8 *CH,unsigned short opcode);
bool arit5(CH8 *CH,unsigned short opcode);
bool arit6(CH8 *CH,unsigned short opcode);
bool arit7(CH8 *CH,unsigned short opcode);
bool arit8(CH8 *CH,unsigned short opcode);
bool aritE(CH8 *CH,unsigned short opcode);

#endif //CHIP8_TEMP_APP_H
