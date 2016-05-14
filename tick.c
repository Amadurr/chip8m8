//
// Created by Kringle on 02/05/2016.
//
#include "app.h"
bool loop(CH8 *CH) {
    while(CH->run == true) {
        //Fetch opcode
        CH->opcode = CH->Memory[CH->pc] << 8 | CH->Memory[CH->pc + 1];
        printf("\nop:%04x ",CH->opcode);
        if(CH->opcode == 0x0000)
            return false;
        //process opcode
        CH->run = opcodes[(CH->opcode & 0xF000) >> 12](CH, CH->opcode);

        //Uncomment to debug
        //deconstructor(CH);


        //redraw if needed
        if (CH->drawFlag == true) {
            pixRender(CH);
        }
        SDL_Delay(1);
        keypress(CH);
        Uint32 newtime = SDL_GetTicks();

        if (newtime >= CH->time + 16) {
            if (CH->ST != 0) {
                CH->ST -= 1;
                printf("Beep!");
            }
            if (CH->DT != 0) {
                CH->DT -= 1;
            }
            CH->time = newtime;
        }
    }

    return true;

}
