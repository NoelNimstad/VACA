#include "VACA/VACA.h"

int main(int argc, char const *argv[])
{
    VACA *V = VACA_Initialize("Tilemap", 320, 240, 1, 60);
    VACA_SetRenderDrawColor(V, 0, 0, 0);

    char *contents = ReadFile("Resources/map.txt");
    Spritesheet *spritesheet = VACA_CreateSpritesheet(V, "Resources/map.png", 30, 30, 10, 10, 0, 0);

    Tilemap *tilemap = VACA_CreateTilemap(contents, spritesheet);

    unsigned char running = 1;
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

        VACA_ClearScreen2(V);
        VACA_RenderPresent(V);
        VACA_EndFrame(V);
    }

    VACA_DestroyTilemap(tilemap);
    VACA_Destroy(V);

    free(contents);

    return 0;
}