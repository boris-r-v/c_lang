/** \file list.h
 @brief Приватные вещи двухсвязного списка
*/

#include <stdio.h>	//for size_t

#ifndef TYPICAL_BI_LIST_PRIVATE
#define TYPICAL_BI_LIST_PRIVATE

typedef struct bilist_node_
{
    void * data;
    bilist_node *prev;
    bilist_node *next;
} bilist_node;

typedef struct bilist_
{
    size_t size;
    size_t data_size;
    bilist_node *head;
    bilist_node *tail;
} bilist;


#endif //TYPICAL_BI_LIST_PRIVATE