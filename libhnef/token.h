/* libhnef/token.h
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/token.h
 *
 * @brief Macros, typedefs and function forward declarations for the
 * HnefToken object.
 *
 * @author Gary Munnelly
 */

#ifndef LIBHNEF_TOKEN_H_
#define LIBHNEF_TOKEN_H_

#include <stdint.h>
#include <stdlib.h>

#define HNEF_MUSCOVITE 0x00 /**< Token belongs to muscovite team */
#define HNEF_SWEDE     0x01 /**< Token belongs to swede team */
#define HNEF_SOLDIER   0x00 /**< Token is a rank and file soldier */
#define HNEF_KING      0x01 /**< Token is a king */

#ifdef _cplusplus
extern "C" {
#endif
	
/**
 * @brief Represents a moveable playing piece in the game.
 */
typedef struct HnefToken {	
	int rank; /**< Token's rank in the game. Either Soldier or King */
	int team; /**< Token's team alignment. Either Swede or Muscovite */
} HnefToken;

void         hnef_token_init               ( HnefToken *token, int team, int rank )	;
uint8_t      hnef_token_serialize          ( HnefToken *t );
int          hnef_token_deserialize        ( HnefToken *token, uint8_t serialized );	

int          hnef_token_get_team           ( HnefToken *t );
void         hnef_token_set_team           ( HnefToken *t, int team );
int          hnef_token_get_rank           ( HnefToken *t );
void         hnef_token_set_rank           ( HnefToken *t, int rank );

#ifdef _cplusplus
}
#endif

#endif /* LIBHNEF_TOKEN_H_ */
