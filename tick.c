//
// Created by Kringle on 02/05/2016.
//
#include "app.h"
bool loop(CH8 *CH) {
    //Fetch opcode
    CH->opcode = CH->Memory[CH->pc] << 8 | CH->Memory[CH->pc + 1];
    printf("\nop:%04x ",CH->opcode);
    //process opcode
    CH->run = opcodes[(CH->opcode & 0xF000) >> 12](CH, CH->opcode);



    //redraw if needed
    if (CH->drawFlag == true) {
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

        CH->drawFlag = false;

    }
    SDL_Delay(4);
    SDL_Event event;


    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    CH->key[0x1] = 1;
                    break;
                case SDLK_2:
                    CH->key[0x2] = 1;
                    break;
                case SDLK_3:
                    CH->key[0x3] = 1;
                    break;
                case SDLK_4:
                    CH->key[0xC] = 1;
                    break;
                case SDLK_q:
                    CH->key[0x4] = 1;
                    break;
                case SDLK_w:
                    CH->key[0x5] = 1;
                    break;
                case SDLK_e:
                    CH->key[0x6] = 1;
                    break;
                case SDLK_r:
                    CH->key[0xD] = 1;
                    break;
                case SDLK_a:
                    CH->key[0x7] = 1;
                    break;
                case SDLK_s:
                    CH->key[0x8] = 1;
                    break;
                case SDLK_d:
                    CH->key[0x9] = 1;
                    break;
                case SDLK_f:
                    CH->key[0xE] = 1;
                    break;
                case SDLK_z:
                    CH->key[0xA] = 1;
                    break;
                case SDLK_x:
                    CH->key[0x0] = 1;
                    break;
                case SDLK_c:
                    CH->key[0xB] = 1;
                    break;
                case SDLK_v:
                    CH->key[0xF] = 1;
                    break;
                case SDLK_ESCAPE:
                    exit(1);
                    break;
                default:
                    break;

            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    CH->key[0x1] = 0;
                    break;
                case SDLK_2:
                    CH->key[0x2] = 0;
                    break;
                case SDLK_3:
                    CH->key[0x3] = 0;
                    break;
                case SDLK_4:
                    CH->key[0xC] = 0;
                    break;
                case SDLK_q:
                    CH->key[0x4] = 0;
                    break;
                case SDLK_w:
                    CH->key[0x5] = 0;
                    break;
                case SDLK_e:
                    CH->key[0x6] = 0;
                    break;
                case SDLK_r:
                    CH->key[0xD] = 0;
                    break;
                case SDLK_a:
                    CH->key[0x7] = 0;
                    break;
                case SDLK_s:
                    CH->key[0x8] = 0;
                    break;
                case SDLK_d:
                    CH->key[0x9] = 0;
                    break;
                case SDLK_f:
                    CH->key[0xE] = 0;
                    break;
                case SDLK_z:
                    CH->key[0xA] = 0;
                    break;
                case SDLK_x:
                    CH->key[0x0] = 0;
                    break;
                case SDLK_c:
                    CH->key[0xB] = 0;
                    break;
                case SDLK_v:
                    CH->key[0xF] = 0;
                    break;
                default:
                    break;
            }
        }
    }

    if (CH->ST != 0) {
        printf("Beep!");
        CH->ST -= 1;
    }
    if (CH->DT != 0) {
        CH->DT -= 1;
    }
    return true;

}
