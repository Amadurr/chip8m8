//
// Created by Kringle on 02/05/2016.
//
#include "app.h"
bool loop(CH8 *CH)
{
    //Fetch opcode
    CH->opcode = CH->Memory[CH->pc]<<8 | CH->Memory[CH->pc+1];

    //process opcode
    CH->run = opcodes[(CH->opcode&0xF000)>>12](CH, CH->opcode);

    //redraw if needed
    if(CH->drawFlag == true)
    {
        pixRender(CH);
        /*

        printf("-------------\n-------------\n");
        printf("screendump..\n");
        for(int y = 0; y < 32;y++) {

            for (int x = 0; x < 64; x++)
                printf("%2x", CH.gfx[(64 * y) + x]);
            printf("\n");
        }
        printf("-------------\n-------------\n");*/
        CH->time = delay(CH->time);
        CH->drawFlag = false;

    }
    if (CH->ST != 0)
    {
        //do sound
        CH->ST -= 1;
    }
    if (CH->DT != 0)
    {
        CH->DT -= 1;
    }
    return true;
}