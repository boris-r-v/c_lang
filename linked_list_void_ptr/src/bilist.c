#include "bilist.h"
#include "bilist_private.h"
#include <stdlib.h>	//for malloc
#include <stdint.h>	//for int8_t

static bilist_iterator create_node( void* data );
static bilist_iterator find_iterator( bilist const* list, size_t index );

typedef bilist_iterator iter;

bilist* bilist_create( )
{
    bilist* list = (bilist*) malloc( sizeof(bilist) );
    list -> size = 0;
    list -> head = list->tail = NULL;
    return list;
}

bilist* bilist_create2( void* array, size_t size, size_t element_size )
{
    bilist *list = bilist_create();
    int8_t* array_ptr = (int8_t*)(array);
    
    size_t i;
    for ( i = 0; i < size; ++i )
    {
	bilist_push_back( list, array_ptr );
	array_ptr += element_size;
    }
    return list;
}

void bilist_delete( bilist* list)
{
    bilist_iterator b = bilist_begin( list );
    bilist_iterator next = NULL;
    while ( b )
    {
	next = b->next;
	free( b );
	b = next;
    }    
}

int bilist_size( bilist const* list )
{
    return list->size;
}

int bilist_empty( bilist const* list )
{
    return 0 == list->size ? TRUE : FALSE;
}

void bilist_push_back ( bilist* list, void* data )
{
    iter it = create_node( data );

    it->prev = list->tail;
    if ( list->tail )
	 list->tail->next = it;

    list->tail = it;

    if ( NULL == list->head )
	list->head = it;
    ++list->size;
}

void bilist_push_front ( bilist* list, void* data )
{
    iter it = create_node( data );

    it->next = list->head;
    if ( list->head )
	list->head->prev = it;

    list->head = it;

    if ( NULL == list->tail )
	list->tail = it;
    ++list->size;
}

void* bilist_pop_back ( bilist* list )
{
    if ( list->tail )
    {
	--list->size;
        iter it = list->tail;
	list->tail = it->prev;
	if ( list->tail )
	    list->tail->next = NULL;
	return it->data;
    }
    return NULL;
}

void* bilist_pop_front ( bilist* list )
{
    if ( list->head )
    {
	--list->size;
	iter it = list->head;
	list->head = it->next;
	if ( list->head )
	    list->head->prev = NULL;
	return it->data;
    }
    return NULL;
}

bilist_iterator bilist_begin( bilist* list )
{
    return list->head;
}

bilist_iterator bilist_end( bilist* list )
{
    return list->tail->next;
}

bilist_iterator bilist_next( bilist_iterator it )
{
    return it->next;
}
bilist_iterator bilist_rbegin( bilist* list )
{
    return list->tail;

}
bilist_iterator bilist_rend( bilist* list )
{
    return list->head->prev;
}
bilist_iterator bilist_prev( bilist_iterator it )
{
    return it->prev;	
}
void* bilist_dereference( bilist_iterator iterator )
{
    return iterator->data;
}
int bilist_insert ( bilist* list, void* data, size_t index )
{
    iter find = find_iterator( list, index );
    if ( !find ) return BILIST_WRONG_INDEX;

    iter it = create_node( data );
    iter prev_find = find->prev;

    if ( prev_find )
    {
	prev_find->next = it;
	it->prev = prev_find;
    }
    else
	list->head = it;

    find->prev = it;
    it->next = find;
    ++list->size;
    
    return BILIST_OK;    
}

void* bilist_at ( bilist* list, size_t index )
{
    iter it = find_iterator( list, index );
    if ( it )
	return it->data;
    return NULL;
}

void* bilist_front( bilist const* list )
{
    return list->head;
}
void* bilist_back( bilist const* list )
{
    return list->tail;
}


//-----------------------------STATICS------------------------

static bilist_iterator create_node( void* _data )
{
    bilist_iterator it = (bilist_iterator) malloc( sizeof( bilist_node ) );
    it->data = _data;
    it->prev = it->next = NULL;
    return it;
}

static bilist_iterator find_iterator( bilist const* list, size_t index )
{
    iter it = NULL;
    int pos = 0;
    for( it = list->head; it && pos < index; it = it->next, ++pos );
    return it; 
}

