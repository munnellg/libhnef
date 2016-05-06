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
 * @brief Represents a single square on the game board.
 *
 * A tile may be occupied by a token. The occupying token is
 * identified by a pointer to an appropriate instance of the HnefToken
 * struct.
 *
 * A tile may also have a structure built on it. This structure is
 * represented by a suitable code and affects some of the rules that
 * determine how a token may interact with the tile
 *
 * Finally, some tiles act as escape routes for the king. It is the
 * goal of the game for one team to aid in their King's escape. This
 * attribute determines whether or not placing the king on this square
 * will result in victory for that particular team
 */
typedef struct HnefTile {
	HnefToken token;     /**< HnefToken standing on this tile */
	int is_occupied;     /**< Boolean denoting whether or not this tile is occupied */
	int type;            /**< Type of structure built on this tile */
	int is_escape;       /**< Boolean denoting whether the king can
							* escape via this tile or not */
} HnefTile;

/* Tile initializers, getters, setters and destructors etc. */
void	     hnef_tile_init                ( HnefTile *tile, int type, int is_escape);
uint8_t      hnef_tile_serialize           ( HnefTile *tile );
int          hnef_tile_deserialize         ( HnefTile *tile, uint8_t serialized );

int          hnef_tile_get_type            ( HnefTile *tile );
void         hnef_tile_set_type            ( HnefTile *tile, int type );
int          hnef_tile_get_is_occupied     ( HnefTile *tile );
void         hnef_tile_set_is_occupied     ( HnefTile *tile, int is_occupied );
int          hnef_tile_get_is_escape       ( HnefTile *tile );
void         hnef_tile_set_is_escape       ( HnefTile *tile, int is_escape );
HnefToken    hnef_tile_get_token           ( HnefTile *tile );
void         hnef_tile_set_token           ( HnefTile *tile, HnefToken token );
void         hnef_tile_unset_token         ( HnefTile *tile );

#ifdef _cplusplus
}
#endif

#endif /* LIBHEFT_TILE_H_ */
