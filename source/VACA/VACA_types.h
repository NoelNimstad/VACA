/**
 * @file VACA_Types.h
 * @date 2024/09/22
 *
 * @brief This file defines the types and type conversion functions used in regards to the VACA SDL wrapper
 */

#ifndef VACA_types_h
#define VACA_types_h

#include <SDL2/SDL.h>
#include "VACA_utils.h"

/**
 * @brief Convert an integer 2d vector into a floating point 2d vector
 * @param _v2f Input integer 2d vector
 * 
 * @return Output floating point 2d vector
 */
#define VACA_ConvertVector2_i2f(_v2i)((Vector2_f){ (_v2i).x, (_v2i).y })
/**
 * @brief Convert a floating point 2d vector into an integer 2d vector
 * @param _v2f Input floating point 2d vector
 * 
 * @return Output integer 2d vector
 */
#define VACA_ConvertVector2_f2i(_v2f)((Vector2_i){ (_v2f).x, (_v2f).y })
/**
 * @brief Check if an integer 2d vector is has magnitude 0
 * @param _v2f Input integer 2d vector
 * 
 * @return Output integer boolean 
 */
#define VACA_Vector2_i_isZero(_v2i)(((_v2i).x = 0) && ((_v2i).y = 0))
/**
 * @brief Check if a floating point 2d vector is has magnitude 0
 * @param _v2f Input floating point 2d vector
 * 
 * @return Output integer boolean 
 */
#define VACA_Vector2_f_isZero(_v2f)(((_v2f).x == 0) && ((_v2f).y == 0))
/**
 * @brief Initializes a Vector2_i
 * 
 * @param _X X position, type `int`
 * @param _Y Y position, type `int`
 */
#define Create_Vector2_i(_X, _Y) ((Vector2_i){ (_X), (_Y) })
/**
 * @brief An integer 2 dimensional vector 
 */
typedef struct
{
    int              x, y;
} Vector2_i;
/**
 * @brief Initializes a Vector2_f
 * 
 * @param _X X position, type `float`
 * @param _Y Y position, type `float`
 */
#define Create_Vector2_f(_X, _Y) ((Vector2_f){ (_X), (_Y) })
/**
 * @brief A floating point 2 dimensional vector 
 */
typedef struct
{
    float            x, y;
} Vector2_f;

/**
 * @brief The VACA struct encapsulates all variables needed for the operation of the VACA SDL wrapper
 */
typedef struct
{
    SDL_Event        event;
    double           deltaTime;

    u8               mouseState;
    Vector2_i        mousePosition;

    u16              screenWidth;
    u16              screenHeight;

    u16              _width;
    u16              _height;
    u8               _scale;
    u8               _fullscreen;

    float            _frameDelay;
    u64              _currentCounter;
    u64              _lastCounter;
    double           _performanceFrequency;

    SDL_Window      *_SDL_Window;
    SDL_Renderer    *_SDL_Renderer;
    SDL_DisplayMode  _SDL_DisplayMode;
} VACA;

/**
 * @brief A single sprite 
 */
typedef struct
{
    SDL_Rect         rect;
    
    SDL_Texture     *_SDL_Texture;
} Sprite;
/**
 * @brief Multiple sprites
 */
typedef struct
{
    SDL_Rect         rect;

    SDL_Rect         _sourceRect; 
    SDL_Texture     *_SDL_Texture;
} Spritesheet;

/**
 * @brief Internal struct for encapsulating an array of tiles of tile type `type` in a `Tilemap`
 */
typedef struct
{
    Vector2_i        type;
    Vector2_i       *positions;
    int              numberOfPositions;
} _TileCollection;
/**
 *  @brief A tilemap
 */
typedef struct
{
    Vector2_i        offset;
    
    Spritesheet     *_spritesheet;
    _TileCollection *_tileCollections;
    u16              _numberOfTileCollections;
} Tilemap;

#endif // VACA_types_h
