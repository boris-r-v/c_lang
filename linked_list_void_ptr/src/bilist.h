/** \file bilist.h
 @brief Двухсвязный список допускающих хранение пользовательских структур данных

    По функционалу приближается, насколько это возможно к std::list, но написан на чистом С.
    Статистическая типизация, отсутвует как класс данные храняться в виде void* 
    
    Также в элементах списка лежат указатели на данные, при упаковки данных копирование не происходит.
    Если время жизни данных пользователя меньше времени жизни элемента списка - то поведение не определно.

    @authors Boris Rozhkin borisrozhkin@gmail.com

*/
#include <stdio.h>	//for size_t
#ifndef TYPICAL_BI_LIST
#define TYPICAL_BI_LIST

#define TRUE 1
#define FALSE 0

/** 
    \defgroup member_access_group Доступ к элементам списка
    Предоставляет доступ к данным хранимым в списке.
*/
/** 
    \defgroup iterators_group Итераторы списка
    Предоставлет доступ работы со списком в стиле STL
*/
/** 
    \defgroup modify_list_group Модификаторы списка
    Модифицирование списка
*/
/** 
    \defgroup create_list_group Создание списка
    Варианты создания списка
*/
/** 
    \defgroup capacity_list_group Ёмкость списка
    Доступ к емкости списка
*/


/** 
@brief Возможные коды ошибок
*
*	Используется в методах доступа к элементам списка по индексу
*/
enum RET_CODE_
{
    BILIST_OK, 		/**< Завершение вызова успешно */
    BILIST_WRONG_INDEX 	/**< Ошибка, некоректный индекс элемента в списке */
}RET_CODE;

/**
 @brief Элемент списка.
*/
typedef struct bilist_node_ bilist_node;
/**
 @brief Итератор списка.
*/
typedef bilist_node* bilist_iterator;
/**
 @brief Двунаправленый список.
*/
typedef struct bilist_ bilist;

/** 
    @ingroup create_list_group
    @brief Создает пустой список

    @return Указатель на пустой список.
*/
bilist* bilist_create( );

/** 
    @ingroup create_list_group
    @brief Создает список и наполняет его содержимым переданного массива

    @param [in] array - указатель на первый элемента массива
    @param [in] size - количество элементов в массиве
    @param [in] element_size - размер одного элемента массива в байтах
    @return Указатель на заполненный список.
*/
bilist* bilist_create2( void* array, size_t size, size_t element_size );
/** 
    @ingroup create_list_group
    @brief Удаляет список

    @param [in] list - список который удаляем
*/
void bilist_delete( bilist* list);
/** 
    @ingroup capacity_list_group
    @brief Возвращает количество элементов в списке

    @param [in] list - указатель на список
    @return Количество элементов в списке
*/
int bilist_size( bilist const* list );
/** 
    @ingroup capacity_list_group
    @brief Проверяет что список пустой

    @param [in] list - указатель на список
    @return 1 - если список пуст, 0 - если в нем есть данные
*/
int bilist_empty( bilist const* list );
/** 
    @ingroup modify_list_group
    @brief Добавляет данные в конец списка

    @param [in] list - указатель на список
    @param [in] data - указатель на обсласть памяти с данными которые будут скопированы в элемент списка
*/
void bilist_push_back ( bilist* list, void* data );
/** 
    @ingroup modify_list_group
    @brief Добавляет данные в начало списка

    @param [in] list - указатель на список
    @param [in] data - указатель на обсласть памяти с данными которые будут скопированы в элемент списка
*/
void bilist_push_front ( bilist* list, void* data );
/** 
    @ingroup modify_list_group
    @brief Добавляет данные в указанную позицию

    @param [in] list - указатель на список
    @param [in] data - указатель на обсласть памяти с данными которые будут скопированы в элемент списка
    @param [in] index - индекс элемента списка перед которым вставить данные
    
    @return BILIST_OK - в случае успеха, BILIST_WRONG_INDEX - если нет элемента с указанным индексом
*/
int bilist_insert ( bilist* list, void* data, size_t index );
/** 
    @ingroup modify_list_group
    @brief Извлекает данные с конца списка и удаляет последний элемент
    
    @param [in] list - указатель на список
    @return Указатель на данные
*/
void* bilist_pop_back ( bilist* list );
/** 
    @ingroup modify_list_group
    @brief Извлекает данные с начала списка и удаляет первый элемент
    
    @param [in] list - указатель на список
    @return Указатель на данные
*/
void* bilist_pop_front ( bilist* list );
/** 
    @ingroup member_access_group
    @brief Извлекает данные с указанной позиции
    
    @param [in] list - указатель на список
    @param [in] index - индекс элемента списка с которого забрать данные
    @return Указатель на данные
*/
void* bilist_at ( bilist* list, size_t index );
/** 
    @ingroup iterators_group
    @brief Вернет итератор, указывающий на первый элемент списка
    
    @param [in] list - указатель на список
    @return Итератор списка
*/
bilist_iterator bilist_begin( bilist* list );
/** 
    @ingroup iterators_group
    @brief Вернет итератор, указывающий на элемент списка, следующий за последним
    
    @param [in] list - указатель на список
    @return Итератор списка
*/
bilist_iterator bilist_end( bilist* list );
/** 
    @ingroup iterators_group
    @brief Вернет следующий итератор списка за указанным
    
    @param [in] it - итератор от которого надо взять следующий
    @return Итератор списка следующий за переданным в качестве параметра
*/
bilist_iterator bilist_next( bilist_iterator it );
/** 
    @ingroup iterators_group
    @brief Вернет итератор, указывающий на последний элемент списка
    
    @param [in] list - указатель на список
    @return Итератор списка
*/
bilist_iterator bilist_rbegin( bilist* list );
/** 
    @ingroup iterators_group
    @brief Вернет итератор, указывающий на элемент списка, предыдущий первому
    
    @param [in] list - указатель на список
    @return Итератор списка
*/
bilist_iterator bilist_rend( bilist* list );
/** 
    @ingroup iterators_group
    @brief Вернет предыдущий итератор списка от указанного
    
    @param [in] it - итератор от которого надо взять предыдущий
    @return Итератор списка предыдущий указаному
*/
bilist_iterator bilist_prev( bilist_iterator it );
/** 
    @ingroup member_access_group
    @brief Вернет итератор на данные хранимые в итераторе
    
	В терминах итераторов STL - разыменует итератор	

    @param [in] iterator списка
    @return Указатель на хранимые данные
*/
void* bilist_dereference( bilist_iterator iterator );
/** 
    @ingroup member_access_group
    @brief Вернет указатель на данные хранимые в первом элементе списка

    @param [in] list - указатель на список
    @return Указатель на хранимые данные
*/
void* bilist_front( bilist const* list );

/** 
    @ingroup member_access_group
    @brief Вернет указатель на данные хранимые в последнем элементе списка

    @param [in] list - указатель на список
    @return Указатель на хранимые данные
*/
void* bilist_back( bilist const* list );

#endif //TYPICAL_BI_LIST