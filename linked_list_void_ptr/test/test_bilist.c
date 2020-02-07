#include <stdarg.h>	//for cmocka
#include <stddef.h>	//for cmocka
#include <setjmp.h>	//for cmocka
#include <cmocka.h>	//for cmocka
#include <stdlib.h>	//for malloc
#include <stdio.h>	//for printf
#include "bilist.h"



int arr[] = {0,1,2,3,4,5,6,7,8,9} ;

void test_bilist_check_at(void **state)
{
    (void) state; /* unused */

    bilist *list = bilist_create2( arr, 10, sizeof(int) );

    assert_int_equal( 0, *(int*)bilist_at( list, 0 ) );
    assert_int_equal( 9, *(int*)bilist_at( list, 9 ) );

    bilist_delete( list );
}
void test_bilist_push_pop_front(void **state)
{
    (void) state; /* unused */

    bilist *list = bilist_create2( arr, 10, sizeof(int) );

    int hundred = 100;

    bilist_push_front( list, &hundred );

    assert_int_equal( 11, bilist_size( list ) );

    assert_int_equal( hundred, *(int*)bilist_dereference( bilist_begin( list ) ) );

    int ret = *(int*)bilist_pop_front( list );
    assert_int_equal( ret, hundred );

    assert_int_equal( 10, bilist_size( list ) );

    assert_int_equal( 0, *(int*)bilist_at( list, 0 ) );
    assert_int_equal( 9, *(int*)bilist_at( list, 9 ) );

    bilist_delete( list );
}

void test_bilist_push_pop_back(void **state)
{
    (void) state; /* unused */

    bilist *list = bilist_create2( arr, 10, sizeof(int) );

    int hundred = 100;

    bilist_push_back( list, &hundred );

    assert_int_equal( 11, bilist_size( list ) );

    assert_int_equal( hundred, *(int*)bilist_dereference( bilist_rbegin( list ) ) );

    int ret = *(int*)bilist_pop_back( list );
    assert_int_equal( ret, hundred );

    assert_int_equal( 10, bilist_size( list ) );

    assert_int_equal( 0, *(int*)bilist_at( list, 0 ) );
    assert_int_equal( 9, *(int*)bilist_at( list, 9 ) );

    bilist_delete( list );
}

void test_bilist_insert(void **state)
{
    (void) state; /* unused */

    bilist *list = bilist_create2( arr, 10, sizeof(int) );

    int hundred = 100;

    bilist_insert( list, &hundred, 0 );
    assert_int_equal( hundred, *(int*)bilist_at( list, 0 ) );
    assert_int_equal( 11, bilist_size( list ) );
    assert_int_equal( 9, *(int*)bilist_at( list, bilist_size( list )-1 ) );

    bilist_delete( list );
}


void test_bilist_loop_over(void **state)
{
    (void) state; /* unused */

    bilist *list = bilist_create2( arr, 10, sizeof(int) );


    assert_int_equal( 11, bilist_size( list ) );

    bilist_delete( list );
}


int main(void)
{
    const struct CMUnitTest test[] = {
	cmocka_unit_test(test_bilist_check_at),
	cmocka_unit_test(test_bilist_push_pop_front),
	cmocka_unit_test(test_bilist_push_pop_back),
	cmocka_unit_test(test_bilist_insert),
    };
    return cmocka_run_group_tests( test, NULL, NULL);

}



