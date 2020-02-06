#include <stdio.h>	//for printf
#include "bilist.h"


void bilist_int_print( bilist* list )
{
    bilist_iterator b = bilist_begin( list );
    
    for ( ; b != bilist_end( list ); b = bilist_next( b ) )
    {
	printf ( "%d ", *(int*)bilist_get( b ) );
    }
	printf ( "\n" );

}


int main(void)
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    bilist *list = bilist_create2( arr, 10, sizeof(int) );
    printf ( "size %d\n", bilist_size ( list ) );
/*
    bilist_int_print( list );


    int *r = (int*)bilist_at( list, 4 );
    printf( "DATA: %d\n", *r );

*/
    int hundred = 100;

    bilist_push_front( list, &hundred );

    bilist_int_print( list );

    int ret = *(int*)bilist_pop_front( list );

    bilist_int_print( list );

    printf ( "size %d\n", bilist_size ( list ) );

    
    return 0;

}



