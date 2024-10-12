# The VACA Game Framework SDL2 Wrapper
VACA by Noel Nimstad is marked with CC0 1.0 Universal 

## Planned features
- Tilemaps
- Keyboard managing
- Rect drawing

## ⚠️ Warning
Only compatible with GCC compilers for now because of compiler macros!

## Example program
```c
#include "VACA/VACA.h"

#define SPEED 300

int main(int argc, char *argv[])
{
    // Initialize a window at 320x240, scale 2, 60fps target frame rate
    VACA *V = VACA_Initialize("Test Window", 320, 240, 2, 60);

    u8 running = 1; // typedef unsigned char u8;
    float frame = 0;
    while(running)
    {
        // To maintain framerate, call the VACA_StartFrame() method in the begining of each frame
        // And then call the VACA_EndFrame() method at the end of each frame.
        VACA_StartFrame(V);

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
        VACA_EndFrame(V); // VACA_EndFrame()
    }

    VACA_Destroy(V); // De-initialize VACA

    return 0;
}
```
