#include <stdio.h>

#include "VACA/VACA.h"

#define WIDTH 400
#define HEIGHT 300

enum Scene
{
    VACA_Splash,
    DoNothing
};

int main(void)
{
    VACA *V = VACA_Initialize("BOMBERMAN", 400, 300, 1, 60);
    Sprite *S = VACA_CreateSprite(V, "../assets/logo.png", 300, 200, 50, 50);

    int running = 1;
    int frame = 0;
    enum Scene scene = VACA_Splash;
    while(running)
    {
        while(VACA_PollEvent(V))
        {
            if(V -> event.type == SDL_QUIT) { running = 0; };
        }

        VACA_ClearScreen(V, 0, 0, 0);

        printf("%d\n", frame++);

        switch(scene)
        {
            case VACA_Splash:
                VACA_SetSpriteOpacity(S, 255 * ((float)frame / 120.0f));
                VACA_DrawSprite(V, S);
                if(frame > 120)
                {
                    scene = DoNothing;
                    VACA_DestroySprite(S);
                }
                break;
            case DoNothing:
                break;
        }

        VACA_RenderPresent(V);
        VACA_MaintainFrameRate(V);
    }

    VACA_DestroySprite(S);
    VACA_Destroy(V);

    return 0;
}