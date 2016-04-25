//
// Created by Kringle on 14/03/2016.
//
#include "app.h"
int main(int argc, char* argv[])
{
    CH8 CH;

    CH.screenWidth = 640;
    CH.screenHeight = 320;

    if(!init(&CH))
    {
        printf("EPICFAIL");
    }

    CH.run = true;


    while(CH.run)
    {
        //Fetch opcode
        CH.opcode = CH.Memory[CH.pc]<<8 | CH.Memory[CH.pc+1];

        //process opcode
        CH.run = opcodes[(CH.opcode&0xF000)>>12](&CH, CH.opcode);


    }
    return 0;
}