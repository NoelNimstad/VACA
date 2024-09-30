/*
    TODO:
    - Ball collisions
    - Winning
*/

#include "VACA/VACA.h"

struct
{
    VACA *V;
} Game;

void init()
{
    Game.V = VACA_Initialize("Two Ball", 400, 300, 2, 10);
}

int main(int argc, char const *argv[])
{
    init();

    VACA_SetRenderDrawColor(Game.V, 0, 0, 0);
    Tilemap *tilemap = VACA_CreateTilemap(Game.V, "assets/tilemaps/map.txt", "assets/tilemaps/map.png");

    unsigned char running = 1;
    while(running)
    {
        VACA_StartFrame(Game.V);

        while(VACA_PollEvent(Game.V))
        {
            if(Game.V -> event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        VACA_ClearScreen2(Game.V);
        VACA_RenderPresent(Game.V);
        VACA_EndFrame(Game.V);
    }

    VACA_DestroyTilemap(tilemap);
    VACA_Destroy(Game.V);

    return 0;
}