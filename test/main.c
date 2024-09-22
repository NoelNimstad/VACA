#include <stdio.h>

#include "VACA/VACA.h"

#define WIDTH 400
#define HEIGHT 300

enum scenes
{
    VACA_Splash,
    TitleScreen
};

struct
{
    VACA *V;
    Sprite *sprites[2];
} Game;

void LoadGameAssets()
{
    Game.sprites[0] = VACA_CreateSprite(Game.V, "assets/logo.png", 300, 200, 0, 0);
    Game.sprites[1] = VACA_CreateSprite(Game.V, "assets/title.png", 256, 240, 0, 0);
}

int main(void)
{
    Game.V = VACA_Initialize("BOMBERMAN", 256, 240, 1, 60);
    LoadGameAssets();

    int running = 1;
    int frame = 0;
    enum scenes scene = VACA_Splash;
    while(running)
    {
        while(VACA_PollEvent(Game.V))
        {
            if(Game.V -> event.type == SDL_QUIT) { running = 0; };
        }

        VACA_ClearScreen(Game.V, 0, 0, 0);

        printf("%d\n", frame++);

        switch(scene)
        {
            case VACA_Splash:
                VACA_SetSpriteOpacity(Game.sprites[0], 255 * ((float)frame / 120.0f));
                VACA_DrawSprite(Game.V, Game.sprites[0]);
                if(frame > 120)
                {
                    scene = TitleScreen;
                    VACA_DestroySprite(Game.sprites[0]);
                }
                break;
            case TitleScreen:
                VACA_DrawSprite(Game.V, Game.sprites[1]);
                break;
        }

        VACA_RenderPresent(Game.V);
        VACA_MaintainFrameRate(Game.V);
    }

    VACA_DestroySprite(Game.sprites[1]);
    VACA_Destroy(Game.V);

    return 0;
}