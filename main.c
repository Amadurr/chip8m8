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

        //redraw if needed
        if(CH.drawFlag == true)
        {
            //proper render function here
            printf("-------------\n-------------\n");
            printf("screendump..\n");
            for(int y = 0; y < 32;y++) {
                for (int x = 0; x < 64; x++)
                    printf("%2x", CH.gfx[(64 * y) + x]);
                printf("\n");
            }
            printf("-------------\n-------------\n");
            CH.drawFlag = false;
        }
    }
    return 0;
}