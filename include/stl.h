#ifndef STL_H_
#define STL_H_

#include <stdio.h>
#include <stdlib.h>

//LIST

typedef struct list {
    void** items; //list of void pointers
    int capacity;
    int size;
} list;
 
void list_init(list*);
int list_size(list*);
static void list_resize(list*, int);
void list_add(list*, void*);
void list_set(list*, int, void*);
void *list_get(list*, int);
int list_max(list*);
void list_delete(list*, int);
void list_free(list*);
void list_swap(list*, int, int);
void list_sort(list*);

//STACK

typedef struct stack {
    void** items;
    int capacity;
    int size;
} stack;

void stack_init(stack* s);
static void stack_resize(stack* s, int capacity);
void stack_push(stack* s, void* item);
void* stack_top(stack* s);
void stack_pop(stack* s);
void stack_free(stack* s);


// //LIST
// // note: add sort() funcion in optimised way

// void list_init(list *v) {
//     v->capacity = 4;
//     v->size = 0;
//     v->items = malloc(sizeof(void *) * v->capacity);
// }
 
// int list_size(list *v) {
//     return v->size;
// }
 
// static void list_resize(list *v, int capacity) {
// #ifdef DEBUG_ON
//     printf("list_resize: %d to %d\n", v->capacity, capacity);
// #endif
 
//     void **items = realloc(v->items, sizeof(void *) * capacity);
//     if (items) {
//         v->items = items;
//         v->capacity = capacity;
//     }
// }
 
// void list_add(list *v, void *item) {
//     if (v->capacity == v->size)
//         list_resize(v, v->capacity * 2);
//     v->items[v->size++] = item;
// }
 
// void list_set(list *v, int index, void *item) {
//     if (index >= 0 && index < v->size)
//         v->items[index] = item;
// }
 
// void *list_get(list *v, int index) {
//     if (index >= 0 && index < v->size)
//         return v->items[index];
//     return NULL;
// }
 
// void list_delete(list *v, int index) {
//     if (index < 0 || index >= v->size)
//         return;
 
//     v->items[index] = NULL;
//     int i;
//     for (i = 0; i < v->size - 1; i++) {
//         v->items[i] = v->items[i + 1];
//         v->items[i + 1] = NULL;
//     }
 
//     v->size--;
 
//     if (v->size > 0 && v->size == v->capacity / 4)
//         list_resize(v, v->capacity / 2);
// }
 
// void list_free(list *v) {
//     free(v->items);
// }

// void list_swap(list* s, int i, int j) {
//     void* one = list_get(s, i);
//     void* two = list_get(s, j);
//     void* temp = one;
//     list_set(s, i, two);
//     list_set(s, j, temp);
// }

// void list_sort(list* s) {
//     int leng = s->size;
//     for (int i=0; i<leng-1; i++) {
//         for (int j=i+1; j<leng; j++) {
//             if (*((int*)list_get(s, i)) > *((int*)list_get(s, j))) {
//                 list_swap(s, i, j);
//             }
//         }
//     }
// }

// //STACK

// void stack_init(stack* s) {
//     s->capacity = 100;
//     s->size = 0;
//     s->items = malloc(sizeof(void *) * s->capacity);
// }
 
// static void stack_resize(stack* s, int capacity) {
// #ifdef DEBUG_ON
//     printf("list_resize: %d to %d\n", v->capacity, capacity);
// #endif
 
//     void** items = realloc(s->items, sizeof(void *) * capacity);
//     if (items) {
//         s->items = items;
//         s->capacity = capacity;
//     }
// }
 
// void stack_push(stack* s, void* item) {
//     if (s->capacity == s->size)
//         stack_resize(s, s->capacity * 2);
//     s->items[s->size++] = item;
// }
 
// void* stack_top(stack* s) {
//     return s->items[s->size-1];
// }
 
// void stack_pop(stack* s) {
//     s->items[s->size-1] = NULL;
//     s->size--;
 
//     if (s->size > 0 && s->size == s->capacity / 4)
//         stack_resize(s, s->capacity / 2);
// }
 
// void stack_free(stack* s) {
//     free(s->items);
// }

#endif
