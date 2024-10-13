/**
 * @file VACA.h
 * @date 2024/09/21
 * 
 * @brief Contains definitions for VACA functions, as well as the code for macro-based functions
 */

#ifndef VACA_h
#define VACA_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "VACA_types.h"
#include "VACA_constants.h"

/**
 * @brief Initialize the VACA SDL Wrapper struct.
 * 
 * @param title Window title
 * @param width Window width
 * @param height Window height
 * @param scale Window scale, 0 for fullscreen
 * @param FPS Target frame rate
 * 
 * @return A pointer to a VACA struct, `VACA*` 
 */
VACA        *VACA_Initialize(const char *title, u16 width, u16 height, u8 scale, u16 FPS);
/**
 * @brief Destroys VACA SDL Wrapper struct as well as members of it that need destroying.
 * 
 * @param V Pointer to the program's VACA struct
 */
void         VACA_Destroy(VACA *V);

/**
 * @brief Sets the renderer's to inputted RGB color. To be used only within the VACA.c file.
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _r Red color value, of type `unsigned char`
 * @param _g Green color value, of type `unsigned char`
 * @param _b Blue color value, of type `unsigned char`
 */
#define      VACA_SetRenderDrawColor(_V, _r, _g, _b) SDL_SetRenderDrawColor(_V -> _SDL_Renderer, _r, _g, _b, 255)
/**
 * @brief Macro to draw a line between points (`_x1`, `_y1`) and (`_x2`, `_y2`)
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _x1 point x1, of type `int`
 * @param _y1 point y1, of type `int`
 * @param _x2 point x2, of type `int`
 * @param _y2 point y2, of type `int`
 */
#define      VACA_DrawLine(_V, _x1, _y1, _x2, _y2) SDL_RenderDrawLine((_V) -> _SDL_Renderer, (_x1), (_y1), (_x2), (_y2))

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
 * @brief Clear the screen with the render draw color
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 */
#define      VACA_ClearScreen2(_V) SDL_RenderClear((_V) -> _SDL_Renderer);

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
void         VACA_StartFrame(VACA *V);
/**
 * @brief Maintains the programs target frame rate. Call at the end of each frame.
 * 
 * @param V Pointer to the program's VACA struct
 */
void         VACA_EndFrame(VACA *V);

/**
 * @brief Macro for polling SDL Events as well as updating mouse infromation
 * 
 * @param _V The program's VACA struct, of type `VACA*`
 */
#define      VACA_PollEvent(_V) SDL_PollEvent(&(_V) -> event)

/**
 * @brief Macro for updating mouse infromation
 * 
 * @param _V The program's VACA struct, of type `VACA*`
 */
#define      VACA_UpdateMouse(_V) (_V) -> mouseState = SDL_GetMouseState(&(_V) -> mousePosition.x, &(_V) -> mousePosition.y)

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
 * @brief Move sprite `_S` to position _X, _Y
 * 
 * @param _S Pointer to the target sprite, of type `Sprite*`
 * @param _X X position, of type `int`
 * @param _Y Y position, of tpye `int`
 */
#define      VACA_MoveSprite(_S, _X, _Y) (_S) -> rect.x = (_X); \
                                         (_S) -> rect.y = (_Y);

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
Spritesheet *VACA_CreateSpritesheet(VACA *V, const char *path, int tileWidth, int tileHeight, int x, int y);
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

/**
 * @brief Macro to calculate the angle between (`_x1`, `_y1`) and (`_x2`, `_y2`)
 * 
 * @param _x1 point x1, of type `int`
 * @param _y1 point y1, of type `int`
 * @param _x2 point x2, of type `int`
 * @param _y2 point y2, of type `int`
 * 
 * @return A `float` of the angle between the points, in radians
 */
#define      VACA_AngleBetween(_x1, _y1, _x2, _y2) (atan2f((_y2) - (_y1), (_x2) - (_x1)))
/**
 * @brief Macro to calculate the distance between (`_x1`, `_y1`) and (`_x2`, `_y2`)
 * 
 * @param _x1 point x1, of type `int`
 * @param _y1 point y1, of type `int`
 * @param _x2 point x2, of type `int`
 * @param _y2 point y2, of type `int`
 * 
 * @return A `float` of the distance between the points
 */
#define      VACA_DistanceBetween(_x1, _y1, _x2, _y2) (sqrtf(((_x2) - (_x1)) * ((_x2) - (_x1)) + ((_y2) - (_y1)) * ((_y2) - (_y1))))

/**
 * @brief Initializes a tilemap which can be drawn using the `VACA_DrawTilemap` method
 * 
 * @param tileInformation Information in VACA tilemap format
 * @param spritesheet Pointer to the spritesheet to use
 * 
 * @return A pointer to the initialized tilemap, of type `Tilemap*` 
 */
Tilemap     *VACA_CreateTilemap(const char *tileInformation, Spritesheet *spritesheet);
/**
 * @brief Renders a tilemap
 * 
 * @param V Pointer to the program's VACA struct
 * @param T Pointer to the tilemap
 */
void         VACA_DrawTilemap(VACA *V, Tilemap *T);
/**
 * @brief Macro to offset a tilemap to coordinate `_x` and `_y`
 * 
 * @param _V Pointer to the program's VACA struct, of type `VACA*`
 * @param _x x coordinate, of type `int`
 * @param _y y coordinate, of type `int`
 */
#define      VACA_OffsetTilemap(_T, _x, _y) (_T)->offset.x = (_x); \
                                            (_T)->offset.y = (_y);
/**
 * @brief De-initializes tilemap
 * 
 * @param t Pointer to the target tilemap
 */
void         VACA_DestroyTilemap(Tilemap *t);

#define      VACA_ResizeWindow(_V, _w, _h) SDL_SetWindowSize((_V) -> _SDL_Window, (_w), (_h))
#define      VACA_MoveWindow(_V, _x, _y) SDL_SetWindowPosition((_V) -> _SDL_Window, (_x), (_y))
#define      VACA_RetitleWindow(_V, _s) SDL_SetWindowTitle((_V) -> _SDL_Window, (_s))

#endif // VACA_h