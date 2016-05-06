#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libhnef/token.h"

START_TEST(test_token)
{
	HnefToken t1, t2;
	uint8_t s;
		
	hnef_token_init( &t1, HNEF_MUSCOVITE, HNEF_KING );

	ck_assert_int_eq(hnef_token_get_team(&t1), HNEF_MUSCOVITE);
	ck_assert_int_eq(hnef_token_get_rank(&t1), HNEF_KING);

	hnef_token_set_team(&t1, HNEF_SWEDE);
	hnef_token_set_rank(&t1, HNEF_SOLDIER);
	
	ck_assert_int_eq(hnef_token_get_team(&t1), HNEF_SWEDE);
	ck_assert_int_eq(hnef_token_get_rank(&t1), HNEF_SOLDIER);

	s = hnef_token_serialize( &t1 );
	ck_assert(hnef_token_deserialize( &t2, s ));

	ck_assert_int_eq(hnef_token_get_team(&t1), hnef_token_get_team(&t2));
	ck_assert_int_eq(hnef_token_get_rank(&t1), hnef_token_get_rank(&t2));
}
END_TEST

Suite *
hnef_suite(void) {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hnefatafl Token");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_token);
	
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
