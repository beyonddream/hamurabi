#define _HAMURABI_TEST
#include "../include/hamurabi.h"
#include <check.h>
#include <stdbool.h>
#include <stdlib.h>


START_TEST(test_init)
{
#define RANDOM_TEST(n) n
	ck_assert_int_eq(RANDOM(3), 3);
#undef RANDOM_TEST
}
END_TEST

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	Suite *suite;
	SRunner *sr;
	TCase *tc;
	int num_failed = 0;

	suite = suite_create("hamurabi");

	tc = tcase_create("basic tests");
	tcase_add_test(tc, test_init);
	suite_add_tcase(suite, tc);

	sr = srunner_create(suite);
	srunner_set_log(sr, "hamurabi.log");
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);

	num_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return num_failed;
}
