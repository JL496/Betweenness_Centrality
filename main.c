#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
//#include "hash.h"
//#include "node.h"
#include "subreddits.h"
#ifdef _OPENMP
# include <omp.h>
#endif

//struct Edge {
//    int src, dest, weight;
//};


int main(int argc, char* argv[]){

    //const int thread_count = strtol(argv[1], NULL, 10);
    //const int N = strtol(argv[2], NULL, 10);
    char* filename = "soc-redditHyperlinks-body.tsv";
    FILE* file = fopen(filename,"r");

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    //int nds[55863][55863];
    const int num_nodes = 55863;
    int nds[num_nodes][num_nodes];
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            nds[i][j] = 0;
        }
    }
    char * source = NULL;
    char * dest = NULL;
    read = getline(&line, &len, file);

    subreddit* head = NULL;
    int src_loc = -1;
    int des_loc = -1;

    for(int i = 0; i < 858490; i++){
        dest = NULL;
        source = NULL;
        read = getline(&line, &len, file);
        printf("Retrieved line of length %zu:\n", read);
        source = strtok(line, "\t");
        dest = strtok(NULL, "\t");
        if(head != NULL){
            src_loc = SearchList(head, source);
        }
        if(src_loc == -1){
            src_loc = AddItem(&head, source);
        }
        if(head != NULL){
            des_loc = SearchList(head, dest);
        }
        if(des_loc == -1){
            des_loc = AddItem(&head, dest);
        }
        nds[src_loc][des_loc] += 1;
    }

    Print(head);

    printf("value: %d\n", SearchList(head, "hi"));
    printf("value: %d\n", SearchList(head, "aww"));

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            printf("%d", nds[i][j]);
        }
        printf("\n");
    }

    fclose(file);

    return 0;
}
