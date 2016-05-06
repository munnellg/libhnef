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
hnef_board_init ( HnefBoard *board, int height, int width ) {
	int i;
	if(board) {
		board->height = height;
		board->width = width;
		board->area = height*width;
		
		/* Initialize board with blank, empty tiles */
		for( i=0; i<board->area; i++ ) {
			hnef_tile_init( &(board->tiles[i]), HNEF_EMPTY, HNEF_NO_ESCAPE );	
		}
	}
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
void
hnef_board_serialize( HnefBoard *board, uint8_t *buffer ) {
	HnefTile *tile;
	int area, height, width, x, y;
	uint8_t serialized;

	/* Get board attributes */
	area = hnef_board_get_area(board);
	height = hnef_board_get_height(board);
	width = hnef_board_get_width(board);

	/* initialize first two buffer elements */	
	buffer[0] = height;
	buffer[1] = width;

	/* Serialize each tile and store in the appropriate buffer slot */
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {			
			serialized = hnef_tile_serialize(&(board->tiles[board->height*y+x]));
			buffer[y*height+x+2] = serialized;
		}
	}
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
int
hnef_board_deserialize( HnefBoard *board, uint8_t* buffer ) {	
	int height, width, x, y;

	/* Extract height and width from the buffer */
	height = buffer[0];
	width  = buffer[1];

	/* Allocate memory for a new board */
	hnef_board_init(board, height, width);

	/* Replace default board tiles with deserialized board tiles */
	for( y=0; y<height; y++ ) {
		for( x=0; x<width; x++ ) {
			/* Deserialize tile */
			if(!hnef_tile_deserialize(&board->tiles[y*height+x], buffer[y*height + x + 2])) {
				return 0;
			}
		}
	}

	/* Return the deserialized board */
	return 1;
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
HnefTile
hnef_board_get_tile( HnefBoard *board, int x, int y ) {
	return board->tiles[board->height*y+x];
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
hnef_board_set_tile( HnefBoard *board, int x, int y, HnefTile tile ) {	
	board->tiles[board->height*y+x] = tile;
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
	return hnef_tile_get_type(&(board->tiles[board->height*y+x]));
}

void
hnef_board_set_tile_type( HnefBoard *board, int x, int y, int type ) {
	hnef_tile_set_type(&(board->tiles[board->height*y+x]), type);
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
	return hnef_tile_get_is_escape(&(board->tiles[board->height*y+x]));
}

void
hnef_board_set_tile_is_escape( HnefBoard *board, int x, int y, int is_escape ) {
	hnef_tile_set_is_escape(&(board->tiles[board->height*y+x]), is_escape);
}

int
hnef_board_get_tile_is_occupied( HnefBoard *board, int x, int y ) {
	return hnef_tile_get_is_occupied(&(board->tiles[board->height*y+x]));
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
HnefToken
hnef_board_get_token( HnefBoard *board, int x, int y ) {	
	return hnef_tile_get_token(&(board->tiles[board->height*y+x]));
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
hnef_board_set_token( HnefBoard *board, int x, int y, HnefToken token ) {	
	hnef_tile_set_token( &(board->tiles[board->height*y + x]), token );
}

int
hnef_board_get_token_rank ( HnefBoard *b, int x, int y ) {
	return b->tiles[b->height*y + x].token.rank;
}

int
hnef_board_get_token_team ( HnefBoard *b, int x, int y ) {
	return b->tiles[b->height*y + x].token.team;
}