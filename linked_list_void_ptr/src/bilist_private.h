/** \file list.h
 @brief Двухсвязный список допускающих хранение пользовательских структур данных

    По функционалу приближается, насколько это возможно к std::list, но написан на чистом С.
    Статистическая типизация, отсутвует как класс данные храняться в виде void* 

    @authors Boris Rozhkin borisrozhkin@gmail.com

    @bug
*/

#ifndef TYPICAL_BI_LIST_PRIVATE
#define TYPICAL_BI_LIST_PRIVATE
typedef unsigned size_t; 
typedef struct list_node_
{
    void * data;
    list_node *prev;
    list_node *next;
} list_node;

typedef struct list_
{
    size_t size;
    list_node *head;
    list_node *tail;
} list;


#endif //TYPICAL_BI_LIST