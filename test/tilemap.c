#include "VACA/VACA.h"

int main(int argc, char const *argv[])
{
    VACA *V = VACA_Initialize("Tilemap", 320, 240, 1, 60);

    char *contents = ReadFile("Resources/map.txt");
    printf("%s\n", contents);

    VACA_SetRenderDrawColor(V, 0, 0, 0);
    Tilemap *tilemap = VACA_CreateTilemap(V, "assets/tilemaps/map.txt", "assets/tilemaps/map.png");

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