/** \file list.h
 @brief Двухсвязный список допускающих хранение пользовательских структур данных

    По функционалу приближается, насколько это возможно к std::list, но написан на чистом С.
    Статистическая типизация, отсутвует как класс данные храняться в виде void* 

    @authors Boris Rozhkin borisrozhkin@gmail.com

    @bug
*/

#ifndef TYPICAL_BI_LIST
#define TYPICAL_BI_LIST

typedef struct list_node_ list_node;
typedef list_node* list_iterator;
typedef struct list_ list;

list* list_create( );
void list_delete( list* );
int list_size( list const* );
int list_empty( list const* );
void list_push_back ( list*, void* );
void list_push_front ( list*, void* );
void* list_pop_back ( list* );
void* list_pop_front ( list* );
list_iterator list_begin( list* );
list_iterator list_end( list* );

#endif //TYPICAL_BI_LIST