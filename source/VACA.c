#include "VACA.h"

VACA *VACA_Initialize(const char *title, int width, int height, int scale, int FPS)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL:\n%s\n", SDL_GetError());
        return NULL;
    }
    
    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        fprintf(stderr, "Failed to initialize SDL_image:\n%s\n", IMG_GetError());
        SDL_Quit();
        return NULL;
    }

    VACA * V = (VACA*)malloc(sizeof(VACA));
    V -> _width = width;
    V -> _height = height;
    V -> _scale = scale;

    V -> _frameDelay = 1000 / FPS;

    V -> _SDL_Window = SDL_CreateWindow(title,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        V -> _width,
                                        V -> _height,
                                        0);

    if(V -> _SDL_Window == NULL)
    {
        fprintf(stderr, "Failed to create a SDL Window:\n%s\n", SDL_GetError());
        SDL_Quit();

        free(V);

        return NULL;
    }
    
    V -> _SDL_Renderer = SDL_CreateRenderer(V -> _SDL_Window, 
                                            0, 
                                            SDL_RENDERER_ACCELERATED);

    if(V -> _SDL_Renderer == NULL) 
    {
        fprintf(stderr, "Failed to create a SDL Renderer:\n%s\n", SDL_GetError());
        SDL_DestroyWindow(V -> _SDL_Window);
        SDL_Quit();

        free(V);
        
        return NULL;
    }

    V -> _lastFrameTime = SDL_GetPerformanceCounter();

    return V;
}

void VACA_Destroy(VACA *V)
{
    SDL_DestroyWindow(V -> _SDL_Window);
    SDL_DestroyRenderer(V -> _SDL_Renderer);
    SDL_Quit();
    IMG_Quit();

    free(V);
}

#define _VACA_SetRenderDrawColor(_V, _r, _g, _b) SDL_SetRenderDrawColor(_V -> _SDL_Renderer, _r, _g, _b, 255)

void VACA_ClearScreen(VACA *V, unsigned char r, unsigned char g, unsigned char b)
{
    _VACA_SetRenderDrawColor(V, r, g, b);
    SDL_RenderClear(V -> _SDL_Renderer);
}

void VACA_DrawRect_i(VACA *V, SDL_Rect *rect, unsigned char r, unsigned char g, unsigned char b)
{
    _VACA_SetRenderDrawColor(V, r, g, b);
    SDL_RenderFillRect(V -> _SDL_Renderer, rect);
}

void VACA_MaintainFrameRate(VACA *V)
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    double elapsed = (double)((currentTime - V -> _lastFrameTime) * 1000.0 / (double)frequency);

    if(elapsed < V -> _frameDelay)
    {
        SDL_Delay((Uint32)(V -> _frameDelay - elapsed));
    }

    V -> _lastFrameTime = SDL_GetPerformanceCounter();
}

Sprite *VACA_CreateSprite(VACA *V, const char *path, int width, int height, int x, int y)
{
    Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));
    sprite -> _SDL_Texture = IMG_LoadTexture(V -> _SDL_Renderer, path);

    if(sprite -> _SDL_Texture == NULL)
    {
        fprintf(stderr, "Failed to load texture:\n%s\n", IMG_GetError());
        return NULL;
    }

    sprite -> rect.w = width;
    sprite -> rect.h = height;
    sprite -> rect.x = x;
    sprite -> rect.y = y;

    return sprite;
}

void VACA_DrawSprite(VACA *V, Sprite *S)
{
    SDL_RenderCopy(V -> _SDL_Renderer, S -> _SDL_Texture, NULL, &S -> rect);
}

void VACA_SetSpriteOpacity(Sprite *S, unsigned char alpha)
{
    SDL_SetTextureAlphaMod(S -> _SDL_Texture, alpha);
}

void VACA_DestroySprite(Sprite *S)
{
    SDL_DestroyTexture(S -> _SDL_Texture);
    free(S);
}