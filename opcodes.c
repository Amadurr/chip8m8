/* bool opN(CH8 CH,unsigned short opcode) // N = First letter of opcode
{
    CODE HERE
} */


#include <stdlib.h>
#include "app.h"
#define DEBUG 1
#define decon_print(x, ...){if (DEBUG) printf(x, __VA_ARGS__);}

bool cpuNULL(CH8 *CH,unsigned short opcode)
{
    //do nothing
    printf("%04x is not an opcode", opcode);
    return false;
}

bool(*opcodes[16])(CH8 *CH,unsigned short opcode) =
        {
        op0, op1, op2, op3,
        op4, op5, op6, op7,
        op8, op9, opA, opB,
        opC, opD, opE, opF
        };

bool(*arit[16])(CH8 *CH,unsigned short opcode) =
        {
        arit0, arit1, arit2,
        arit3, arit4, arit5,
        arit6, arit7, cpuNULL,
        cpuNULL, cpuNULL, cpuNULL,
        cpuNULL, cpuNULL, aritE
        };

bool(*FX[7][16])(CH8 *CH,unsigned short opcode) =
        {
                {
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, FX07,
                cpuNULL, cpuNULL, FX0A, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, FX15, cpuNULL, cpuNULL,
                FX18, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, FX1E, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, FX29, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, FX33,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, FX55, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                },{
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, FX65, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL,
                cpuNULL, cpuNULL, cpuNULL, cpuNULL
                }
        };


bool op0(CH8 *CH,unsigned short opcode) {
    switch (opcode & 0x000F) {
        case 0x0000:    //00E0  v
            decon_print("CLS\n",NULL);
            for (int i = 0; i < 32*64; i++)
                CH->gfx[i] = 0x00;
            CH->pc += 2;
            CH->drawFlag = true;
            return true;
        case 0x000e:    //00EE  v
            decon_print("RET\n",NULL);
            if(CH->sp == 0)
            {
                fprintf(stderr, "Cant return when not in subroutine, Exiting");
                return false;
            }
            CH->pc = CH->stack[--CH->sp];
            CH->pc += 2;

            return true;

        case 0x000F:    // reg dump test opcode
            decon_print("DMP\n",NULL);
            printf("initializing reg dump...\n");

            printf("pc = %i\n", CH->pc);
            printf("sp = %i\n", CH->sp);
            printf("opcode = %i\n", CH->opcode);
            printf("I = %i\n", CH->I);
            printf("DT = %i\n", CH->DT);
            printf("ST = %i\n", CH->ST);
            printf("-------------\n-------------\n");
            for(int i = 0; i < 0x10; i++)
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
                    printf("%2x", CH->gfx[(64 * y) + x]);
                printf("\n\n");
            }
            printf("-------------\n-------------\n");
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
    decon_print("JP %03x\n", (opcode & 0x0FFF));
    CH->pc = opcode & 0x0FFF;
    return true;
}

bool op2(CH8 *CH,unsigned short opcode)
{
    decon_print("CALL %03x\n", (opcode & 0x0FFF));
    if (CH->sp >= 0xF)
    {
        fprintf(stderr,"stack is full, cant start more subroutines, exiting...");
        return false;
    }
    CH->stack[CH->sp++] = CH->pc;
    CH->pc = opcode & 0x0FFF;
    return true;
}

bool op3(CH8 *CH,unsigned short opcode)
{
    decon_print("SE V%01x, %02x\n", (opcode & 0x0F00)>>8, (opcode & 0x00FF));
    if((CH->V[(opcode & 0x0f00) >> 8]) == (opcode & 0x00ff))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op4(CH8 *CH,unsigned short opcode)
{
    decon_print("SNE V%01x, %02x\n", (opcode & 0x0F00)>>8, (opcode & 0x00FF));
    if((CH->V[(opcode & 0x0f00) >> 8]) != (opcode & 0x00ff))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op5(CH8 *CH,unsigned short opcode)
{
    decon_print("SE V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    if((CH->V[(opcode & 0x0f00) >> 8]) == (CH->V[(opcode & 0x00f0) >> 4]))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool op6(CH8 *CH,unsigned short opcode)
{
    decon_print("LD V%01x, %02x\n", (opcode & 0x0F00)>>8, (opcode & 0x00FF));
    CH->V[(opcode & 0x0f00) >> 8] = (opcode & 0x00ff);
    CH->pc += 2;
    return true;
}

bool op7(CH8 *CH,unsigned short opcode)
{
    decon_print("ADD V%01x, %02x\n", (opcode & 0x0F00)>>8, (opcode & 0x00FF));
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
    decon_print("SNE V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    if((CH->V[(opcode & 0x0f00) >> 8]) != (CH->V[(opcode & 0x00f0) >> 4]))
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}


bool opA(CH8 *CH,unsigned short opcode) //Sets I to the address NNN.
{
    decon_print("LD I, %03x\n", (opcode & 0x0FFF));
    CH->I = opcode & 0x0FFF;
    CH->pc += 2;
    return true;
}
bool opB(CH8 *CH,unsigned short opcode) //Jumps to the address NNN plus V0.
{
    decon_print("JP V0, %03x\n", (opcode & 0x0FFF));
    CH->pc = (opcode & 0x0FFF) + CH->V[0];
    return true;
}
bool opC(CH8 *CH,unsigned short opcode) //Sets VX to the result of a bitwise and operation on a random number and NN.
{
    decon_print("RND V%01x, %02x\n", (opcode & 0x0F00)>>8, (opcode & 0x00FF));
    CH->V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
    CH->pc += 2;
    return true;
}

//UuW
bool opD(CH8 *CH,unsigned short opcode)
{
    decon_print("DRW V%01x, V%01x, %01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4, (opcode & 0x000F));
    unsigned char sprite;

//    unsigned short shift;
    unsigned short x = CH->V[(opcode & 0x0F00) >> 8];
    unsigned short y = CH->V[(opcode & 0x00F0) >> 4];
    CH->V[0xF] = 0;
    for(int yLine = 0; yLine < (opcode&0x000F); yLine++)
    {
        sprite = CH->Memory[CH->I + yLine];

        for(int xLine = 0; xLine < 8; xLine++)
        {
            if((sprite & ((0x80 >> xLine))) && (((x + xLine) + ((y + yLine) * 64)) < (32*64)))
            {
                if (CH->gfx[(x + xLine) + (y + yLine) * 64] == 1)
                    CH->V[0xF] = 1;

                CH->gfx[(x + xLine) + (y + yLine) * 64] ^= 1;
            }
        }
    }
    CH->drawFlag = true;
    CH->pc += 2;
    return true;
}
//UuW



bool opE(CH8 *CH, unsigned short opcode)
{
    if ((opcode & 0x00FF) == 0x9E)
        return opEX9E(CH, opcode);
    else if((opcode & 0x00Ff) == 0xA1)
        return opEXA1(CH, opcode);
    else
        return false;
}

bool opF(CH8 *CH, unsigned short opcode)
{
    FX[(opcode & 0x00F0) >> 4 ][opcode & 0x000F](CH, CH->opcode);
    return true;
}

bool opEX9E(CH8 *CH,unsigned short opcode)//Skips the next instruction if the key stored in VX is pressed

{
    decon_print("SKP V%01x\n", (opcode & 0x0F00)>>8);
    if(CH->key[CH->V[(opcode & 0x0F00) >> 8]] != 0)
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool opEXA1(CH8 *CH,unsigned short opcode) //Skips the next instruction if the key stored in VX isn't pressed
{
    decon_print("SKNP V%01x\n", (opcode & 0x0F00)>>8);
    if(CH->key[CH->V[(opcode & 0x0F00) >> 8]] == 0)
        CH->pc += 4;
    else
        CH->pc += 2;
    return true;
}

bool FX07(CH8 *CH,unsigned short opcode)
{
    decon_print("LD V%01x, %02x\n", (opcode & 0x0F00)>>8, CH->DT);
    CH->V[(opcode & 0x0f00) >> 8] = CH->DT;
    CH->pc += 2;
    return true;
}

bool FX0A(CH8 *CH,unsigned short opcode)
{

    for(int i = 0; i <= 0xF; i++)
        if(CH->key[i])
        {
            decon_print("LD V%01x, %01x\n", (opcode & 0x0F00)>>8, i);
            CH->V[(opcode & 0x0f00) >> 8] = i;
            CH->pc += 2;

        }
    return true;
}

bool FX15(CH8 *CH,unsigned short opcode)
{
    decon_print("LD DT, V%01x\n", (opcode & 0x0F00)>>8);
    CH->DT = CH->V[(opcode & 0x0f00) >> 8];
    CH->pc += 2;
    return true;
}

bool FX18(CH8 *CH,unsigned short opcode)
{
    decon_print("LD ST, V%01x\n", (opcode & 0x0F00)>>8);
    CH->ST = CH->V[(opcode & 0x0f00) >> 8];
    CH->pc += 2;
    return true;
}

bool FX1E(CH8 *CH,unsigned short opcode)
{
    decon_print("ADD I, V%01x\n", (opcode & 0x0F00)>>8);
    CH->I += CH->V[(opcode & 0x0f00) >> 8];
    CH->pc += 2;
    return true;
}

bool FX29(CH8 *CH,unsigned short opcode)
{
    decon_print("LD F, V%01x\n", (opcode & 0x0F00)>>8);
    CH->I = CH->V[(opcode & 0x0f00) >> 8] * 5;
    CH->pc += 2;
    return true;
}

bool FX33(CH8 *CH,unsigned short opcode)
{
    decon_print("LD B, V%01x\n", (opcode & 0x0F00)>>8);
    unsigned short Vval = CH->V[(opcode & 0x0F00) >> 8];
    CH->Memory[CH->I] = Vval /100;
    CH->Memory[CH->I+1] = (Vval % 100) / 10;
    CH->Memory[CH->I+2] = Vval % 10;
    CH->pc += 2;
    return true;
}

bool FX55(CH8 *CH,unsigned short opcode)
{
    decon_print("LD [I], V%01x\n", (opcode & 0x0F00)>>8);
    for (int i = 0; i <= ((opcode & 0x0f00) >> 8); i++)
        CH->Memory[CH->I + i] = CH->V[i];
    CH->pc += 2;
    return true;
}

bool FX65(CH8 *CH,unsigned short opcode)
{
    decon_print("LD V%01x, [I]\n", (opcode & 0x0F00)>>8);
    for (int i = 0; i <= ((opcode & 0x0f00) >> 8); i++)
        CH->V[i] = CH->Memory[CH->I + i];
    CH->pc += 2;
    return true;
}




bool arit0(CH8 *CH,unsigned short opcode)
{
    decon_print("LD V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}

bool arit1(CH8 *CH,unsigned short opcode)
{
    decon_print("OR V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) | (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit2(CH8 *CH,unsigned short opcode)
{
    decon_print("AND V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) & (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit3(CH8 *CH,unsigned short opcode)
{
    decon_print("XOR V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[(opcode & 0x0f00) >> 8] = (CH->V[(opcode & 0x0f00) >> 8]) ^ (CH->V[(opcode & 0x00f0) >> 4]);
    CH->pc += 2;
    return true;
}

bool arit4(CH8 *CH,unsigned short opcode)
{
    decon_print("ADD V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    if (CH->V[(opcode & 0x0f00) >> 8] + (CH->V[(opcode & 0x00f0) >> 4]) >= 256)
        CH->V[0xf] = 1;
    else
        CH->V[0xf] = 0;
    CH->V[(opcode & 0x0f00) >> 8] += CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}

bool arit5(CH8 *CH,unsigned short opcode)
{
    decon_print("SUB V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    if ((CH->V[(opcode & 0x0f00) >> 8] < CH->V[(opcode & 0x00f0) >> 4]))
        CH->V[0xf] = 0;
    else
        CH->V[0xf] = 1;
    CH->V[(opcode & 0x0f00) >> 8] -= CH->V[(opcode & 0x00f0) >> 4];
    CH->pc += 2;
    return true;
}

bool arit6(CH8 *CH,unsigned short opcode)
{
    decon_print("SHR V%01x{, V%01x}\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[0xf] = CH->V[(opcode & 0x0f00) >> 8] & 0x1;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x0f00) >> 8] >> 1;

    CH->pc += 2;
    return true;
}

bool arit7(CH8 *CH,unsigned short opcode)
{
    decon_print("SUBN V%01x, V%01x\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    if (CH->V[(opcode & 0x0f00) >> 8] > CH->V[(opcode & 0x00f0) >> 4])
        CH->V[0xf] = 0;
    else
        CH->V[0xf] = 1;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x00f0) >> 4] - CH->V[(opcode & 0x0f00) >> 8] ;
    CH->pc += 2;
    return true;
}

bool aritE(CH8 *CH,unsigned short opcode)
{
    decon_print("SHL V%01x {, V%01x}\n", (opcode & 0x0F00)>>8, (opcode & 0x00F0)>>4);
    CH->V[0xf] = CH->V[(opcode & 0x0f00) >> 8] >> 7;
    CH->V[(opcode & 0x0f00) >> 8] = CH->V[(opcode & 0x0f00) >> 8] << 1;
    CH->pc += 2;
    return true;
}


