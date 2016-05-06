/* libhnef/tile.c
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/tile.c
 *
 * @brief Code for manipulating an individual tile on the game board
 *
 * @author Gary Munnelly
 */

#include "tile.h"


/**
 * @brief Initializes passed tile struct with parameters given
 *
 * @param type The type of structure built on this tile
 *
 * @param is_escape A boolean denoting whether or not the king can
 * escape via this tile
 *
 * @return A pointer to the newly allocated tile or NULL on failed
 * allocation
 */
void
hnef_tile_init( HnefTile *tile, int type, int is_escape ) {
	if(tile) {
			tile->type = type;
			tile->is_escape = is_escape;
			tile->is_occupied = 0;
	}
}

/**
 * @brief Serialize the HnefTile passed as an argument into an 8 bit
 * representation which may be used to export the tile to a
 * file. Deserialized representation also hold the representation for
 * the HnefToken standing on the tile.
 *
 * The least significant 3 bits represent the token on the tile.
 *
 * The fourth and fifth bits represent the type of structure built on
 * the tile.
 *
 * The sixth bit represents whether or not this is an escape tile.
 *
 * @param tile The tile to be serialized
 *
 * @return The serialized representation of the tile
 */
uint8_t
hnef_tile_serialize( HnefTile *tile ) {
	uint8_t c;
	int is_escape, type;

	c = 0;

	/* Check to see if the tile passed is valid */
	if(tile) {
		/* Get appropriate tile properties */
		is_escape = hnef_tile_get_is_escape(tile);
		type = hnef_tile_get_type(tile);

		/* Serialize tile */
		c = ((1 << 1) | is_escape) << 2;
		c = (c | type) << 3;
		/* Call to serialize the token and append the result to */
		/* the encoding                                         */
		if(tile->is_occupied) {
			c |= hnef_token_serialize(&(tile->token));	
		}		
	} 

	/* Return the encoded tile */
	return c;
}

/**
 * @brief Deserialize an encoded tile into a HnefTile instance.
 *
 * @param serialized The encoded tile
 *
 * @return A pointer to a new HnefTile instance initialized with the
 * parameters extracted from serialized.
 */
int
hnef_tile_deserialize( HnefTile *tile, uint8_t serialized ) {
	
	if(!tile) {
		return 0;
	}

	/* Initialize new tile with appropriate bits */
	hnef_tile_init(
		tile,
		(serialized >> 3) & 0x03,
		(serialized >> 5) & 0x01
	);

	/* Deserialize the token bits into the tile's token attribute*/
	tile->is_occupied = hnef_token_deserialize(&(tile->token), serialized);

	/* Return the new tile */
	return 1;
}

/**
 * @brief Get the type of structure built on a HnefTile instance
 *
 * @param tile The tile whose structure we would like to identify
 *
 * @return The integer encoding for a tile's structure
 */
int
hnef_tile_get_type( HnefTile *tile ) {
	return tile->type;
}

/**
 * @brief Set the type of structure built on a HnefTile instance
 *
 * @param tile The tile whose structure we would like to set
 *
 * @param type The integer encoding for the type of stucture to be
 * placed on the tile
 */
void
hnef_tile_set_type( HnefTile *tile, int type ) {
	tile->type = type;
}

/**
 * @brief get the is_escape attribute of the tile passed as an argument
 *
 * @param tile The tile whose is_escape attribute we want to retrieve
 *
 * @return The value of the is_escape attribute of tile
 */
int
hnef_tile_get_is_occupied( HnefTile *tile ) {
	return tile->is_occupied;
}

/**
 * @brief Set the is_escape attribute of tile
 *
 * @param tile The tile whose is_escape attribute we want to set
 *
 * @param is_escape The value we would like to assign to the tile's
 * is_escape attribute
 */
void
hnef_tile_set_is_occupied( HnefTile *tile, int is_occupied ) {
	tile->is_occupied = is_occupied;
}

/**
 * @brief get the is_escape attribute of the tile passed as an argument
 *
 * @param tile The tile whose is_escape attribute we want to retrieve
 *
 * @return The value of the is_escape attribute of tile
 */
int
hnef_tile_get_is_escape( HnefTile *tile ) {
	return tile->is_escape;
}

/**
 * @brief Set the is_escape attribute of tile
 *
 * @param tile The tile whose is_escape attribute we want to set
 *
 * @param is_escape The value we would like to assign to the tile's
 * is_escape attribute
 */
void
hnef_tile_set_is_escape( HnefTile *tile, int is_escape ) {
	tile->is_escape = is_escape;
}

/**
 * @brief Get the token attribute of this tile
 *
 * @param tile The tile whose token we wish to set
 *
 * @return A pointer to the token currently standing on the tile or
 * NULL if the tile is unoccupied
 */
HnefToken
hnef_tile_get_token( HnefTile *tile ) {
	return tile->token;
}

/**
 * @brief Set the token attribute of this tile
 *
 * @param tile The tile whose token we wish to set
 *
 * @param token The token we would like to place on the tile
 */
void
hnef_tile_set_token( HnefTile *tile, HnefToken token ) {
	tile->token = token;
	tile->is_occupied = 1;
}

/**
 * @brief Set the token attribute of this tile
 *
 * @param tile The tile whose token we wish to set
 *
 * @param token The token we would like to place on the tile
 */
void
hnef_tile_unset_token( HnefTile *tile ) {
	hnef_token_init(&(tile->token), 0, 0);
	tile->is_occupied = 0;
}