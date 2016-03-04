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
struct _hneftile {
	HnefToken* token;    /**< Pointer to the HnefToken standing on this tile */
	int type;            /**< Type of structure built on this tile */
	int is_escape;       /**< Boolean denoting whether the king can
												* escape via this tile or not */
};

/**
 * @brief Allocates memory for a new tile object and returns the
 * result initialized with the parameters passed. Will return NULL on
 * failure to allocate.
 *
 * @param type The type of structure built on this tile
 *
 * @param is_escape A boolean denoting whether or not the king can
 * escape via this tile
 *
 * @param token A pointer to a token that is currently standing on
 * this tile. Pass NULL for a tile with no token on it
 *
 * @return A pointer to the newly allocated tile or NULL on failed
 * allocation
 */
HnefTile*
hnef_tile_new( int type, int is_escape, HnefToken *token ) {
	HnefTile *tile;

	/* Allocate memory to tile */
	tile = malloc(sizeof(*tile));

	/* Test if allocation was successful and initialize object if so */
	if(tile) {
			tile->type = type;
			tile->is_escape = is_escape;
			tile->token = token;
	}

	/* Return the new tile or NULL on failed allocation */
	return tile;
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
		c |= hnef_token_serialize(hnef_tile_get_token(tile));
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
HnefTile *
hnef_tile_deserialize( uint8_t serialized ) {
	HnefTile *tile;
	HnefToken *token;

	/* Start by deserializing the token bits */
	token = hnef_token_deserialize(serialized);

	/* Initialize new tile with appropriate bits and extracted token */
	tile = hnef_tile_new(
		(serialized >> 3) & 0x03,
		(serialized >> 5) & 0x01,
		token);

	/* Return the new tile */
	return tile;
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
HnefToken*
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
hnef_tile_set_token( HnefTile *tile, HnefToken *token ) {
	tile->token = token;
}

/**
 * @brief Replaces any token currently standing on this tile with the
 * token passed as an argument. Useful for operations such as captures
 * (where NULL would be passed as an argument). This function will
 * return a pointer to the token that was replaced so that it is not
 * lost in the process.
 *
 * @param tile The tile whose token we wish to replace
 *
 * @param token The token which we would like to place on the tile
 *
 * @return A pointer to the token that was replaced on the tile
 */
HnefToken*
hnef_tile_replace_token( HnefTile *tile, HnefToken *token ) {
	HnefToken *tmp;
	
	tmp = tile->token;
	tile->token = token;
	return tmp;
}

/**
 * @brief Test to see if there is a token standing on this instance of
 * HnefTile
 *
 * @param tile The tile whose occupancy we wish to test
 * 
 * @return True if there is a token on this tile. False otherwise
 */
int
hnef_tile_is_occupied( HnefTile *tile ) {
	return tile->token != NULL;
}

/**
 * @brief Release the memory allocated to this tile instance. Will
 * also deallocate the memory allocated to any tokens standing on this
 * tile
 *
 * @param tile The tile whose memory we wish to deallocate
 */
void
hnef_tile_free( HnefTile *tile ) {
	if(tile) {
		hnef_token_free(tile->token);
		free(tile);		
	}
}


