# The VACA Game Framework SDL2 Wrapper
VACA by Noel Nimstad is marked with CC0 1.0 Universal 

## Planned features
- Tilemaps
- Keyboard managing
- Rect drawing
- Save file utilities

## ⚠️ Warning
Only compatible with GCC compilers for now because of compiler macros!

## Example program
```c
#include "VACA/VACA.h"

#define SPEED 300

int main(int argc, char *argv[])
{
    VACA *V = VACA_Initialize("Test Window", 320, 240, 1, 60); // Initializes a window at 320x240, scale 1, 60fps target frame rate

    unsigned char running = 1;
    float frame = 0;
    while(running)
    {
        VACA_StartFrame(V); // Start the framerate maintaining function

        while(VACA_PollEvent(V)) // macro for SDL_PollEvent(V -> event)
        {
            if(V->event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        frame += V->deltaTime * SPEED;
        if(frame > 255) frame = 0;
        VACA_ClearScreen(V, floor(frame), floor(frame), 0); // Clear the screen with RGB color floor(frame), floor(frame), 0

        VACA_RenderPresent(V); // Present what has been drawn
        VACA_EndFrame(V); // End the framerate maintaining function
    }

    VACA_Destroy(V); // De-initialize VACA

    return 0;
}
```
