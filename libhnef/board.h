/* libhnef/tile.h
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/board.h
 *
 * @brief Macros, typedefs and function forward declarations for the
 * HnefBoard struct
 *
 * @author Gary Munnelly
 */

#ifndef LIBHNEF_BOARD_H
#define LIBHNEF_BOARD_H

#include "tile.h"

#define MAX_WIDTH  32
#define MAX_HEIGHT 32

/* Allow us to compile this file as a C++ library */
#ifdef _cplusplus
extern "C" {
#endif

/**
 * @brief Represents a board on which a game of hnefatafl may be
 * played. Maintains a dynamic array of tiles, a height, width and
 * area parameter
 */
typedef struct HnefBoard {
	int height;           /**< Height of the board */
	int width;            /**< Width of the board */
	int area;             /**< Area of the board */
	HnefTile tiles[MAX_HEIGHT*MAX_HEIGHT];     /**< HnefTiles of which the board is comprised */
} HnefBoard; 

HnefBoard*   hnef_board_new                   ( int h, int w );
void         hnef_board_serialize             ( HnefBoard *b, uint8_t *buffer);
int          hnef_board_deserialize           ( HnefBoard *board, uint8_t *buf );

int          hnef_board_get_height            ( HnefBoard *b );
int          hnef_board_get_width             ( HnefBoard *b );
int          hnef_board_get_area              ( HnefBoard *b );	
HnefTile     hnef_board_get_tile              ( HnefBoard *b, int x, int y );
void         hnef_board_set_tile              ( HnefBoard *b, int x, int y, HnefTile t );
int          hnef_board_get_tile_type         ( HnefBoard *b, int x, int y );
void         hnef_board_set_tile_type         ( HnefBoard *b, int x, int y, int type );
int          hnef_board_get_tile_is_escape    ( HnefBoard *b, int x, int y );
void         hnef_board_set_tile_is_escape    ( HnefBoard *b, int x, int y, int is_escape );
HnefToken    hnef_board_get_token             ( HnefBoard *b, int x, int y );
int          hnef_board_get_tile_is_occupied  ( HnefBoard *b, int x, int y );
void         hnef_board_set_token             ( HnefBoard *b, int x, int y, HnefToken t );
int          hnef_board_get_token_rank        ( HnefBoard *b, int x, int y );
int          hnef_board_get_token_team        ( HnefBoard *b, int x, int y );

#ifdef _cplusplus
}
#endif

#endif /* LIBHNEF_BOARD_H */
