Реализация двухсвязанного списка на С.
Тип списка вычисляется на этапе компиляции, позволяет хранить структуры разных типов (как шаблоны в С++)

---------------------------------
ОГРАНИЧЕНИЕ: Работает в блоке ограниченным define и undef
#define E some_data_struct
#include "list.h"

    LIST_GET_TYPE *nlist = LIST_CREATE();
    Node* e1 = get_some_data_struct
    Node* e2 = get_some_data_struct
    Node* e3 = get_some_data_struct
    Node* e4 = get_some_data_struct
    
    LIST_PUSH_BACK( nlist, e1 );
    LIST_PUSH_BACK( nlist, e2 );
    LIST_PUSH_FRONT( nlist, e3 );
    LIST_PUSH_FRONT( nlist, e4 );
#undef E
Другими словами список шаблонный но его удобно использовать либо в отельном блоке либо в отдельном файле(единицы трансляции)
----------------------------

Документация: make doc -> ./doxygen/html/index.html

