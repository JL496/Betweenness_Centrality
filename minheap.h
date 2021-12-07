#ifndef __MINHEAP_H__
#define __MINHEAP_H__

typedef struct Node Node;
typedef struct Heap Heap;

struct Node{
    int value;
    int distance;
};
  
struct Heap{
    int size;
    int max; 
    int *pos;    
    struct Node **arr;
};

struct Node* addNode(int value, int distance);
struct Heap* createHeap(int max);
void decrease(struct Heap* heap, int value, int distance);
struct Node* getMin(struct Heap* heap);
void heapify(struct Heap* heap, int id);
bool inHeap(struct Heap *heap, int value);
bool isEmpty(struct Heap* heap);
void swap(struct Node** a, struct Node** b);

#endif
