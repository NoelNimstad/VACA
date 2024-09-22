#ifndef VACA_h
#define VACA_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "VACA_Types.h"

VACA        *VACA_Initialize(const char *title, int width, int height, int scale, int FPS);
void         VACA_Destroy(VACA *V);

void         VACA_ClearScreen(VACA *V, unsigned char r, unsigned char g, unsigned char b);
void         VACA_DrawRect_i(VACA *V, SDL_Rect *rect, unsigned char r, unsigned char g, unsigned char b);

void         VACA_MaintainFrameRate(VACA *V);

#define      VACA_PollEvent(_V) SDL_PollEvent(&_V -> event)
#define      VACA_RenderPresent(_V) SDL_RenderPresent(_V -> _SDL_Renderer)

Sprite      *VACA_CreateSprite(VACA *V, const char *path, int width, int height, int x, int y);
void         VACA_DrawSprite(VACA *V, Sprite *S);
void         VACA_SetSpriteOpacity(Sprite *S, unsigned char alpha);
void         VACA_DestroySprite(Sprite *S);

Spritesheet *VACA_CreateSpritesheet(VACA *V, const char *path, int width, int height, int tileWidth, int tileHeight, int x, int y);
void         VACA_SelectSpriteFromSpritesheet(Spritesheet *SS, int x, int y);
void         VACA_DrawSpriteFromSpritesheet(VACA *V, Spritesheet *SS);
void         VACA_DestroySpritesheet(Spritesheet *SS);

#endif // VACA_h