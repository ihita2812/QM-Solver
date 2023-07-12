#include "stl.h"

//LIST
// note: add sort() funcion in optimised way

void list_init(list* v) {
    // printf("init started\n");
    v->capacity = 1;
    v->size = 0;
    v->items = malloc(sizeof(void*));
    // if (v->items) printf("init complete\n");
    // else printf("init failed\n");
}

int list_size(list* v) {
    return v->size;
}

static void list_resize(list* v, int capacity) {
#ifdef DEBUG_ON
    printf("list_resize: %d to %d\n", v->capacity, capacity);
#endif
 
    void** items = realloc(v->items, sizeof(void*) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    } else {
        printf("resize failed\n");
    }
}

void list_add(list* v, void* item) {
    // printf("adding %d to list\npointer values is %p\n", *((unsigned int*)item), item);
    if (v->capacity == v->size) {
        // printf("resizing list\n");
        list_resize(v, v->capacity * 2);
        // printf("resized list to %d\n", v->capacity);
    }
    *(v->items+(v->size++)) = item;
    // printf("%u added to list\n", *(unsigned int*)item);
}

void list_set(list *v, int index, void *item) {
    if (index >= 0 && index < v->size)
        v->items[index] = item;
    // printf("\nDEBUG: list_set was called\n");
}

void* list_get(list* v, int index) {
    // printf("\nDEBUG: list_get was called\n");
    if (index >= 0 && index < v->size) {
        // printf("pointer is %p\n", v->items[index]);
        // printf("got value %u\n", *((unsigned int*)v->items[index]));
        return v->items[index];
    }
    else {
        // printf("listget failed\n");
        return NULL;
    }
}

void list_delete(list *v, int index) {
    // printf("\nDEBUG: list_delete was called\n");
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

void list_swap(list* s, int i, int j) {
    void* one = list_get(s, i);
    void* two = list_get(s, j);
    void* temp = one;
    list_set(s, i, two);
    list_set(s, j, temp);
}

void list_sort(list* s) {
    printf("\nDEBUG: list_sort was called\n");
    int leng = s->size;
    for (int i=0; i<leng-1; i++) {
        for (int j=i+1; j<leng; j++) {
            if (*((int*)list_get(s, i)) > *((int*)list_get(s, j))) {
                list_swap(s, i, j);
            }
        }
    }
}

//STACK

void stack_init(stack* s) {
    s->capacity = 1;
    s->size = 0;
    s->items = malloc(sizeof(void *));
    if (s->items) printf("init complete\n");
    else printf("init failed\n");
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
        stack_resize(s, s->capacity * 2);
    s->items[s->size++] = item;
}

void* stack_top(stack* s) {
    return s->items[s->size-1];
}

void stack_pop(stack* s) {
    s->items[s->size-1] = NULL;
    s->size--;
 
    if (s->size > 0 && s->size == s->capacity / 4)
        stack_resize(s, s->capacity / 2);
}

void stack_free(stack* s) {
    free(s->items);
}
