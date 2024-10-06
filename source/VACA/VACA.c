/**
 * @file VACA.C
 * @date 2024/09/21
 * 
 * @brief Contains code for VACA functions defined in VACA.h
 * @note See comments for the purpose of each function in VACA.h
 */

#include "VACA.h"

VACA *VACA_Initialize(const char *title, int width, int height, int scale, int FPS)
{
    // Attempt to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL:\n%s\n", SDL_GetError());
        return NULL;
    }
    
    // Attempt to initialize SDL_image
    if(IMG_Init(IMG_INIT_PNG) == 0)
    {
        fprintf(stderr, "Failed to initialize SDL_image:\n%s\n", IMG_GetError());
        SDL_Quit();
        return NULL;
    }

    // Allocate memory for an instance of VACA
    VACA *V = (VACA*)malloc(sizeof(VACA));

    V -> _width = width;   // Asign variables
    V -> _height = height; // 
    V -> _scale = scale;   //

    // Calculate the frame delay (1000 ms / frames per second)
    V -> _frameDelay = 1000 / FPS;

    // Attempt to create a SDL_Window
    V -> _SDL_Window = SDL_CreateWindow(title,
                                        SDL_WINDOWPOS_CENTERED, // Center window
                                        SDL_WINDOWPOS_CENTERED, //
                                        V -> _width,
                                        V -> _height,
                                        0);                     // No special initialization 

    // Make sure the window was created correctly
    if(V -> _SDL_Window == NULL)
    {
        fprintf(stderr, "Failed to create a SDL Window:\n%s\n", SDL_GetError());
        SDL_Quit();

        free(V);

        return NULL;
    }
    
    // Attempt to create a SDL_Renderer
    V -> _SDL_Renderer = SDL_CreateRenderer(V -> _SDL_Window, 
                                            0, 
                                            SDL_RENDERER_ACCELERATED);

    // Make sure the renderer was created correctly
    if(V -> _SDL_Renderer == NULL) 
    {
        fprintf(stderr, "Failed to create a SDL Renderer:\n%s\n", SDL_GetError());
        SDL_DestroyWindow(V -> _SDL_Window);
        SDL_Quit();

        free(V);
        
        return NULL;
    }

    V -> _lastCounter = SDL_GetPerformanceCounter();          // Get current time
    V -> _performanceFrequency = SDL_GetPerformanceFrequency(); // Get (the constant) performance frequency

    return V;
}

void VACA_Destroy(VACA *V)
{
    if(V == NULL) return;

    SDL_DestroyWindow(V -> _SDL_Window);
    SDL_DestroyRenderer(V -> _SDL_Renderer);
    SDL_Quit();
    IMG_Quit();

    free(V);
}

void VACA_ClearScreen(VACA *V, unsigned char r, unsigned char g, unsigned char b)
{
    VACA_SetRenderDrawColor(V, r, g, b);
    SDL_RenderClear(V -> _SDL_Renderer);
}

void VACA_DrawRect(VACA *V, SDL_Rect *rect, unsigned char r, unsigned char g, unsigned char b)
{
    VACA_SetRenderDrawColor(V, r, g, b);
    SDL_RenderFillRect(V -> _SDL_Renderer, rect);
}


void VACA_StartFrame(VACA *V)
{
    V -> _currentCounter = SDL_GetPerformanceCounter(); // Get current time
    V -> deltaTime = (double)((V -> _currentCounter - V -> _lastCounter) / V -> _performanceFrequency); // Calculate elapsed time
    V -> _lastCounter = V -> _currentCounter;
}
void VACA_EndFrame(VACA *V)
{
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    double frameTime = (double)(currentCounter - V -> _lastCounter) / V -> _performanceFrequency;

    if(frameTime < V -> _frameDelay)
    {
        SDL_Delay((Uint32)((V -> _frameDelay - frameTime))); // Delay by the difference between the delta time and elapsed time
    }
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

void VACA_DestroySprite(Sprite *S)
{
    if(S == NULL) return;

    SDL_DestroyTexture(S -> _SDL_Texture);
    free(S);
}

Spritesheet *VACA_CreateSpritesheet(VACA *V, const char *path, int width, int height, int tileWidth, int tileHeight, int x, int y)
{
    Spritesheet *spritesheet = (Spritesheet*)malloc(sizeof(Spritesheet));
    spritesheet -> _SDL_Texture = IMG_LoadTexture(V -> _SDL_Renderer, path);

    if(spritesheet -> _SDL_Texture == NULL)
    {
        fprintf(stderr, "Failed to load texture:\n%s\n", IMG_GetError());
        return NULL;
    }

    spritesheet -> rect.w = tileWidth;
    spritesheet -> rect.h = tileHeight;
    spritesheet -> rect.x = x;
    spritesheet -> rect.y = y;

    spritesheet -> _sourceRect.w = tileWidth;
    spritesheet -> _sourceRect.h = tileHeight;
    spritesheet -> _sourceRect.x = 0;
    spritesheet -> _sourceRect.y = 0;

    return spritesheet;
}

void VACA_DestroySpritesheet(Spritesheet *SS)
{
    if(SS == NULL) return;

    SDL_DestroyTexture(SS -> _SDL_Texture);
    free(SS);
}

Tilemap *VACA_CreateTilemap(const char *tileInformation, Spritesheet *spritesheet)
{
    if(tileInformation == NULL || spritesheet == NULL) 
    {
        printf("Invalid input to create tilemap\n");
        return NULL;
    }

    Tilemap *t = (Tilemap*)malloc(sizeof(Tilemap));
    if(t == NULL)
    {
        printf("Failed to allocate memory for tilemap");
    }

    t -> _spritesheet = spritesheet;
    t -> _numberOfTileCollections = 0;

    int length; char **rows = SplitString(tileInformation, '\n', &length);
    if(length < 1 || rows == NULL)
    {
        printf("Empty tilemap or invalid data\n");
        free(t);
        return NULL;
    }

    t -> _tileCollections = (_TileCollection*)malloc(sizeof(_TileCollection) * length);
    if(t -> _tileCollections == NULL)
    {
        printf("Failed to allocate memory for tile collections");
        DestroyStringList(rows);
        free(t);
        return NULL;
    }

    for (int i = 0; i < length; i++) 
    {
        int parts;
        char **information = SplitString(rows[i], ' ', &parts);
        if (parts != 2 || information == NULL) 
        {
            printf("Insufficient information for tilemap at row %d\n", i);
            DestroyStringList(information);
            continue;
        }

        _TileCollection tc = { 0 };
        tc.type = SDL_atoi(information[0]);

        int amountOfPositions;
        char **positions = SplitString(information[1], '|', &amountOfPositions);
        if (amountOfPositions % 2 != 0 || positions == NULL) 
        {
            printf("Invalid positions data for tile collection at row %d\n", i);
            DestroyStringList(information);
            DestroyStringList(positions);
            continue;
        }

        int positionCount = amountOfPositions / 2;
        tc.positions = (Vector2_i*)malloc(sizeof(Vector2_i) * positionCount);
        if (!tc.positions) 
        {
            printf("Failed to allocate memory for positions at row %d\n", i);
            DestroyStringList(information);
            DestroyStringList(positions);
            continue;
        }

        for (int h = 0; h < amountOfPositions; h += 2) 
        {
            tc.positions[h / 2].x = SDL_atoi(positions[h]);
            tc.positions[h / 2].y = SDL_atoi(positions[h + 1]);
        }

        t -> _tileCollections[i] = tc;
        t -> _numberOfTileCollections++;

        DestroyStringList(information);
        DestroyStringList(positions);
    }

    DestroyStringList(rows);

    return t;
}

void VACA_DestroyTilemap(Tilemap *t)
{
    if(t == NULL) return;

    for(int i = 0; i < t -> _numberOfTileCollections; i++)
    {
        free(t -> _tileCollections[i].positions);
    }
    free(t -> _tileCollections);

    VACA_DestroySpritesheet(t -> _spritesheet);
    free(t);
}