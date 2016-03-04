/* libhnef/tile.h
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/tile.h
 *
 * @brief Macros, typedefs and function forward declarations for the
 * HnefTile struct
 *
 * @author Gary Munnelly
 */

#ifndef LIBHNEF_TILE_H_
#define LIBHNEF_TILE_H_

#include "token.h"

#define HNEF_EMPTY     0x00 /**< Code for tile with no structure built on it*/
#define HNEF_CASTLE    0x01 /**< Code for tile with a castle built on it */
#define HNEF_THRONE    0x02 /**< Code for tile with a throne built on it */
#define HNEF_CAMP      0x03 /**< Code for tile with a camp site built on it */

#define HNEF_NO_ESCAPE 0x00 /**< King cannot escape via this tile */
#define HNEF_ESCAPE    0x01 /**< King can escape via this tile */

#ifdef _cplusplus
extern "C" {
#endif

/**
 * @brief typedef allowing us to call _hneftile as HnefTile
 */
typedef struct _hneftile   HnefTile;

/* Tile initializers, getters, setters and destructors etc. */
HnefTile*    hnef_tile_new                 ( int type, int is_escape, HnefToken *token );
uint8_t      hnef_tile_serialize           ( HnefTile *tile );
HnefTile*    hnef_tile_deserialize         ( uint8_t serialized );

int          hnef_tile_get_type            ( HnefTile *tile );
void         hnef_tile_set_type            ( HnefTile *tile, int type );
int          hnef_tile_get_is_escape       ( HnefTile *tile );
void         hnef_tile_set_is_escape       ( HnefTile *tile, int is_escape );
HnefToken*   hnef_tile_get_token           ( HnefTile *tile );
void         hnef_tile_set_token           ( HnefTile *tile, HnefToken *token );
HnefToken*   hnef_tile_replace_token       ( HnefTile *tile, HnefToken *token );
int          hnef_tile_is_occupied         ( HnefTile *tile );

void         hnef_tile_free                ( HnefTile *tile );

#ifdef _cplusplus
}
#endif

#endif /* LIBHEFT_TILE_H_ */
