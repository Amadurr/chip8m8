/* bool opN(CH8 CH,unsigned short opcode) // N = First letter of opcode
{
    CODE HERE
} */


#include <stdlib.h>
#include "app.h"

bool cpuNULL(CH8 *CH,unsigned short opcode)
{
    //do nothing
    printf("not an opcode");
    return false;
}

bool(*opcodes[16])(CH8 *CH,unsigned short opcode) =
        {
        op0, op1, op2, op3,
        op4, op5, op6, op7,
        op8, op9/*, opA, opB,
        opC, opD, opE, opF*/
        };

bool(*arit[16])(CH8 *CH,unsigned short opcode) =
        {
        arit0, arit1, arit2,
        arit3, arit4, arit5,
        arit6, arit7, cpuNULL,
        cpuNULL, cpuNULL, cpuNULL,
        cpuNULL, cpuNULL, aritE
        };



bool op0(CH8 *CH,unsigned short opcode) {
    switch (opcode & 0x000f) {
        case 0x0000:    //00E0  v
            for (int i = 0; i < 32*64; i++)
                CH->gfx[i] = 0x00;
            CH->pc += 2;
            return true;
        case 0x000e:    //00EE  v
            CH->pc = CH->stack[CH->sp];
            CH->pc += 2;
            return true;

        case 0x000F:    // reg dump test opcode
            printf("initializing reg dump...\n");

            printf("pc = %i\n", CH->pc);
            printf("sp = %i\n", CH->sp);
            printf("opcode = %i\n", CH->opcode);
            printf("I = %i\n", CH->I);
            printf("-------------\n-------------\n");
            for(int i = 0; i < 0xf; i++)
            {
                printf("V%x = %i\n",i , CH->V[i]);
            }
            printf("-------------\n-------------\n");
            printf("Stack:\n");

            for(int i = 0; i < 0xf; i++)
            {
                printf("%x = %i\n", i , CH->stack[i]);
            }
            printf("-------------\n-------------\n");
            printf("screendump..\n");
            for(int y = 0; y < 32;y++) {
                for (int x = 0; x < 64; x++)
                    printf("%02x", CH->gfx[(64 * y) + x]);
                printf("\n");
            }
            printf("-------------\n-------------\n");
            printf("press a key to contune");
            getchar();
            CH->pc += 2;
            return true;
            CH->run = false;

        default:
            printf("youdungoofed");
            return false;
    }
}

bool op1(CH8 *CH,unsigned short opcode)
{
    CH->pc = opcode & 0x0FFF;
    return true;
}

bool op2(CH8 *CH,unsigned short opcode)
{
    CH->stack[++CH->sp] = CH->pc;
    CH->pc = opcode & 0x0FFF;
    return true;
}

bool op3(CH8 *CH,unsigned short opcode)
{
    if((CH->V[(opcode & 0x0f00) >> 8]) == (opcode & 0x00ff))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op4(CH8 *CH,unsigned short opcode)
{
    if((CH->V[(opcode & 0x0f00) >> 8]) != (opcode & 0x00ff))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op5(CH8 *CH,unsigned short opcode)
{
    if((CH->V[(opcode & 0x0f00) >> 8]) == (CH->V[(opcode & 0x00f0) >> 4]))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op6(CH8 *CH,unsigned short opcode)
{
    CH->V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff);
    CH->pc += 2;
    return true;
}

bool op7(CH8 *CH,unsigned short opcode)
{
    CH->V[(opcode & 0x0f00) >> 8] += (opcode & 0x00ff);
    CH->pc += 2;
    return true;
}
bool op8(CH8 *CH, unsigned short opcode)
{
    arit[(CH->opcode&0xF)](CH, CH->opcode);
    return true;
}
bool op9(CH8 *CH, unsigned short opcode)
{
    if((CH->V[(opcode & 0x0f00) >> 8]) != (CH->V[(opcode & 0x00f0) >> 4]))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}




bool arit0(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}
<<<<<<< HEAD
<<<<<<< HEAD

bool opA(CH8 CH,unsigned short opcode) //Sets I to the address NNN.
{
CH.I = opcode & 0x0FFF;
CH.pc += 2;
return true;
}
bool opB(CH8 CH,unsigned short opcode) //Jumps to the address NNN plus V0.
{
    CH.pc = (opcode & 0x0FFF) + CH.V[0];
    return true;
}
bool opC(CH8 CH,unsigned short opcode) //Sets VX to the result of a bitwise and operation on a random number and NN.
{
    CH.V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
    return true;
}
bool opEX9E(CH8 CH,unsigned short opcode) //Skips the next instruction if the key stored in VX is pressed
{
    if(CH.key[CH.V[(opcode & 0x0F00) >> 8]] != 0)
        CH.pc += 4;
    else
        CH.pc += 2;
    return true;
}
bool opEXA1(CH8 CH,unsigned short opcode) //Skips the next instruction if the key stored in VX isn't pressed
{
    if(CH.key[CH.V[(opcode & 0x0F00) >> 8]] == 0)
        CH.pc += 4;
    else
        CH.pc += 2;
    return true;
}


=======
=======

bool opA(CH8 *CH,unsigned short opcode) //Sets I to the address NNN.
{
CH->I = opcode & 0x0FFF;
CH->pc += 2;
    return true;
}

bool opB(CH8 *CH,unsigned short opcode) //Jumps to the address NNN plus V0.
{
    CH->pc = (opcode & 0x0FFF) + CH->V[0];
    return true;
}

bool opC(CH8 *CH,unsigned short opcode) //Sets VX to the result of a bitwise and operation on a random number and NN.
{
    CH->V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
    return true;
}

bool opEX9E(CH8 *CH,unsigned short opcode) //Skips the next instruction if the key stored in VX is pressed
{
    if(CH->key[CH->V[(opcode & 0x0F00) >> 8]] != 0)
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool opEXA1(CH8 *CH,unsigned short opcode) //Skips the next instruction if the key stored in VX isn't pressed
{
    if(CH->key[CH->V[(opcode & 0x0F00) >> 8]] == 0)
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

>>>>>>> testtest
bool arit1(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) | (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit2(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) & (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit3(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) ^ (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit4(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    if (CH->V[(opcode & 0x0f00) >> 8] + (CH->V[(opcode & 0x00f0) >> 4]) >= 256)
        CH->V[0xf] = 1;
    else
        CH->V[0xf] = 0;
    CH->V[(opcode & 0x0f00) >> 8] += CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}

bool arit5(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    if (CH->V[(opcode & 0x0f00) >> 8] < CH->V[(opcode & 0x00f0) >> 4])
        CH->V[0xf] = 0;
    else
        CH->V[0xf] = 1;
    CH->V[(opcode & 0x0f00) >> 8] -= CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}

bool arit6(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[0xf] = CH->V[(opcode & 0x0f00) >> 8] & 0x1;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x0f00) >> 8] >> 1;

    CH->pc += 2;
    return true;
}

bool arit7(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    if (CH->V[(opcode & 0x0f00) >> 8] > CH->V[(opcode & 0x00f0) >> 4])
        CH->V[0xf] = 0;
    else
        CH->V[0xf] = 1;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x00f0) >> 4] - CH->V[(opcode & 0x0f00) >> 8] ;
    CH->pc += 2;
    return true;
}

bool aritE(CH8 *CH,unsigned short opcode) // N = First letter of opcode
{
    CH->V[0xf] = CH->V[(opcode & 0x0f00) >> 8] >> 7;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x0f00) >> 8] << 1;
    CH->pc += 2;
    return true;
}
<<<<<<< HEAD
>>>>>>> testtest
=======

>>>>>>> testtest
