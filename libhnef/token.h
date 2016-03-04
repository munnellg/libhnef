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
 * @brief Allows us to call _hneftoken as HnefToken
 */
typedef struct _hneftoken  HnefToken;

HnefToken*   hnef_token_new                ( int team, int rank );
uint8_t      hnef_token_serialize          ( HnefToken *t );
HnefToken*   hnef_token_deserialize        ( uint8_t serialized );	

int          hnef_token_get_team           ( HnefToken *t );
void         hnef_token_set_team           ( HnefToken *t, int team );
int          hnef_token_get_rank           ( HnefToken *t );
void         hnef_token_set_rank           ( HnefToken *t, int rank );

void         hnef_token_free               ( HnefToken *t );

#ifdef _cplusplus
}
#endif

#endif /* LIBHNEF_TOKEN_H_ */
