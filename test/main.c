#include "VACA/VACA.h"

int main(int argc, char *argv[])
{
    VACA *vaca = VACA_Initialize("test", 320, 240, 2, 60);

    u8 running = 1;
    while(running)
    {
        VACA_StartFrame(vaca);

        while(VACA_PollEvent(vaca))
        {
            if(vaca -> event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        VACA_ClearScreen(vaca, 0, 0, 0);

        VACA_SetRenderDrawColor(vaca, 255, 0, 0);
        VACA_DrawLine(vaca, 0, 0, 320, 240);

        VACA_RenderPresent(vaca);

        VACA_EndFrame(vaca);
    }

    VACA_Destroy(vaca);
    return 0;
}