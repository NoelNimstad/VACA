/**
 * @file VACA.h
 * @date 2024/09/21
 * 
 * Contains definitions for VACA functions, as well as the code for macro-based functions
 */

#ifndef VACA_h
#define VACA_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "VACA_types.h"

/**
 * @brief Initialize the VACA SDL Wrapper struct.
 * 
 * @param title Window title
 * @param width Window width
 * @param height Window height
 * @param scale Window scale
 * @param FPS Target frame rate
 * 
 * @return A pointer to a VACA struct, `VACA*` 
 */
VACA        *VACA_Initialize(const char *title, int width, int height, int scale, int FPS);
/**
 * @brief Destroys VACA SDL Wrapper struct as well as members of it that need destroying.
 * 
 * @param V Pointer to the program's VACA struct
 */
void         VACA_Destroy(VACA *V);

/**
 * @brief Clear the screen with inputted RGB color
 * 
 * @param V Pointer to the program's VACA struct
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 */
void         VACA_ClearScreen(VACA *V, unsigned char r, unsigned char g, unsigned char b);

/**
 * @brief Draws rectangle 
 * 
 * @param V Pointer to the program's VACA struct
 * @param rect Pointer to an `SDL_Struct` representing the rectangle
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 */
void         VACA_DrawRect(VACA *V, SDL_Rect *rect, unsigned char r, unsigned char g, unsigned char b);

/**
 * @brief Maintains the programs target frame rate. Call at the end of each frame.
 * 
 * @param V Pointer to the program's VACA struct
 */
void         VACA_MaintainFrameRate(VACA *V);

/**
 * @brief Macro for polling SDL Events
 * 
 * @param _V The program's VACA struct, of type `VACA*`
 */
#define      VACA_PollEvent(_V) SDL_PollEvent(&(_V) -> event)
/**
 * @brief Macro for putting drawn content to the screen
 * 
 * @param _V The program's VACA struct, of type `VACA*`
 */
#define      VACA_RenderPresent(_V) SDL_RenderPresent((_V) -> _SDL_Renderer)

/**
 * @brief Initializes a sprite which can be drawn using the `VACA_DrawSprite` method
 * 
 * @param V Pointer to the program's VACA struct
 * @param path Path to the spirte
 * @param width Sprite width
 * @param height Sprite height
 * @param x X location
 * @param y Y location
 * 
 * @return A pointer to the initialized sprite, of type `Sprite*` 
 */
Sprite      *VACA_CreateSprite(VACA *V, const char *path, int width, int height, int x, int y);
/**
 * @brief Draws sprite `_S` to the screen
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _S Pointer to the target sprite, of type `Sprite*`
 */
#define      VACA_DrawSprite(_V, _S) SDL_RenderCopy((_V) -> _SDL_Renderer, (_S) -> _SDL_Texture, NULL, &(_S) -> rect)
/**
 * @brief Changes the alpha of sprite `_S` to value `_A`
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _A Target alpha, of type `unsigned char`
 */
#define      VACA_SetSpriteOpacity(_S, _A) SDL_SetTextureAlphaMod((_S) -> _SDL_Texture, alpha)
/**
 * @brief Destroys sprite as well as members of it that need destroying.
 * 
 * @param S Pointer to the target sprite
 */
void         VACA_DestroySprite(Sprite *S);

/**
 * @brief Initializes a spritesheet of multiple sprites which can be drawn using the `VACA_DrawSpritesheet` method and can have sprite selected by calling the `VACA_SelectSpriteFromSpritesheet` method
 * 
 * @param V Pointer to the program's VACA struct
 * @param path Path to the spirtesheet
 * @param width Spritesheet width
 * @param height Spritesheet height
 * @param tileWidth Width of each tile
 * @param tileHeight Height of each tile
 * @param x X location
 * @param y Y location
 * 
 * @return A pointer to the initialized spritesheet, of type `Spritesheet*` 
 */
Spritesheet *VACA_CreateSpritesheet(VACA *V, const char *path, int width, int height, int tileWidth, int tileHeight, int x, int y);
/**
 * @brief Marcro to mark the sprite at coordinates (`X`, `Y`) from the spritesheet `SS` as the active one; e.g the one which will be drawn upon calling `VACA_DrawSpriteFromSpritesheet`
 * 
 * @param _SS Pointer to the target spritesheet, type `Spritesheet*`
 * @param _x X coordinate of the target sprite, type `int`
 * @param _y Y coordinate of the target sprite, type `int`
 */
#define      VACA_SelectSpriteFromSpritesheet(_SS, _x, _y) (_SS) -> _sourceRect.x = (_SS) -> _sourceRect.w * (_x); \
                                                           (_SS) -> _sourceRect.y = (_SS) -> _sourceRect.h * (_y);
/**
 * @brief Draws sprite `_S` to the screen
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _SS Pointer to the target spritesheet, of type `SS*`
 */
#define      VACA_DrawSpriteFromSpritesheet(_V, _SS) SDL_RenderCopy((_V) -> _SDL_Renderer, (_SS) -> _SDL_Texture, &(_SS) -> _sourceRect, &(_SS) -> rect)

/**
 * @brief Destroys spritesheet as well as members of it that need destroying.
 * 
 * @param SS Pointer to the target spritesheet
 */
void         VACA_DestroySpritesheet(Spritesheet *SS);

#endif // VACA_h