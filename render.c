//
// Created by Kringle on 02/05/2016.
//


#include "app.h"
void pixRender(CH8* CH)
{
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    for(int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if(CH->gfx[(y*64) + x] != 0)
            {
                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_QUADS);
                glVertex2f(x/32.0f-1, 1-y/16.0f);
                glVertex2f((x+1)/32.0f-1, 1-y/16.0f);
                glVertex2f((x+1)/32.0f-1,1-(y+1)/16.0f);
                glVertex2f(x/32.0f-1, 1-(y+1)/16.0f);
                glEnd();
                glPopMatrix();
            }
        }
    }
    SDL_GL_SwapWindow(CH->window);
    SDL_Delay(0);
}

Uint32 delay(Uint32 time)
{
    //Sleep(1);
    /*
     * float dt = 17;
    Uint32 newtime = SDL_GetTicks();
    while(newtime < time + dt)
    {
        newtime = SDL_GetTicks();
    }
    return newtime;*/
}

