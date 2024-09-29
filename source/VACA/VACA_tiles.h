#ifndef VACA_tiles_h
#define VACA_tiles_h

#include <stdlib.h>
#include "VACA_types.h"

Tilemap *VACA_CreateTilemap(VACA *V, const char *txtPath, const char *imgPath);

void     VACA_DestroyTilemap(Tilemap *t);

#endif