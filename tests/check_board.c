#include <stdlib.h>
#include <check.h>
#include <stdint.h>
#include "../libhnef/board.h"

START_TEST(test_board) {
	HnefBoard b1, b2;
	HnefTile t1, t2;
	HnefToken tok1, tok2;

	int h=5, w=7, i, j;
	uint8_t s[5*7+2] = {0};

	/* Create a new board */
	hnef_board_init( &b1, h, w );

	/* Test dimensions */
	ck_assert_int_eq(hnef_board_get_height(&b1), h);
	ck_assert_int_eq(hnef_board_get_width(&b1), w);
	ck_assert_int_eq(hnef_board_get_area(&b1), w*h);

	/* Board is empty by default */
	for(i=0; i<w; i++) {
		for(j=0; j<h; j++) {
			t1 = hnef_board_get_tile(&b1, i, j);
			ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_EMPTY);
			ck_assert_int_eq(hnef_board_get_tile_type(&b1, i, j), HNEF_EMPTY);
			
			ck_assert(!hnef_tile_get_is_escape(&t1));
			ck_assert(!hnef_board_get_tile_is_escape(&b1, i, j));
			
			ck_assert(!hnef_tile_get_is_occupied(&t1));
			ck_assert(!hnef_board_get_tile_is_occupied(&b1, i, j));
		}
	}

  /* Set corner tiles to castles */
	for(i=0; i<w; i+=(w-1)) {
		for(j=0; j<h; j+=(h-1)) {			
			hnef_board_set_tile_type(&b1, i, j, HNEF_CASTLE);
			hnef_board_set_tile_is_escape(&b1, i, j, HNEF_ESCAPE);
			
			t1 = hnef_board_get_tile(&b1, i, j);
			ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_CASTLE);
			ck_assert(hnef_tile_get_is_escape(&t1));
			
			ck_assert(!hnef_tile_get_is_occupied(&t1));
			ck_assert(!hnef_board_get_tile_is_occupied(&b1, i, j));
		}
	}

	/* Put a throne tile in the middle */
	hnef_board_set_tile_type(&b1, w/2, h/2, HNEF_THRONE);
	hnef_board_set_tile_is_escape(&b1, w/2, h/2, HNEF_NO_ESCAPE);

	ck_assert_int_eq(hnef_board_get_tile_type(&b1, w/2, h/2), HNEF_THRONE);
	ck_assert(!hnef_board_get_tile_is_occupied(&b1, w/2, h/2));
	
	/* Put a king on the center tile */
	hnef_token_init(&tok1, HNEF_SWEDE, HNEF_KING);
	hnef_board_set_token(&b1, w/2, h/2, tok1);
	ck_assert_int_eq(hnef_board_get_token_rank(&b1, w/2, h/2), hnef_token_get_rank(&tok1));
	ck_assert_int_eq(hnef_board_get_token_team(&b1, w/2, h/2), hnef_token_get_team(&tok1));

	/* Put regular soldier on one of the edge tiles */
	hnef_token_init(&tok1, HNEF_MUSCOVITE, HNEF_SOLDIER);
	hnef_board_set_token(&b1, w/2, 0, tok1);
	

	/* Serialize then deserialize */
	hnef_board_serialize(&b1, s);
	hnef_board_deserialize(&b2, s);

	/* Check board dimensions */
	ck_assert_int_eq(hnef_board_get_height(&b1), hnef_board_get_height(&b2));
	ck_assert_int_eq(hnef_board_get_width(&b1), hnef_board_get_width(&b2));
	ck_assert_int_eq(hnef_board_get_area(&b1), hnef_board_get_area(&b2));

	/* Ensure all tiles match */
	for(i=0; i<w; i++) {
		for(j=0; j<h; j++) {
			ck_assert_int_eq(hnef_board_get_tile_type(&b1, i, j), hnef_board_get_tile_type(&b2, i, j));
			ck_assert_int_eq(hnef_board_get_tile_is_escape(&b1, i, j), hnef_board_get_tile_is_escape(&b2, i, j));
			ck_assert_int_eq(hnef_board_get_token_team(&b1, i, j), hnef_board_get_token_team(&b2, i, j));
			ck_assert_int_eq(hnef_board_get_token_rank(&b1, i, j), hnef_board_get_token_rank(&b2, i, j));
		}
	}
}
END_TEST

Suite *
hnef_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hnefatafl");

	tc_core = tcase_create("Core");
	
	tcase_add_test(tc_core, test_board);
	
	suite_add_tcase(s, tc_core);

	return s;	
}

int
main(void) {
	int nfailed;
	Suite *s;
	SRunner *sr;
	
	s = hnef_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	nfailed = srunner_ntests_failed(sr);
	srunner_free(sr);
	
	return (nfailed == 0)? EXIT_SUCCESS : EXIT_FAILURE;
}
