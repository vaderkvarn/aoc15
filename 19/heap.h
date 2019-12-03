#include <stdlib.h>

typedef struct {
    char *val;
    size_t length;
    int n;
} Elem;

typedef struct {
    size_t length;
    size_t capacity;
    Elem *data;
} Heap;

void initHeap(Heap *h, size_t capacity);

void hPush(Heap *h, Elem e);

Elem hPop(Heap *h);