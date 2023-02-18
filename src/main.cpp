#include <SDL.h>
#include "Engine/Engine.h"
int main(int argc, char *argv[])
{  
    Engine E1;
    E1.init();
    SDL_Quit();
    return 0;
}
