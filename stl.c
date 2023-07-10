#include "stl.h"

//LIST
// note: add sort() funcion in optimised way

void list_init(list *v) {
    v->capacity = 4;
    v->size = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}
 
int list_size(list *v) {
    return v->size;
}
 
static void list_resize(list *v, int capacity) {
#ifdef DEBUG_ON
    printf("list_resize: %d to %d\n", v->capacity, capacity);
#endif
 
    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}
 
void list_add(list *v, void *item) {
    if (v->capacity == v->size)
        list_resize(v, v->capacity * 2);
    v->items[v->size++] = item;
}
 
void list_set(list *v, int index, void *item) {
    if (index >= 0 && index < v->size)
        v->items[index] = item;
}
 
void *list_get(list *v, int index) {
    if (index >= 0 && index < v->size)
        return v->items[index];
    return NULL;
}
 
void list_delete(list *v, int index) {
    if (index < 0 || index >= v->size)
        return;
 
    v->items[index] = NULL;
    int i;
    for (i = 0; i < v->size - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }
 
    v->size--;
 
    if (v->size > 0 && v->size == v->capacity / 4)
        list_resize(v, v->capacity / 2);
}
 
void list_free(list *v) {
    free(v->items);
}

//STACK

void stack_init(stack* s) {
    s->capacity = 100;
    s->size = 0;
    s->items = malloc(sizeof(void *) * s->capacity);
}
 
static void stack_resize(stack* s, int capacity) {
#ifdef DEBUG_ON
    printf("list_resize: %d to %d\n", v->capacity, capacity);
#endif
 
    void** items = realloc(s->items, sizeof(void *) * capacity);
    if (items) {
        s->items = items;
        s->capacity = capacity;
    }
}
 
void stack_push(stack* s, void* item) {
    if (s->capacity == s->size)
        list_resize(s, s->capacity * 2);
    s->items[s->size++] = item;
}
 
void* stack_top(stack* s) {
    return s->items[s->size-1];
}
 
void stack_pop(stack* s) {
    s->items[s->size-1] = NULL;
    s->size--;
 
    if (s->size > 0 && s->size == s->capacity / 4)
        list_resize(s, s->capacity / 2);
}
 
void list_free(stack* s) {
    free(s->items);
}
