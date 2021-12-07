#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "dijkstra.h"
#include "minheap.h"
#include "graph.h"
  
void dijkstra(struct Graph* graph, int z, int* locs){
    int verts = graph->vertices;
    struct Heap* aHeap = createHeap(verts);
    int dist[verts]; 
    int nods[verts];    

    #pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < verts; i++){
        dist[i] = INT_MAX;
        nods[i] = -1;
        aHeap->pos[i] = i;
        aHeap->arr[i] = addNode(i, dist[i]);
    }

    aHeap->pos[z] = z;
    aHeap->arr[z] = addNode(z, dist[z]);
    dist[z] = 0;
    decrease(aHeap, z, dist[z]);
    aHeap->size = verts;

    while (!isEmpty(aHeap)){
        struct Node* node = getMin(aHeap);
        int x = node->value;
        struct ANode* al = graph->arr[x].head;

        while (al != NULL){
            int y = al->d;
            if (inHeap(aHeap, y) && dist[x] > dist[y] + al->weight && dist[x] != INT_MAX){
                dist[y] = dist[x] + al->weight;
                nods[y] = x;
                decrease(aHeap, y, dist[y]);
            }
            al = al->next;
        }
    }

    #pragma omp parallel for num_threads(thread_count)
    for(int i = 0; i < verts; i++){
        int a = nods[i];
        while(a != -1 && a != z && a != INT_MAX){
            locs[a] += 1;
            int temp = nods[a];
            a = temp;
        }
    }
}