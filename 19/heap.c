#include "heap.h"
#include <stdbool.h>

void initHeap(Heap *h, size_t capacity) {
    h->capacity = capacity;
    h->length = 0;
    h->data = malloc(capacity*sizeof(Elem));
}

void hPush(Heap *h, Elem e) {
    int next_pos = h->length;
    h->data[next_pos] = e;
    if (h->length == 0) {
        h->length++;
        return;
    }
    int parent_idx = next_pos/2;
    while (e.length < h->data[parent_idx].length) {
        //swap
        h->data[next_pos] = h->data[parent_idx];
        h->data[parent_idx] = e;
        next_pos = parent_idx;
        parent_idx = (next_pos-1)/2;
        if (next_pos == 0) {
            break;
        }
    }
    h->length++;
}

Elem hPop(Heap *h) {
    Elem ret = h->data[0];
    h->data[0] = h->data[h->length - 1]; 
    h->length--;
    int next_pos = 0;
    if (h->length == 0) {
        return ret;
    }
    int l_child = 1;
    int r_child = 2;

    while (true) { 
        int next = next_pos;
        if (l_child < h->length && h->data[l_child].length < h->data[next].length) {
            next = l_child;
        } 
        if (r_child < h->length && h->data[r_child].length < h->data[next].length) {
            next = r_child;
        }
        if (next == next_pos) break;
        Elem e = h->data[next];
        h->data[next] = h->data[next_pos];
        h->data[next_pos] = e;
        l_child = 2*next + 1;
        r_child = 2*next + 2;
        next_pos = next;
    }
    return ret;
}
