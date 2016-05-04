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
        loop(&CH);
        printf("\nop:%04x I:%03x PC:%04x SP:%04x ",CH.opcode, CH.I, CH.pc,CH.sp);
        for(int i = 0; i <= 0xf; i++)
        {
            printf("V%01x:%02x ",i, CH.V[i]);
        }
        //getchar();
    }
    return 0;
}