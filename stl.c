#include "stl.h"

//LIST
void list_init(list *v) {
    v->capacity = 4;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}
 
int list_total(list *v) {
    return v->total;
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
    if (v->capacity == v->total)
        list_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}
 
void list_set(list *v, int index, void *item) {
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}
 
void *list_get(list *v, int index) {
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}
 
void list_delete(list *v, int index) {
    if (index < 0 || index >= v->total)
        return;
 
    v->items[index] = NULL;
    int i;
    for (i = 0; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }
 
    v->total--;
 
    if (v->total > 0 && v->total == v->capacity / 4)
        list_resize(v, v->capacity / 2);
}
 
void list_free(list *v) {
    free(v->items);
}
