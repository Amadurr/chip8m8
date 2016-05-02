//
// Created by Kringle on 04/04/2016.
//

#ifndef CHIP8_TEMP_APP_H
#define CHIP8_TEMP_APP_H

#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

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
    unsigned char DT;
    unsigned char ST;

    int screenWidth;
    int screenHeight;
    bool run;
    bool drawFlag;

    Uint32 time;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GLContext* gl_context;
    SDL_AudioSpec* audio;
    Uint8 *audio_pos;
    Uint32 audio_len;
}CH8;


// opcodes
bool(*opcodes[16])(CH8 *CH,unsigned short opcode);
bool(*arit[16])(CH8 *CH,unsigned short opcode);
bool(*FX[7][16])(CH8 *CH,unsigned short opcode);

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
bool op9(CH8 *CH,unsigned short opcode);
bool opA(CH8 *CH,unsigned short opcode);
bool opB(CH8 *CH,unsigned short opcode);
bool opC(CH8 *CH,unsigned short opcode);
bool opD(CH8 *CH,unsigned short opcode);
bool opE(CH8 *CH,unsigned short opcode);
bool opF(CH8 *CH,unsigned short opcode);

bool opEX9E(CH8 *CH,unsigned short opcode);
bool opEXA1(CH8 *CH,unsigned short opcode);
bool opEX9E(CH8 *CH,unsigned short opcode);
bool opEX9E(CH8 *CH,unsigned short opcode);


bool arit0(CH8 *CH,unsigned short opcode);
bool arit1(CH8 *CH,unsigned short opcode);
bool arit2(CH8 *CH,unsigned short opcode);
bool arit3(CH8 *CH,unsigned short opcode);
bool arit4(CH8 *CH,unsigned short opcode);
bool arit5(CH8 *CH,unsigned short opcode);
bool arit6(CH8 *CH,unsigned short opcode);
bool arit7(CH8 *CH,unsigned short opcode);
bool aritE(CH8 *CH,unsigned short opcode);

bool FX07(CH8 *CH,unsigned short opcode);
bool FX0A(CH8 *CH,unsigned short opcode);
bool FX15(CH8 *CH,unsigned short opcode);
bool FX18(CH8 *CH,unsigned short opcode);
bool FX1E(CH8 *CH,unsigned short opcode);
bool FX29(CH8 *CH,unsigned short opcode);
bool FX33(CH8 *CH,unsigned short opcode);
bool FX55(CH8 *CH,unsigned short opcode);
bool FX65(CH8 *CH,unsigned short opcode);


//GFX
bool gfxInit(CH8* CH);
void pixRender(CH8* CH);
Uint32 delay(Uint32 time);


//loop
bool loop(CH8* CH);
#endif //CHIP8_TEMP_APP_H
