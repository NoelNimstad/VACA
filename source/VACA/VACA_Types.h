#ifndef VACA_Rect_h
#define VACA_Rect_h

typedef struct VACA_Scene
{

} VACA_Scene;

typedef struct VACA
{
    SDL_Event     event;

    VACA_Scene   *_scenes;

    int           _width;
    int           _height;
    int           _scale;

    float         _frameDelay;
    Uint64        _lastFrameTime;

    SDL_Window   *_SDL_Window;
    SDL_Renderer *_SDL_Renderer;
} VACA;

#define VACA_ConvertVector2_i2f(_v2i)((Vector2_f){ _v2i.x, _v2i.y })
#define VACA_ConvertVector2_f2i(_v2f)((Vector2_i){ _v2f.x, _v2f.y })

typedef struct Vector2_i
{
    int           x, y;
} Vector2_i;

typedef struct Vector2_f
{
    float         x, y;
} Vector2_f;

typedef struct Sprite
{
    SDL_Rect      rect;
    
    SDL_Texture  *_SDL_Texture;
} Sprite;

#endif // VACA_Rect_h