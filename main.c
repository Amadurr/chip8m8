#include "app.h"
int main(int argc, char* argv[])
{
    CH8 CH;

    CH.screenWidth = 640;
    CH.screenHeight = 320;

    if(!init(&CH))
    {
        printf("EPICFAIL");
        return -1;
    }

    CH.run = true;

    loop(&CH);

    return 0;
}