#include <stdio.h>
#include <stdlib.h>

#include "VACA/VACA.h"

enum scenes
{
    TitleScreen
};

struct
{
    VACA        *V;
    Sprite      *sprites[1];
    Spritesheet *spritesheets[1];

    int          frame;
    int          running;

    enum scenes  scene;
} Game;

void Initialize()
{
    Game.V = VACA_Initialize("BOOM MAN", 256, 240, 1, 30);

    Game.sprites[0] = VACA_CreateSprite(Game.V, 
                                        "assets/title.png", 
                                        256, 
                                        240, 
                                        0, 
                                        0);
    Game.spritesheets[0] = VACA_CreateSpritesheet(Game.V, 
                                                  "assets/alphanum1.png", 
                                                  208, 
                                                  16, 
                                                  8, 
                                                  8,
                                                  96, 
                                                  208);

    Game.frame = 0;
    Game.running = 1;

    Game.scene = TitleScreen;
}

char frameCounter[9] = ".........";
void GameLoop()
{
    while(VACA_PollEvent(Game.V))
    {
        if(Game.V -> event.type == SDL_QUIT) 
            Game.running = 0;
    }

    printf("%d %f\n", Game.frame++, Game.V -> deltaTime);

    switch(Game.scene)
    {
        case TitleScreen:

// TITLE SCREEN
VACA_DrawSprite(Game.V, Game.sprites[0]);

sprintf(frameCounter, "%d", Game.frame);

for(int i = 0; i < 9; i++)
{
    if(frameCounter[i] == '.') break;
    VACA_SelectSpriteFromSpritesheet(Game.spritesheets[0], frameCounter[i] - 48, 0);
    Game.spritesheets[0] -> rect.x = 96 + i * 8;

    VACA_DrawSpriteFromSpritesheet(Game.V, Game.spritesheets[0]);
}

VACA_RenderPresent(Game.V);
VACA_MaintainFrameRate(Game.V);

            break;
    }
}

void CleanUp()
{
    VACA_DestroySprite(Game.sprites[0]);
    VACA_DestroySpritesheet(Game.spritesheets[0]);
    VACA_Destroy(Game.V);
}

int main(void)
{
    Initialize();

    while(Game.running)
    {
        GameLoop();
    }

    CleanUp();

    return 0;
}