/* bool opN(CH8 CH,unsigned short opcode) // N = First letter of opcode
{
    CODE HERE
} */

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

