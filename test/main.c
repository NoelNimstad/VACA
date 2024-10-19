#include "VACA/VACA.h"

int main(void)
{
    VACA *v = VACA_Initialize("tilemap", 320, 240, 1, 60);
    Spritesheet *s = VACA_CreateSpritesheet(v, "Resources/map.png", 10, 10, 0, 0);
    char *contents = readFile("Resources/map.txt");
    Tilemap *t = VACA_CreateTilemap(contents, s);

    SDL_Rect rect = { 100, 100, 100, 100 };

    getFileFromUserInput();

    u8 running = 1;
    float value = 0.0f;
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

        value += v->deltaTime * 100;
        u8 pos = (int)value % 255;

        VACA_SetRenderDrawColor(v, 0, 0, 0);
        VACA_ClearScreen2(v);  
        VACA_OffsetTilemap(t, 90, 300 - pos);                         
        VACA_DrawTilemap(v, t);
        VACA_SetRenderDrawColor(v, 200, 50, 50);
        VACA_FillRect(v, rect);
        VACA_RenderPresent(v);

        VACA_EndFrame(v);
    }

    VACA_DestroyTilemap(t);
    free(contents);
    VACA_DestroySpritesheet(s);
    VACA_Destroy(v);
    return 0;
}
