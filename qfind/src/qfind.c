#include <stdlib.h>
 
#include "qfind.h"
 
int qfind (void* first, size_t total_elem, size_t size, int (*cmp)(const void*,const void*), const void* criteria )
{
    if ( 0 == total_elem )
	return -1;

    char* begin = (char*) first;
    char* end = begin + total_elem*size;

    int pos = 0;
    while( begin < end )
    {
	if ( 0 == (*cmp)( begin, criteria ) )
	    return pos;
	pos++;
	begin += size;
    }
    
    return -1;
}
