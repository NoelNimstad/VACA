#include "VACA/VACA.h"

int main(void)
{
    VACA *v = VACA_Initialize("tilemap", 320, 240, 2, 60);
    Spritesheet *s = VACA_CreateSpritesheet(v, "Resources/map.png", 10, 10, 0, 0);
    char *contents = ReadFile("Resources/map.txt");
    Tilemap *t = VACA_CreateTilemap(contents, s);
    VACA_SetRenderDrawColor(v, 0, 0, 0);

    u8 running = 1;
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
        VACA_OffsetTilemap(t, 0, 0);                         
        VACA_DrawTilemap(v, t);
        VACA_RenderPresent(v);

        VACA_EndFrame(v);
    }

    VACA_DestroyTilemap(t);
    free(contents);
    VACA_DestroySpritesheet(s);
    VACA_Destroy(v);
    return 0;
}