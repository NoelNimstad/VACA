#include "VACA/VACA.h"

typedef struct Ball
{
    Vector2_f     velocity;
    unsigned char image;
} Ball;

struct
{
    VACA         *V;
    Sprite       *sprites[4];

    int           frame;
    int           running;

    unsigned char state;

    Ball         *balls;
    Vector2_f     yellowBallVelocity;
} Game;

void init()
{
    Game.V = VACA_Initialize("Two Ball", 400, 500, 2, 120);

    Game.sprites[0] = VACA_CreateSprite(Game.V, "assets/twoball/board.png", 400, 500, 0, 0);
    Game.sprites[1] = VACA_CreateSprite(Game.V, "assets/twoball/yellow.png", 15, 15, 0, 0);
    Game.sprites[2] = VACA_CreateSprite(Game.V, "assets/twoball/yellow_hand.png", 18, 18, 0, 0);
    Game.sprites[3] = VACA_CreateSprite(Game.V, "assets/twoball/cursor.png", 15, 15, 0, 0);

    Game.state = 0;
}

int main(int argc, char const *argv[])
{
    init();

    VACA_SetRenderDrawColor(Game.V, 255, 0, 0);
    SDL_ShowCursor(SDL_DISABLE);

    unsigned char running = 1;
    while(running)
    {
        while(VACA_PollEvent(Game.V))
        {
            if(Game.V -> event.type == SDL_QUIT)
                running = 0;
        }

        VACA_UpdateMouse(Game.V);

        VACA_DrawSprite(Game.V, Game.sprites[0]);
        switch(Game.state)
        {
            case 0:
                Game.V -> mousePosition.x = SDL_clamp(Game.V -> mousePosition.x, 63, 347);
                Game.V -> mousePosition.y = SDL_clamp(Game.V -> mousePosition.y, 63, 447);

                VACA_MoveSprite(Game.sprites[2], Game.V -> mousePosition.x - 12, Game.V -> mousePosition.y - 12);
                VACA_DrawSprite(Game.V, Game.sprites[2]);

                if(Game.V -> mouseState == 1)
                {
                    Game.state = 1;
                    VACA_MoveSprite(Game.sprites[1], Game.V -> mousePosition.x - 12, 
                                                    Game.V -> mousePosition.y - 12)                   
                }
                break;
            case 1:
                VACA_DrawSprite(Game.V, Game.sprites[1]);

                VACA_DrawLine(Game.V, Game.sprites[1] -> rect.x + 7, 
                                    Game.sprites[1] -> rect.y + 7,
                                    Game.V -> mousePosition.x,
                                    Game.V -> mousePosition.y);

                VACA_MoveSprite(Game.sprites[3], Game.V -> mousePosition.x,
                                                Game.V -> mousePosition.y);
                VACA_DrawSprite(Game.V, Game.sprites[3]);

                if(Game.V -> mouseState == 1)
                {
                    float theta = VACA_AngleBetween(Game.V -> mousePosition.x, Game.V -> mousePosition.y, Game.sprites[1] -> rect.x + 7, Game.sprites[1] -> rect.y + 7);
                    printf("%f %f\n", cosf(theta), sinf(theta));
                    Game.state = 2;
                }
                break;
            case 2:
                VACA_DrawSprite(Game.V, Game.sprites[1]);
        }

        VACA_MaintainFrameRate(Game.V);
        VACA_RenderPresent(Game.V);
    }

    VACA_DestroySprite(Game.sprites[0]);
    VACA_DestroySprite(Game.sprites[1]);
    VACA_DestroySprite(Game.sprites[2]);
    VACA_DestroySprite(Game.sprites[3]);
    VACA_Destroy(Game.V);

    return 0;
}





























