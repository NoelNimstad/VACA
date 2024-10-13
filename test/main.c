#include "VACA/VACA.h"

mainFunction
{
    VACA *v = VACA_Initialize("tilemap", 320, 240, 2, 60);
    Tilemap *t = VACA_CreateTilemap(ReadFile("Resources/map.txt"),
                                    VACA_CreateSpritesheet(v, "Resources/map.png", 30, 30, 10, 10, 0, 0));
    VACA_SetRenderDrawColor(v, 0, 0, 0);

    u8 running = 1;
    u8 frame = 0;
    while(running)
    {
        VACA_StartFrame(v);

        while(VACA_PollEvent(v))
        {
            if(v->event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        VACA_ClearScreen2(v);  
        VACA_OffsetTilemap(t, ++frame, ++frame);                         
        VACA_DrawTilemap(v, t);
        VACA_RenderPresent(v);

        VACA_EndFrame(v);
    }

    VACA_DestroyTilemap(t);
    VACA_Destroy(v);
    return 0;
}