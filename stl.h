#ifndef STL_H_
#define STL_H_

#include <stdlib.h>
#include "structure.h"

//List
typedef struct list {
    void** items;
    int capacity;
    int total;
} list;
 
void list_init(list*);
int list_total(list*);
static void list_resize(list*, int);
void list_add(list*, void*);
void list_set(list*, int, void*);
void *list_get(list*, int);
void list_delete(list*, int);
void list_free(list*);

#endif