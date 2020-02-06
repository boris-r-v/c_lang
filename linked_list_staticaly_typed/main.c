/*
copyright Boris Rozhkin borisrozhkin@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct		//Структура хранимая в списке
{
    int num; 		//некоторые полезные данные
} Node;

Node* node_create( int d )
{
    static int i = 0;
    Node* ret = (Node*) malloc(sizeof(Node) );
    ret -> num = d ? d : i++;
    return ret;
}

typedef struct		//Другая структура НЕ хранимая в списке
{
    int num; 		//некоторые полезные данные
} Node_wr;

Node_wr* node_wr_create( int d )
{
    Node_wr* ret = (Node_wr*) malloc(sizeof(Node) );
    ret -> num = d;
    return ret;
}

#define StoreData Node
#include "list.h"

void n_list_print( LIST_GET_TYPE *nlist )
{
    printf("------------%d------------\n", LIST_SIZE( nlist ) );
    LIST_NODE_GET_TYPE* n = LIST_BEGIN_NODE( nlist );
    int i = 0;
    for (; n; n = LIST_NEXT_NODE( n ) )
    {
	Node* d = LIST_NODE_DATA ( n );
	printf ( "index: %d,  data: %d\n", i, d->num ); 
	++i;
    }
    printf("-------------------------\n");
}
void work_node()
{


    LIST_GET_TYPE *nlist = LIST_CREATE();
    Node* e0 = node_create(0);
    Node* e1 = node_create(0);
    Node* e2 = node_create(0);
    Node* e3 = node_create(0);
    Node* e4 = node_create(0);
    Node* e5 = node_create(0);
    Node* e6 = node_create(0);
    
    LIST_PUSH_BACK( nlist, e2 );
    LIST_PUSH_BACK( nlist, e3 );
    LIST_PUSH_BACK( nlist, e4 );
    LIST_PUSH_BACK( nlist, e5 );
    LIST_PUSH_BACK( nlist, e6 );
    LIST_PUSH_FRONT( nlist, e1 );
    LIST_PUSH_FRONT( nlist, e0 );

    n_list_print( nlist );

printf ("вставка 500 перед 3-м индексом:\n" );
    Node* e500 = node_create(500);
    LIST_INSERT( nlist, 3, e500 );
    n_list_print( nlist );

printf ("вставка 400 перед 0-м индексом:\n" );
    Node* e400 = node_create(400);
    LIST_INSERT( nlist, 0, e400 );
    n_list_print( nlist );

    LIST_ERASE( nlist, 3 );
    n_list_print( nlist );

printf ("list_at index==2: %d\n", LIST_AT( nlist, 2 )->num );
    n_list_print( nlist );

    free( LIST_POP_BACK( nlist  ) );
    free( LIST_POP_FRONT( nlist  ) );
    n_list_print( nlist );
    
    LIST_CLEAR ( nlist );
    n_list_print( nlist );
    Node* e7 = node_create(0);

    LIST_PUSH_FRONT( nlist, e7 );
    n_list_print( nlist );

    LIST_ERASE( nlist, 0 );
    n_list_print( nlist );

    Node_wr* w7 = node_wr_create(0);

    LIST_PUSH_FRONT( nlist, w7 );

    LIST_DELETE ( nlist );

}
#undef StoreData

int main ( int argc, char **argv )
{
    work_element();    
    printf("+++++++++++++++++++++++++++++++++++++\n");
    work_node();    

}
