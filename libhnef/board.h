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

/* Allow us to compile this file as a C++ library */
#ifdef _cplusplus
extern "C" {
#endif

/**
 * @brief typedef allowing us to call _hnefboard as HnefBoard
 */
typedef struct _hnefboard  HnefBoard; 

HnefBoard*   hnef_board_new                ( int h, int w );
uint8_t*     hnef_board_serialize          ( HnefBoard *b );
HnefBoard*   hnef_board_deserialize        ( uint8_t *buf );

int          hnef_board_get_height         ( HnefBoard *b );
int          hnef_board_get_width          ( HnefBoard *b );
int          hnef_board_get_area           ( HnefBoard *b );	
HnefTile*    hnef_board_get_tile           ( HnefBoard *b, int x, int y );
void         hnef_board_set_tile           ( HnefBoard *b, int x, int y, HnefTile *t );
int          hnef_board_get_tile_type      ( HnefBoard *b, int x, int y );
int          hnef_board_get_tile_is_escape ( HnefBoard *b, int x, int y );
HnefTile*    hnef_board_replace_tile       ( HnefBoard *b, int x, int y, HnefTile *t );
HnefToken*   hnef_board_get_token          ( HnefBoard *b, int x, int y );
void         hnef_board_set_token          ( HnefBoard *b, int x, int y, HnefToken *t );
int          hnef_board_get_token_rank     ( HnefBoard *b, int x, int y );
int          hnef_board_get_token_team     ( HnefBoard *b, int x, int y );
HnefToken*   hnef_board_replace_token      ( HnefBoard *b, int x, int y, HnefToken *t );
int          hnef_board_is_occupied        ( HnefBoard *b, int x, int y );

void         hnef_board_free               ( HnefBoard *b );

#ifdef _cplusplus
}
#endif

#endif /* LIBHNEF_BOARD_H */
