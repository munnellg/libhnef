#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libhnef/tile.h"

START_TEST(test_tile) {
	HnefTile t1, t2;
	HnefToken tok1, tok2;
	uint8_t s;
	
	hnef_token_init(&tok1, HNEF_MUSCOVITE, HNEF_KING);
	
	hnef_tile_init( &t1, HNEF_CASTLE, HNEF_NO_ESCAPE);
	ck_assert(!hnef_tile_get_is_occupied(&t1));
	

	/* Test getters and setters for tile type */
	ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_CASTLE);
	hnef_tile_set_type(&t1, HNEF_EMPTY);
	ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_EMPTY);
	hnef_tile_set_type(&t1, HNEF_CAMP);
	ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_CAMP);
	hnef_tile_set_type(&t1, HNEF_THRONE);
	ck_assert_int_eq(hnef_tile_get_type(&t1), HNEF_THRONE);

	/* Test getters and setters for tile is_escape */
	ck_assert_int_eq(hnef_tile_get_is_escape(&t1), HNEF_NO_ESCAPE);
 	hnef_tile_set_is_escape(&t1, HNEF_ESCAPE);
	ck_assert_int_eq(hnef_tile_get_is_escape(&t1), HNEF_ESCAPE);
	
	hnef_tile_set_token(&t1, tok1);	
	tok2 = hnef_tile_get_token(&t1);
	ck_assert_int_eq(hnef_token_get_team(&tok1), hnef_token_get_team(&tok2));
	ck_assert_int_eq(hnef_token_get_rank(&tok1), hnef_token_get_rank(&tok2));
	ck_assert(hnef_tile_get_is_occupied(&t1));
	
	/* Test serialization */
	s = hnef_tile_serialize(&t1);
	hnef_tile_deserialize(&t2, s);

	ck_assert_int_eq(hnef_tile_get_type(&t1), hnef_tile_get_type(&t2));
	ck_assert_int_eq(hnef_tile_get_is_escape(&t1),  hnef_tile_get_is_escape(&t2));
	ck_assert(hnef_tile_get_is_occupied(&t2));
	
	tok2 = hnef_tile_get_token(&t2);
	ck_assert_int_eq(hnef_token_get_team(&tok1), hnef_token_get_team(&tok2));
	ck_assert_int_eq(hnef_token_get_rank(&tok1), hnef_token_get_rank(&tok2));
}
END_TEST

Suite *
hnef_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hnefatafl Token");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_tile);
	
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
