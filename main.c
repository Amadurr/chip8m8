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
    while(CH.run)
    {
        CH.opcode = 0x1234;
        if((*p[(CH.opcode&0xf000)>>12])(CH,CH.opcode))
        {
            printf("opcode: %x failed", CH.opcode);
        }
    }
    getchar();
    return 0;
}