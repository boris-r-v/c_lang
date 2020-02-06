#include <stdarg.h>	//for cmocka
#include <stddef.h>	//for cmocka
#include <setjmp.h>	//for cmocka
#include <cmocka.h>	//for cmocka
#include <stdlib.h>	//for malloc
#include <stdio.h>	//for printf
#include "bilist.h"



void test_bilist_fail(void **state)
{
    (void) state; /* unused */

    assert_int_not_equal( 2, 3 );
}
void test_bilist_success(void **state)
{
    (void) state; /* unused */


    assert_int_equal( 2, 2 );
}


int main(void)
{
    const struct CMUnitTest test[] = {
	cmocka_unit_test(test_bilist_fail),
	cmocka_unit_test(test_bilist_success),
    };
    return cmocka_run_group_tests( test, NULL, NULL);
}


