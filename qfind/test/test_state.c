#include <stdarg.h>	//for cmocka
#include <stddef.h>	//for cmocka
#include <setjmp.h>	//for cmocka
#include <cmocka.h>	//for cmocka
#include <stdlib.h>	//for malloc
#include <stdio.h>	//for printf
#include "qfind.h"

int compare_int( const void* b, const void* original )
{
    if ( *(const int*)b == *(const int*)original ) return 0; 
    return -1;
}
void test_int_fail(void **state)
{
    (void) state; /* unused */

    int array[] = { 40, 10, 100, 90, 20, 25 };
    int criteria = 101;

    int ret = qfind( array, 6, sizeof( int ), compare_int, &criteria );

    assert_int_not_equal( 2, ret );
}
void test_int_success(void **state)
{
    (void) state; /* unused */

    int array[] = { 40, 10, 100, 90, 20, 25 };
    int criteria = 100;

    int ret = qfind( array, 6, sizeof( int ), compare_int, &criteria );

    assert_int_equal( criteria, array[ret] );
}


int compare_float( const void* b, const void* original )
{
    if ( *(const float*)b == *(const float*)original ) return 0; 
    return -1;
}
void test_float_fail(void **state)
{
    (void) state; /* unused */

    int array[] = {3.3, 2.2, 11.1, 6.6, 3.2, 4.1 };
    int criteria = 3.1;

    int ret = qfind( array, 6, sizeof( int ), compare_int, &criteria );

    assert_int_not_equal( 2, ret );
}
void test_float_success(void **state)
{
    (void) state; /* unused */

    int array[] = {3.3, 2.2, 11.1, 6.6, 3.2, 4.1 };
    int criteria = 3.2;

    int ret = qfind( array, 6, sizeof( int ), compare_int, &criteria );

    assert_float_equal( criteria, array[ret], 0.01 );
}

typedef struct sample sample;
struct sample
{
  int value;
};
sample* sample_new()
{
  sample *s;
 
  s = malloc(sizeof *s);
  if ( NULL == s ) return NULL;
 
  s->value = 0;
  return s;
}
void sample_do_imortant_jonb(sample *s)
{
    if ( NULL == s ) return;
    /*implementation being later*/
}
void sample_free(sample *s)
{
    if ( NULL != s ) free( s );
    s = NULL;
}

int sample_equal(sample* s1, sample* s2)
{
    return s1->value - s2->value;
}

int compare_sample_ptr( const void* b, const void* original )
{
    if ( 0 == sample_equal( *(sample**)b, *(sample**)original ) ) return 0; 
    return -1;
}
void test_sample_fail(void **state)
{
    (void) state; /* unused */

    sample *s0 = sample_new();
    sample *s1 = sample_new();
    sample *s2 = sample_new();
    sample *s3 = sample_new();
    sample *s4 = sample_new();
    sample *s5 = sample_new();
    s2->value = 100;

    sample* array[] = {s0, s1, s2, s3, s4, s5};
    
    int ret = qfind( array, 6, sizeof( sample* ), compare_sample_ptr, &s2 );

    assert_int_not_equal( 4, ret );
}

void test_sample_success(void **state)
{
    (void) state; /* unused */

    sample *s0 = sample_new();
    sample *s1 = sample_new();
    sample *s2 = sample_new();
    sample *s3 = sample_new();
    sample *s4 = sample_new();
    sample *s5 = sample_new();
    s2->value = 100;

    sample* array[] = {s0, s1, s2, s3, s4, s5};
    
    int ret = qfind( array, 6, sizeof( sample* ), compare_sample_ptr, &s2 );

    assert_int_equal( 2, ret );
}


int main(void)
{
    const struct CMUnitTest test[] = {
	cmocka_unit_test(test_int_fail),
	cmocka_unit_test(test_int_success),
	cmocka_unit_test(test_float_fail),
	cmocka_unit_test(test_float_success),
	cmocka_unit_test(test_sample_fail),
	cmocka_unit_test(test_sample_success),
    };
    return cmocka_run_group_tests( test, NULL, NULL);
}


