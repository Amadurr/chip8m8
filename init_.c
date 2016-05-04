//
// Created by Kringle on 04/04/2016.
//
#include "app.h"

#include <strings.h>


#define AUDIO_PATH "beep.wav"

bool init(CH8 *CH)
{
    unsigned char fontSet[80] =
            {
                0x60, 0x90, 0x90, 0x90, 0x60, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0x60, 0x90, 0x20, 0x40, 0xF0, // 2
                0x60, 0x90, 0x20, 0x90, 0x60, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xE0, 0x10, 0xE0, // 5
                0x60, 0x80, 0xE0, 0x90, 0x60, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0x60, 0x90, 0x60, 0x90, 0x60, // 8
                0x60, 0x90, 0x70, 0x10, 0x60  // 9
            };
    CH->window = NULL;
    CH->renderer = NULL;
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
    for(int i = 0; i < 0x0200 ; i++)
        CH->Memory[i] = fontSet[i];
    CH->drawFlag = false;
    char ROM[20];
    printf("Please input a ROM name\n");
    scanf("%s", ROM);
    load(CH, ROM);
    strcpy(CH->title,ROM);



    if(!gfxInit(CH))

    {
        fprintf(stderr, "failed to initiate GFX");
        return false;
    }



    return true;
}