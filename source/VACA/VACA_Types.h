/**
 * @file VACA_Types.h
 *
 * This file defines the types used in regards to the VACA SDL wrapper
 */

#ifndef VACA_Rect_h
#define VACA_Rect_h

/**
 * @brief The VACA struct encapsulates all variables needed for the operation of the VACA SDL wrapper
 */
typedef struct VACA
{
    SDL_Event     event;

    int           _width;
    int           _height;
    int           _scale;

    float         _frameDelay;
    Uint64        _lastFrameTime;

    SDL_Window   *_SDL_Window;
    SDL_Renderer *_SDL_Renderer;
} VACA;

/**
 * @brief Convert an integer 2d vector into a floating point 2d vector
 * @param[in] _v2f Input integer 2d vector
 * 
 * @return Output floating point 2d vector
 */
#define VACA_ConvertVector2_i2f(_v2i)((Vector2_f){ _v2i.x, _v2i.y })

/**
 * @brief Convert a floating point 2d vector into an integer 2d vector
 * @param[in] _v2f Input floating point 2d vector
 * 
 * @return Output integer 2d vector
 */
#define VACA_ConvertVector2_f2i(_v2f)((Vector2_i){ _v2f.x, _v2f.y })

/**
 * @brief An integer 2 dimensional vector 
 */
typedef struct Vector2_i
{
    int           x, y;
} Vector2_i;

/**
 * @brief A floating point 2 dimensional vector 
 */
typedef struct Vector2_f
{
    float         x, y;
} Vector2_f;

/**
 * @brief A single sprite 
 */
typedef struct Sprite
{
    SDL_Rect      rect;
    
    SDL_Texture  *_SDL_Texture;
} Sprite;

/**
 * @brief Multiple sprites
 */
typedef struct Spritesheet
{
    SDL_Rect      rect;

    SDL_Rect      _sourceRect; 
    SDL_Texture  *_SDL_Texture;
} Spritesheet;

#endif // VACA_Rect_h