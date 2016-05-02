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
