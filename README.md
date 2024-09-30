# The VACA Game Framework SDL2 Wrapper
VACA by Noel Nimstad is marked with CC0 1.0 Universal 

## Planned features
- Tilemaps

## Example program
```c
#include "VACA/VACA.h"

#define SPEED 300

int main(int argc, char const *argv[])
{
    VACA *V = VACA_Initialize("Test Window", 320, 240, 1, 60);

    unsigned char running = 1;
    float frame = 0;
    while(running)
    {
        VACA_StartFrame(V);

        while(VACA_PollEvent(V))
        {
            if(V -> event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        frame += V -> deltaTime * SPEED;
        if(frame > 255) frame = 0;
        VACA_ClearScreen(V, floor(frame), floor(frame), 0);

        VACA_RenderPresent(V);
        VACA_EndFrame(V);
    }

    VACA_Destroy(V);

    return 0;
}
```
