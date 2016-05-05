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
        printf("I:%03x PC:%04x SP:%04x ",CH.I, CH.pc,CH.sp);
        for(int i = 0; i <= 0xf; i++)
        {
            printf("V%01x:%02x ",i, CH.V[i]);
        }
        if((CH.opcode&0xF0FF) == 0xf00A){
            scanf("%x",&CH.V[CH.opcode&0x0F00>>8]);
            CH.pc+=2;
        }

        getchar();



    }
    return 0;
}