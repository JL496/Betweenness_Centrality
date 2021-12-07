#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct ANode* addANode(int d, int weight){
    struct ANode* newNode = (struct ANode*)malloc(sizeof(struct ANode));
    newNode->d = d;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* newGraph(int verts){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = verts;
    graph->arr = (struct AList*)malloc(verts * sizeof(struct AList));
    for (int i = 0; i < verts; ++i){
        graph->arr[i].head = NULL;
    }
    return graph;
}
  
void addEdge(struct Graph* graph, int s, int d){
    int w = 1;
    struct ANode* an = graph->arr[s].head;
    while (an != NULL){
        int v = an->d;
        if(v == d){
            w = an->weight + 1;
            an->weight = an->weight + 1;
            return;
        }
        an = an->next;
    }
    struct ANode* new = addANode(d, w);
    new->next = graph->arr[s].head;
    graph->arr[s].head = new;
}
