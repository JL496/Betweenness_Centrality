#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minheap.h"

struct Node* addNode(int value, int distance){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->distance = distance;
    node->value = value;
    return node;
}
  
struct Heap* createHeap(int max){
    struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
    heap->pos = (int *)malloc(max * sizeof(int));
    heap->size = 0;
    heap->max = max;
    heap->arr = (struct Node**)malloc(max * sizeof(struct Node*));
    return heap;
}

void decrease(struct Heap* heap, int value, int distance){
    int a = heap->pos[value];
    int b = (a-1)/2;
    heap->arr[a]->distance = distance;
  
    while (a && heap->arr[a]->distance < heap->arr[b]->distance){
        heap->pos[heap->arr[a]->value] = b;
        heap->pos[heap->arr[b]->value] = a;
        swap(&heap->arr[a], &heap->arr[b]);
        a = b;
        b = (a-1)/2;
    }
}

struct Node* getMin(struct Heap* heap){
    if (isEmpty(heap)){
        return NULL;
    }
    
    int newsize = heap->size - 1;
    heap->size = newsize;
    struct Node* first = heap->arr[0];
    struct Node* last = heap->arr[newsize];
    heap->arr[0] = last;
    heap->pos[first->value] = newsize;
    heap->pos[last->value] = 0;
    heapify(heap, 0);
  
    return first;
}

void heapify(struct Heap* heap, int x){
    int s, one, two;
    s = x;
    one = 2*x + 1;
    two = 2*x + 2;
    bool changed = false;
  
    if (one < heap->size && heap->arr[one]->distance < heap->arr[s]->distance){
        s = one;
        changed = true;
    }
  
    if (two < heap->size && heap->arr[two]->distance < heap->arr[s]->distance){
        s = two;
        changed = true;
    }
  
    if (changed == true){
        Node *sNode = heap->arr[s];
        Node *xNode = heap->arr[x];
        heap->pos[sNode->value] = x;
        heap->pos[xNode->value] = s;
        swap(&heap->arr[s], &heap->arr[x]);
        heapify(heap, s);
    }
}
  
bool inHeap(struct Heap *heap, int value){
   if (heap->pos[value] < heap->size){
       return true;
   }
   return false;
}

bool isEmpty(struct Heap* heap){
    if (heap->size == 0){
        return true;
    } 
    return false;
}
  
void swap(struct Node** one, struct Node** two){
    struct Node* temp = *one;
    *one = *two;
    *two = temp;
}
