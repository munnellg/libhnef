/* libhnef/board.c
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/board.c
 *
 * @brief Code for manipulating a board of tiles for the game
 * Hnefatafl
 *
 * @author Gary Munnelly
 */
#include "board.h"

/**
 * @brief Represents a board on which a game of hnefatafl may be
 * played. Maintains a dynamic array of tiles, a height, width and
 * area parameter
 */
struct _hnefboard {
	int height;           /**< Height of the board */
	int width;            /**< Width of the board */
	int area;             /**< Area of the board */
	HnefTile **tiles;     /**< HnefTiles of which the board is comprised */
};

/**
 * @brief Allocate memory for a new instance of the HnefBoard
 * struct. This function will return NULL in the event that the
 * allocation fails.
 *
 * @param height The height of the game board
 *
 * @param width The width of the game board
 *
 * @return A pointer to the newly allocated board or NULL on failed
 * allocation
 */
HnefBoard*
hnef_board_new ( int height, int width ) {
	HnefBoard *board;
	int i;

	/* Allocate memory for the board */
	board = malloc(sizeof(*board));

  /* If allocaion was successful, start populating the new struct */
	if(board) {
			board->height = height;
			board->width = width;
			board->area = height*width;
			board->tiles = malloc(board->area*sizeof(*(board->tiles)) );

			/* If we failed to allocate memory for the tiles array, then
			 * free the board and return NULL. The allocation has failed */
			if(!board->tiles) {
				hnef_board_free(board);
				return NULL;
			}
			
			/* Initialize board with blank, empty tiles */
			for( i=0; i<board->area; i++ ) {
				board->tiles[i] = hnef_tile_new( HNEF_EMPTY, HNEF_NO_ESCAPE, NULL );	
			}
	}

	/* Return the new board. Note, the board will be NULL if memory
	 * allocation failed */
	return board;
}

/**
 * @brief Serializes the HnefBoard object passed as a parameter into
 * an array of bytes where each array element represents a single tile
 * on the board. The first two elements of the array are the height
 * and width respectively. Their product will give the number of
 * remaining elements in the array.
 *
 * @param board The board to be serialized into a buffer
 *
 * @return An array of 8 bit bytes where each element represents a
 * game tile except for the first two elements which are height and
 * width respectively
 */
uint8_t*
hnef_board_serialize( HnefBoard *board ) {
	HnefTile *tile;
	int area, height, width, x, y;
	uint8_t serialized, *buffer;

	/* Get board attributes */
	area = hnef_board_get_area(board);
	height = hnef_board_get_height(board);
	width = hnef_board_get_width(board);

	/* Allocate memory for the serialized buffer and initialize first
	 * two elements */
	buffer = malloc((area+2)*sizeof(buffer));
	buffer[0] = height;
	buffer[1] = width;

	/* Serialize each tile and store in the appropriate buffer slot */
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {
			tile = hnef_board_get_tile(board, x, y);
			serialized = hnef_tile_serialize(tile);
			buffer[y*height+x+2] = serialized;
		}
	}

	/* Return the serialized board representation */
	return buffer;
}

/**
 * @brief Deserialize the buffer passed as an argument into the
 * HnefBoard struct that it represents.
 *
 * @param buffer The buffer containing the data to be deserialized
 *
 * @return A pointer to a HnefBoard object built from the data in
 * buffer
 */
HnefBoard*
hnef_board_deserialize( uint8_t* buffer ) {
	HnefBoard *board;
	HnefTile *tile;
	int height, width, x, y;

	/* Extract height and width from the buffer */
	height = buffer[0];
	width  = buffer[1];

	/* Allocate memory for a new board */
	board = hnef_board_new(height, width);

	/* Replace default board tiles with deserialized board tiles */
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {
			/* Deserialize tile */
			tile = hnef_tile_deserialize(buffer[y*height + x + 2]);
			/* Replace default tile with deserialized tile */
			tile = hnef_board_replace_tile(board, x, y, tile);
			/* Free the default tile */
			free(tile);		
		}
	}

	/* Return the deserialized board */
	return board;
}

/**
 * @brief Get the height attribute of the HnefBoard passed as an
 * argument
 *
 * @param board The board whose height we wish to determine
 *
 * @return The height attribute of board
 */
int
hnef_board_get_height ( HnefBoard *board ) {
	return board->height;
}

/**
 * @brief Get the width attribute of the HnefBoard passed as an
 * argument
 *
 * @param board The board whose width we wish to determine
 *
 * @return The width attribute of board
 */
int
hnef_board_get_width ( HnefBoard *board ) {
	return board->width;
}

/**
 * @brief Get the area attribute of the HnefBoard passed as an
 * argument
 *
 * @param board The board whose area we wish to determine
 *
 * @return The area attribute of board
 */
int
hnef_board_get_area( HnefBoard *board ) {
	return board->area;
}

/**
 * @brief Determine whether or not the tile at the given coordinates
 * is occupied by a token.
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return True if the tile at (x,y) is occupied, false otherwise
 */
int
hnef_board_is_occupied( HnefBoard *board, int x, int y ) {
	HnefTile *tile;
	
	tile = hnef_board_get_tile( board, x, y );
	return hnef_tile_is_occupied( tile );
}

/**
 * @brief Get the board tile located at the coordinates passed as arguments
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return A pointer to the tile at coordinates (x,y)
 */
HnefTile*
hnef_board_get_tile( HnefBoard *board, int x, int y ) {
	int height;
	
	height = hnef_board_get_height(board);
	return board->tiles[height*y + x];
}

/**
 * @brief Update the pointer at the coordinates passed as arguments so
 * that they point to the tile passed as an argument
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @param tile The tile we would like to assign to the coordinates (x,y)
 */
void
hnef_board_set_tile( HnefBoard *board, int x, int y, HnefTile *tile ) {
	int height;
	
	height = hnef_board_get_height(board);
	board->tiles[ height*y + x ] = tile;
}

/**
 * @brief Get the integer code for the structure built on the tile
 * located at the coordinates passed as arguments.
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return The integer code of the structure built on the tile at
 * coordinates (x,y)
 */
int
hnef_board_get_tile_type( HnefBoard *board, int x, int y ) {
	HnefTile *tile;

	tile = hnef_board_get_tile(board, x, y);
	return hnef_tile_get_type(tile);
}


/**
 * @brief Determine whether or not the tile at the given coordinates
 * is a tile via which the king may escape
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return True if the tile at (x,y) is an escape tile, false otherwise
 */
int
hnef_board_get_tile_is_escape( HnefBoard *board, int x, int y ) {
	HnefTile *tile;

	tile = hnef_board_get_tile(board, x, y);
	return hnef_tile_get_is_escape(tile);
}

/**
 * @brief Replaces the tile at the passed coordinates with the tile
 * passed as an argument. This function will return a pointer to the
 * tile that was replaced so that it is not lost in the process.
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @param tile The tile which we would like to position at the given
 * coordinates
 *
 * @return A pointer to the tile that was replaced
 */
HnefTile*
hnef_board_replace_tile( HnefBoard *board, int x, int y, HnefTile *tile ) {
	HnefTile *tmp;

	tmp = hnef_board_get_tile(board, x, y);
	hnef_board_set_tile( board, x, y, tile );
	return tmp;
}

/**
 * @brief Get the token attribute of the tile positioned at the
 * coordinates passed as coordinates
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return A pointer to the token currently standing on the tile or
 * NULL if the tile is unoccupied
 */
HnefToken*
hnef_board_get_token( HnefBoard *board, int x, int y ) {
	HnefTile *tile;
	
	tile = hnef_board_get_tile( board, x, y );
	return hnef_tile_get_token( tile );
}

/**
 * @brief Set the token attribute of the tile positioned at the
 * coordinates passed as coordinates
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @param token A pointer to the token we would like to place on the
 * tile at (x,y)
 */
void
hnef_board_set_token( HnefBoard *board, int x, int y, HnefToken *token ) {
	HnefTile *tile;
	
	tile = hnef_board_get_tile( board, x, y );
	hnef_tile_set_token( tile, token );
}

/**
 * @brief Get the rank of the token positioned at the coordinates
 * passed as arguments
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return The integer encoding of the rank of the token or -1 if
 * there is no token on the tile
 */
int
hnef_board_get_token_rank( HnefBoard *board, int x, int y ) {
	HnefToken *token;

	token = hnef_board_get_token( board, x, y );
	return token? hnef_token_get_rank(token) : -1;
}

/**
 * @brief Get the team of the token positioned at the coordinates
 * passed as arguments
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @return The integer encoding of the team of the token or -1 if
 * there is no token on the tile
 */
int
hnef_board_get_token_team( HnefBoard *board, int x, int y ) {
	HnefToken *token;

	token = hnef_board_get_token( board, x, y );
	return token? hnef_token_get_team(token) : -1;
}

/**
 * @brief Replaces any token currently standing on this tile with the
 * token passed as an argument. Useful for operations such as captures
 * (where NULL would be passed as an argument). This function will
 * return a pointer to the token that was replaced so that it is not
 * lost in the process.
 *
 * @param board The board whose tiles we are examining
 *
 * @param x The x coordinate of the tile we wish to examine
 *
 * @param y The y coordinate of the tile we wish to examine
 *
 * @param token Pointer to the token we would like to place on the
 * tile at (x,y)
 *
 * @return Pointer to the token that was previously positioned at
 * (x,y) or NULL if the tile was unoccupied
 */
HnefToken*
hnef_board_replace_token( HnefBoard *board, int x, int y, HnefToken *token ) {
	HnefTile *tile;
	tile = hnef_board_get_tile( board, x, y );
	return hnef_tile_replace_token( tile, token );
}

/**
 * @brief Deallocate the memory that was given to the HnefBoard object
 * passed as an argument. This will also free all the memory allocated
 * to the tiles of which the board is comprised and, by extension, any
 * tokens that are standing on those tiles.
 *
 * @param board The board whose memory we wish to deallocate 
 */
void
hnef_board_free( HnefBoard *board ) {
	HnefTile *tile;
	int x, y;
	int height, width;

	/* Get the height and width of the board */
	height = hnef_board_get_height(board);
	width = hnef_board_get_width(board);

	/* Deallocate the memory for each individual tile */
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {
			tile = hnef_board_get_tile( board, x, y );
			hnef_tile_free(tile);
		}
	}

	/* Free all memory */
	free(board->tiles);
	free(board);
}
