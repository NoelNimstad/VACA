#include "VACA/VACA.h"

#define SPEED 200
#define WIDTH 200
#define HEIGHT 200

#define SWAP_STATE() state = !state;                                           \
                     timer = randomBetween(1, 5);                              \
                     VACA_ClearScreen(V, state ? 0 : 255, state ? 255 : 0, 0); \
                     VACA_RenderPresent(V);

int main(int argc, char const *argv[])
{
    seedRandom();
    u8 state = 1;
    u8 notwin = 1;
    u16 clock = randomBetween(500, 100);
    char title[10] = "0";
    float score = 0;
    float timer;
    float totalTime = 0;

    VACA *V = VACA_Initialize("0", WIDTH, HEIGHT, 1, 120);

    Vector2_f position = { 0, 0 };
    Vector2_f velocity = { SPEED, SPEED };

    VACA_MoveWindow(V, position.x, position.y);
    SWAP_STATE();

    int8_t running = 1;
    while(running)
    {
        VACA_StartFrame(V);

        while(VACA_PollEvent(V))
        {
            if(V -> event.type == SDL_QUIT)
            {
                running = 0;
            }
            if(V -> event.type == SDL_MOUSEMOTION)
            {
                score += V -> deltaTime * SPEED * (state ? 1 : -1);

                if(score > 5000)
                {
                    char winString[40];
                    sprintf(winString, "you win! score: %f", totalTime);
                    notwin = 0;

                    VACA_RetitleWindow(V, winString);
                    VACA_ResizeWindow(V, WIDTH * 2, 1);
                    VACA_ClearScreen(V, 0, 0, 0);
                    VACA_RenderPresent(V);
                }
            }
        }

        if(notwin)
        {
            totalTime += V -> deltaTime;

            if((timer -= V -> deltaTime) < 0)
            {
                SWAP_STATE();
            }

            position.x += velocity.x * V -> deltaTime;
            position.y += velocity.y * V -> deltaTime;

            if(position.x < 0 || position.x > V -> screenWidth - WIDTH)
            {
                velocity.x *= -1;
                position.x += velocity.x * V -> deltaTime;
            }
            if(position.y < 0 || position.y > V -> screenHeight - HEIGHT)
            {
                velocity.y *= -1;
                position.y += velocity.y * V -> deltaTime;
            }

            sprintf(title, "%d", (int)score);
            VACA_MoveWindow(V, floor(position.x), floor(position.y));
            VACA_RetitleWindow(V, title);
        }

        VACA_EndFrame(V);
    }

    return 0;
}