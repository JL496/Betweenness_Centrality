#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>
#include <stdbool.h>
#include "dijkstra.h"
#include "graph.h"
#include "subreddits.h"
#include "radixsort.h"
#ifdef _OPENMP
# include <omp.h>
#endif

int main(int argc, char* argv[]){
    const double time0 = omp_get_wtime();

    const int thread_count = strtol(argv[1], NULL, 10);
    const int num_nodes = 35775; //35775
    
    char* filename = "soc-redditHyperlinks-body.tsv";
    FILE* file = fopen(filename,"r");

    struct Graph* graph = newGraph(num_nodes);
    char * source = NULL;
    char * dest = NULL;
    char buf[3000];
    fgets(buf, 3000, file);

    int totals[num_nodes];
    int order[num_nodes];

    subreddit* head = NULL;
    int src_loc = -1;
    int des_loc = -1;

    char names[num_nodes][22];
    const double time1 = omp_get_wtime();
    while(fgets(buf,3000,file) != NULL){
    //for(int i = 0; i < 400; i++){
        dest = NULL;
        source = NULL;
        fgets(buf, 3000, file);
        source = strtok(buf, "\t");
        dest = strtok(NULL, "\t");
        if(head != NULL){
            src_loc = SearchList(head, source);
        }
        if(src_loc == -1){
            src_loc = AddItem(&head, source);
            strcpy(names[src_loc], source);
        }
        if(head != NULL){
            des_loc = SearchList(head, dest);
        }
        if(des_loc == -1){
            des_loc = AddItem(&head, dest);
            strcpy(names[des_loc], dest);
        }
        addEdge(graph, src_loc, des_loc);
    }
    const double time2 = omp_get_wtime();

    for(int j = 0; j < num_nodes; j++){
        totals[j] = 0;
        order[j] = j;
    }
    const double time3 = omp_get_wtime();

    #pragma omp parallel for num_threads(thread_count)
    for(int i = 0; i < num_nodes; i++){
        dijkstra(graph, i, totals);
    }
    const double time4 = omp_get_wtime();

    radix(totals, order, num_nodes);
    const double time5 = omp_get_wtime();

    for(int i = num_nodes-20; i < num_nodes; i++){
        printf("%s: %d\n", names[order[i]], totals[i]);
    }
    const double time6 = omp_get_wtime();
    printf("Read Time: %12.5e\nShortest Path Time: %12.5e\nSort Time: %12.5e\nTotal Time: %12.5e\n", time2-time1, time4-time3, time5-time4,time6-time0);


    fclose(file);

    return 0;
}
