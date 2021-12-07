#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct Graph Graph;
typedef struct ANode ANode;
typedef struct AList AList;

struct ANode{
    int d;
    int weight;
    struct ANode* next;
};
  
struct AList{     
   struct ANode *head; 
};

struct Graph{
    int vertices;
    struct AList* arr;
};

struct ANode* addANode(int d, int weight);
struct Graph* newGraph(int verts);
void addEdge(struct Graph* graph, int s, int d);

#endif
