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
        fprintf(stderr, "Memory error");
        return false;
    }

    size_t result = fread(buffer, 1, bufferSize, fp);
    if(result != bufferSize)
    {
        fprintf(stderr, "Reading error");
        return false;
    }
    if((0x1000-0x200) > bufferSize)
    {
        for (int i = 0; i < bufferSize; ++i)
            CH->Memory[i + 512] = buffer[i];
    }
    else
        printf("ROM too big!");
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
    if((CH->opcode&0xF0FF) == 0xf00A){
        scanf("%x",&CH->V[CH->opcode&0x0F00>>8]);
        CH->pc+=2;
    }

    else getchar();
}
