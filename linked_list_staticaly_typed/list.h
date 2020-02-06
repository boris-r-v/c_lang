/** \file list.h
 @brief Двухсвязный список допускающих хранение пользовательских структур данных

    По функционалу приближается, насколько это возможно к std::list, но написан на чистом С.
    Статистическая типизация, контроль упаковки данных использует директивы препроцессора.

    По сути, препоцессор текстовой заменой, создаст спискок хранения для требуемой структуры данных.
    Соответсвенно если попытаться укаковать струтуру не того типа будет ошибка компиляции

    Этот код:
    @code
    {				// Новый кодовый блок, ограничивающий время жизни списка
    	typedef struct 		// Структура хранимая в списке
	{
	    int num; 		// некоторые полезные данные
	} Curve;

	#define StoreData Curve		// Указали тип хранимых данных в списке

	#include "list.h"		// Создали список для хранения Curve

    	    ...				// Полезный код

	#undef StoreData		// Сбросили тип хранимых данных
    }
    @endcode
    Создаст список с типом Curve_List, хранящий елементы  Curve_ListNode, в которых зраняться указатели на структуру Curve  	

    @authors Boris Rozhkin borisrozhkin@gmail.com

    @bug Memory leaks in some operations
*/

/** @def CAT(X,Y)
    @brief Возвращает строку типа X_Y
*/

/** @def TEMPLATE(X,Y)
    @brief Формирует название методов работы со списком с указанным типом данных
*/

#ifndef TEMPLATES_H_
#define TEMPLATES_H_
#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)

#endif //TEMPLATES_H_

#ifdef StoreData	

#define T StoreData
#define LIST_NODE_GET_TYPE  TEMPLATE(T,list_node)
#define LIST_NODE_CREATE  TEMPLATE(T,list_node_create)
#define LIST_NODE_DATA  TEMPLATE(T,list_node_data)
#define LIST_GET_TYPE  TEMPLATE(T,list)
#define LIST_CREATE  TEMPLATE(T,list_create)
#define LIST_CLEAR  TEMPLATE(T,list_clear)
#define LIST_DELETE  TEMPLATE(T,list_delete)
#define LIST_PUSH_FRONT  TEMPLATE(T,list_push_front)
#define LIST_POP_FRONT  TEMPLATE(T,list_pop_front)
#define LIST_PUSH_BACK TEMPLATE(T,list_push_back)
#define LIST_POP_BACK TEMPLATE(T,list_pop_back)
#define LIST_GET_POS TEMPLATE(T,list_get_pos)
#define LIST_INSERT TEMPLATE(T,list_insert)
#define LIST_ERASE TEMPLATE(T,list_erase)
#define LIST_AT TEMPLATE(T,list_at)
#define LIST_BEGIN_NODE TEMPLATE(T,list_begin_node)
#define LIST_NEXT_NODE TEMPLATE(T,list_next_node)
#define LIST_SIZE TEMPLATE(T,list_size)

#ifndef RET_CODE
#define RET_CODE
/** 
@brief Возможные коды ошибок
* 
*/
enum RET_CODE
{ 
    RET_OK, 		//! Завершение вызова успешнео
    RET_WRONG_INDEX 	//! Ошибка, некоректный индекс элемента в списке
};

#endif // RET_CODE

/**
 @brief Элемент списка. (TEMPLATE макрос генерирующий имя из типа и _list_node)

    Содержит указатель на полезные данных и указатели на соседей.

    Если храним стуктуры Curve - то тип элемента списка будет: Curve_ListNode
	
*/
typedef struct TEMPLATE(T,_ListNode)
{
    T* data;				///< Указатель на полезные данные	

    struct TEMPLATE(T,_ListNode) *prev;	///< Указатель на предыдущей элемент списка

    struct TEMPLATE(T,_ListNode) *next;	///< Указатель на следующий элемиента списка

}LIST_NODE_GET_TYPE;

/**
 @brief Cписок. 

    (TEMPLATE макрос генерирующий имя из типа и _List)

    Если StoreData определено как: Curve то Curve_list.
*/
typedef struct TEMPLATE(T,_List) 
{
    unsigned size;			//! Количество элементов в списке
    LIST_NODE_GET_TYPE* head;		//! Указатель на первый элемент списка (голову списка)
    LIST_NODE_GET_TYPE* tail;		//! Указатель на последний элемент спика (хвост списка)
} LIST_GET_TYPE;



/** 
    @brief Создает пустой список

        LIST_CREATE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_create, но в коде для вызова использовать имя макроса.

    @return Указатель пустой список хранения элементов, указанных ранее в StoreData.
*/
LIST_GET_TYPE* LIST_CREATE( )
{
    LIST_GET_TYPE* list = (LIST_GET_TYPE*) malloc(sizeof(LIST_GET_TYPE) );
    list -> size = 0;
    list -> head = list->tail = NULL;
    return list;
}

/** 
    @brief Созданет элемент списка

        LIST_NODE_CREATE - это макрос создающий подходящее имя метода.

	Если StoreData определено как: Curve, то метод будет: Curve_list_node_create, но в коде для вызова использовать имя макроса.

    @param [in] _data - указатель на данные хранимые в этом элементе списка
    @return Указатель на созданный элемента списка
*/
LIST_NODE_GET_TYPE* LIST_NODE_CREATE( T* _data )
{
    LIST_NODE_GET_TYPE* ret = (LIST_NODE_GET_TYPE*) malloc(sizeof(LIST_NODE_GET_TYPE) );
    ret->data = _data;
    ret->prev = ret->next = NULL;
    return ret;
}

/** 
    @brief Возращает данные пользоватля из элемента списка

    @deprecated - ненужный метод

        LIST_NODE_DATA - это макрос создающий подходящее имя метода.

	Если StoreData определено как: Curve, то метод будет: Curve_list_node_data, но в коде для вызова использовать имя макроса.

    @param [in] _node - указатель на элемент списка
    @return Указатель на данные пользователя
*/
T* LIST_NODE_DATA( LIST_NODE_GET_TYPE* _node )
{
    return _node -> data;
}

/** 
    @brief Удаляет список вместе с данными пользовтеля

        LIST_DELETE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_delete, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список который нужно удалить
*/
void LIST_DELETE( LIST_GET_TYPE* _list )
{
    LIST_NODE_GET_TYPE *head = _list -> head;
    LIST_NODE_GET_TYPE *next = NULL;
    while( head )
    {	
	next = head->next;
	free( head->data ); 
	free( head );
	head = next;
    }
    free( _list );
    _list = NULL;
}

/** 
    @brief Очищает список, удалая данные пользовтеля

        LIST_CLEAR - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_clear, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список который нужно удалить
*/
void LIST_CLEAR( LIST_GET_TYPE* _list )
{
    LIST_NODE_GET_TYPE *head = _list -> head;
    LIST_NODE_GET_TYPE *next = NULL;
    while( head )
    {	
	next = head->next;
	free( head->data ); 
	free( head );
	head = next;
    }
    _list -> size = 0;
    _list -> head = _list->tail = NULL;
}

/** 
    @brief Вернет элемент списка в указанной позиции

        LIST_GET_POS - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_get_pos, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _index - индекс элемента, начиная с 0

    @return Указатель элемент списка или NULL - если такой позиции нет
*/
LIST_NODE_GET_TYPE* LIST_GET_POS( LIST_GET_TYPE* _list, int const _index )
{
    LIST_NODE_GET_TYPE* tmp = NULL;
    int pos = 0;
    for( tmp = _list->head; tmp && pos < _index; tmp = tmp->next, ++pos );
    return tmp; 
}

/** 
    @brief Добавляет элемент в начало списка

        LIST_PUSH_FRONT - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_push_front, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _data - указатель данные пользователя которые нужно упаковать
*/
void LIST_PUSH_FRONT(  LIST_GET_TYPE *_list, T *_data )
{

    LIST_NODE_GET_TYPE* node = LIST_NODE_CREATE(_data );
    
    if ( _list->head ) 
    {
	_list->head->prev = node;
        node->next = _list->head;
	_list->head = node;
    }
    else
    {
	_list->head = node;
	_list->tail = node;	//FIX ME - может 0 оставить
    }
    _list->size += 1;
}

/** 
    @brief Добавляет элемент в конец списка

        LIST_PUSH_BACK - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_push_back, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _data - указатель данные пользователя которые нужно упаковать
*/
void LIST_PUSH_BACK( LIST_GET_TYPE* _list, T *_data )
{
    LIST_NODE_GET_TYPE* node = LIST_NODE_CREATE(_data );
    if ( _list->tail )
    {
	_list->tail->next = node;
	node->prev = _list->tail;
	_list->tail = node;
    }
    else
    {
	_list->tail = node;
	_list->head = node;
    }
    
    _list->size += 1;
}


/** 
    @brief Вставки данные перед указанной позицией

        LIST_INSERT - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_insert, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _index - индекс элемента, начиная с 0, перед которым вставить данные
    @param [in] _data - данные которые упаковываем в список
    @return 1 если вставка неудачна или 0 - если удачна
*/
int LIST_INSERT( LIST_GET_TYPE* _list, int const _index, T* _data )
{
    LIST_NODE_GET_TYPE* find = LIST_GET_POS( _list, _index );
    if ( !find ) return RET_WRONG_INDEX; 

    LIST_NODE_GET_TYPE* node = LIST_NODE_CREATE(_data );
    LIST_NODE_GET_TYPE* prev_find = find->prev;
    if ( prev_find )
    {
	prev_find->next = node;
        node->prev = prev_find;
    }
    else
	_list->head = node;
    
    find->prev = node;
    node->next = find;
    ++_list->size;
    return RET_OK;	
}

/** 
    @brief Извлекает элемент из начала списка

        LIST_POP_FRONT - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_pop_front, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @return Указатель данные пользователя, извелеченные из списка, за удаление извлеченного ответственен код пользователя
*/
T* LIST_POP_FRONT(  LIST_GET_TYPE *_list )
{
    LIST_NODE_GET_TYPE* ret = _list->head;
    _list->head = ret->next;
    _list->head->prev = NULL;
    _list->size -= 1;
    T* data = ret->data;
    free( ret );
    return data;
}

/** 
    @brief Извлекает данные из конца списка

        LIST_POP_BACK - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_pop_back, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @return Указатель данные пользователя, извелеченные из списка, за удаление извлеченного ответственен код пользователя
*/
T* LIST_POP_BACK( LIST_GET_TYPE* _list )
{
    LIST_NODE_GET_TYPE* ret = _list->tail;
    _list->tail = ret->prev;
    _list->tail->next = NULL;
    ret->next = ret->prev = NULL;
    _list->size -= 1;
    T* data = ret->data;
    free(ret);
    return data;
}

/** 
    @brief Извлекает извелкает данные из указанной позиции списка

        LIST_AT - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_at, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _index - индекс элемента, начиная с 0.
*/
T* LIST_AT( LIST_GET_TYPE* _list, int _index )
{
    LIST_NODE_GET_TYPE* tmp = LIST_GET_POS( _list, _index );
    if ( !tmp ) return NULL; 
    
    return tmp->data;
}


/** 
    @brief Метод удаления элемента списка с данными пользовател

        LIST_ERASE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_erase, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список в который вставляем
    @param [in] _index - индекс элемента, начиная с 0, который надо удалить
    @return 1 если удаление несуществующего элемента или 0 - если удаление прошло успешно
*/
int LIST_ERASE( LIST_GET_TYPE* _list, int _index )
{
    LIST_NODE_GET_TYPE* tmp = LIST_GET_POS( _list, _index );
    if ( !tmp ) return RET_WRONG_INDEX; 
    
    LIST_NODE_GET_TYPE* tmp_next = tmp->next;
    LIST_NODE_GET_TYPE* tmp_prev = tmp->prev;
    if ( tmp_next )
	tmp_next->prev = tmp_prev;
    if ( tmp_prev )
	tmp_prev->next = tmp_next;

    free(tmp->data);
    free(tmp);
    --_list->size;
    if ( 0 == _list->size )
	_list->head = _list->tail = NULL;

    return RET_OK;
}


/** 
    @brief Метод доспута к началу списка

        LIST_BEGIN_NODE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_begin_node, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список
    @return Первый элемент списка
*/
LIST_NODE_GET_TYPE* LIST_BEGIN_NODE(LIST_GET_TYPE* _list)
{
    return _list->head;
}

/** 
    @brief Метод доспута к следующему элементу списка

        LIST_NEXT_NODE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_next_node, но в коде для вызова использовать имя макроса.

    @param [in] _node - указатель на текущий элемент
    @return Следующий элемент за текущим
*/
LIST_NODE_GET_TYPE* LIST_NEXT_NODE( LIST_NODE_GET_TYPE* _node)
{
    return _node->next;
}

/** 
    @brief Возвращает количество элементов в списке

        LIST_SIZE - это макрос создающий подходящее имя метода.

        Если StoreData определено как: Curve, то метод будет: Curve_list_size, но в коде для вызова использовать имя макроса.

    @param [in] _list - указатель на список
    @return Количество элементов в списке
*/
unsigned LIST_SIZE(LIST_GET_TYPE* _list)
{
    return _list->size;
}


#endif //E