//
// Created by Kringle on 18/04/2016.
//

#include "app.h"
#include <stdlib.h>


bool load(CH8 *CH, const char *filename)
{
    FILE* fp;
    fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    long bufferSize = ftell(fp);
    rewind(fp);

    unsigned char * buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory error <- ");
        return false;
    }

    size_t result = fread(buffer, 1, bufferSize, fp);
    if(result != bufferSize)
    {
        fprintf(stderr, "Reading error <- ");
        return false;
    }
    if((0x1000-0x200) > bufferSize)
    {
        for (int i = 0; i < bufferSize; ++i)
            CH->Memory[i + 512] = buffer[i];
    }
    else
        printf("ROM too big <- ");
    fclose(fp);
    free(buffer);


    return true;
}

void deconstructor(CH8* CH)
{
    printf("I:%03x PC:%04x SP:%04x ",CH->I, CH->pc,CH->sp);
    for(int i = 0; i <= 0xf; i++)
    {
        printf("V%01x:%02x ",i, CH->V[i]);
    }
    printf("DT:%02x ST:%02x", CH->DT, CH->ST);
    if((CH->opcode&0xF0FF) == 0xf00A){
        scanf("%x",&CH->V[CH->opcode&0x0F00>>8]);
        CH->pc+=2;
    }

    else getchar();
}

void keypress(CH8 *CH)
{
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
}