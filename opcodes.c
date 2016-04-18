/* bool opN(CH8 CH,unsigned short opcode) // N = First letter of opcode
{
    CODE HERE
} */


#include <stdlib.h>
#include "app.h"

bool op0(CH8 CH,unsigned short opcode) {
    switch (opcode & 0x000f) {
        case 0x0000:    //00E0  v
            for (int i = 0; i < 0x1000; i++)
                CH.gfx[i] = 0x00;
            CH.pc += 2;
            return true;
        case 0x000e:    //00EE  v
            CH.pc = CH.stack[CH.sp];
            CH.pc += 2;
            return true;
        default:
            printf("youdungoofed");
            return false;
    }
}

bool op1(CH8 CH,unsigned short opcode)
{
    CH.pc = opcode & 0x0FFF;
    return true;
}

bool op2(CH8 CH,unsigned short opcode)
{
    CH.stack[++CH.sp] = CH.pc;
    CH.pc = opcode & 0x0FFF;
    return true;
}

bool op3(CH8 CH,unsigned short opcode)
{
    if((CH.V[(opcode & 0x0f00) >> 8]) == (opcode & 0x00ff))
        CH.pc += 4;
    else
        CH.pc += 2;
    return true;
}

bool op4(CH8 CH,unsigned short opcode)
{
    if((CH.V[(opcode & 0x0f00) >> 8]) != (opcode & 0x00ff))
        CH.pc += 4;
    else
        CH.pc += 2;
    return true;
}

bool op5(CH8 CH,unsigned short opcode)
{
    if((CH.V[(opcode & 0x0f00) >> 8]) == (CH.V[(opcode & 0x00f0) >> 4]))
        CH.pc += 4;
    else
        CH.pc += 2;
    return true;
}

bool op6(CH8 CH,unsigned short opcode)
{
    CH.V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff);
    CH.pc += 2;
    return true;
}

bool op7(CH8 CH,unsigned short opcode)
{
    CH.V[(opcode & 0x0f00) >> 8] += (opcode & 0x00ff);
    CH.pc += 2;
    return true;
}

bool opA(CH8 CH,unsigned short opcode) //Sets I to the address NNN.
{
CH.I = opcode & 0x0FFF;
CH.pc += 2;
}
bool opB(CH8 CH,unsigned short opcode) //Jumps to the address NNN plus V0.
{
    CH.pc = (opcode & 0x0FFF) + CH.V[0];
}
bool opC(CH8 CH,unsigned short opcode) //Sets VX to the result of a bitwise and operation on a random number and NN.
{
    CH.V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
}
bool opEX9E(CH8 CH,unsigned short opcode) //Skips the next instruction if the key stored in VX is pressed
{
    if(CH.key[CH.V[(opcode & 0x0F00) >> 8]] != 0)
        CH.pc += 4;
    else
        CH.pc += 2;
}
bool opEXA1(CH8 CH,unsigned short opcode) //Skips the next instruction if the key stored in VX isn't pressed
{
    if(CH.key[CH.V[(opcode & 0x0F00) >> 8]] == 0)
        CH.pc += 4;
    else
        CH.pc += 2;
}


