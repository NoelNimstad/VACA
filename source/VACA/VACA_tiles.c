#include "VACA_tiles.h"

Tilemap *VACA_CreateTilemap(VACA *V, const char *txtPath, const char *imgPath)
{
    Tilemap *t = (Tilemap*)malloc(sizeof(Tilemap));

    return t;
}

void     VACA_DestroyTilemap(Tilemap *t)
{
    free(t);
}