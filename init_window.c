//
// Created by Kringle on 02/05/2016.
//
<<<<<<< HEAD

=======
#include "app.h"


bool gfxInit(CH8* CH)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL failed to initialize: %s\n", SDL_GetError());
        return false;
    }




    CH->window = SDL_CreateWindow(
            CH->title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CH->screenWidth,
            CH->screenHeight,
            SDL_WINDOW_OPENGL);

    if(CH->window == NULL)
    {
        printf("SDL failed to create window: %s\n", SDL_GetError());
        return false;
    }
    CH->gl_context = SDL_GL_CreateContext(CH->window);
    printf("Using opengl version %s.\n", glGetString(GL_VERSION));
    return true;
}
>>>>>>> a363ddba87d3b2b1d394837d5fcf161c3406388a