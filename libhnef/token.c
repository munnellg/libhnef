/* libhnef/token.c
 *
 * Copyright (C) 2016 Gary Munnelly
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
/**
 * @file libhnef/token.c

 * @brief Code for managing indivudual playing pieces on the
 * board. Includes functions for serializing and deserializing the
 * playing pieces into 8 bit encoded representations.
 *
 * @author Gary Munnelly
 */
#include "token.h"

void
hnef_token_init( HnefToken *token, int team, int rank ) {
	if(token) {
		token->team = team;
		token->rank = rank;
	}
}

/**
 * @brief Serialize a HnefToken object into its binary
 * representation. Requires 3 bits to store the data.
 *
 * The first bit is a test bit to ensure that the serialization was
 * successful as a common soldier for one of the teams will have the
 * encoding 0 0. It will always be set to 1.
 *
 * The second bit is the token's team - 1 for Swede, 0 for Muscovite
 *
 * The third bit is the token's rank - 0 for king, 1 for soldier
 *
 * @param token The token to be serialized
 *
 * @return A byte with the encoding for token or 0 if serialization
 * failed
 */
uint8_t
hnef_token_serialize ( HnefToken *token ) {
	uint8_t serialized;
	int rank, team;

	/* Start with empty representation */
	serialized = 0;

	/* Ensure we've been passed a valid token */
	if (token) {
		/* Get object properties */
		rank = hnef_token_get_rank(token);
		team = hnef_token_get_team(token);

		/* Serialize object */
		serialized = (serialized | rank) << 1;
		serialized = (serialized | team) << 1;
		serialized |= 0x01;		
	}

	/* Return serialized object */
	return serialized;
}

int
hnef_token_deserialize( HnefToken *token, uint8_t serialized ) {
	
	/* Check out test bit to ensure serialized is valid */
	if( !(serialized & 0x01)  || !token ) {
		return 0;
	}
	
	/* Extract info from serialized and pass it to a constructor */
	hnef_token_init( token,
		(serialized >> 1) & 0x01,
		(serialized >> 2) & 0x01
	);
	return 1;	
}

/**
 * @brief Get the team code for the HnefToken passed as argument
 *
 * @param token Token whose team we want to determine
 *
 * @return The team to which token belongs encoded as an int
 */
int
hnef_token_get_team( HnefToken *token ) {
	return token->team;
}

/**
 * @brief Set the team code for the HnefToken passed as argument
 *
 * @param token Token whose team we want to set
 *
 * @param team The team to which we would like to assign the token
 */
void
hnef_token_set_team( HnefToken *token, int team ) {
	token->team = team;
}

/**
 * @brief Get the rank code for the HnefToken passed as argument
 *
 * @param token Token whose rank we want to determine
 *
 * @return The token's rank encoded as an int
 */
int
hnef_token_get_rank( HnefToken *token ) {
	return token->rank;
}

/**
 * @brief Set the rank code for the HnefToken passed as argument
 *
 * @param token Token whose team we want to set
 *
 * @param rank The rank which we would like to assign to token
 */
void
hnef_token_set_rank( HnefToken *token, int rank ) {
	token->rank = rank;
}
