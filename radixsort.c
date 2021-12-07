#include <stdio.h>
#include "radixsort.h"

int getMax(int* arr, int nodes){
    int max = arr[0];
    for(int i = 1; i < nodes; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

void cSort(int* arr, int* ord, int nodes, int n){
    int out[nodes];
    int outord[nodes];
    int num[10];

    for(int i = 0; i < 10; i++){
        num[i] = 0;
    }
 
    for (int j = 0; j < nodes; j++){
        int calc = (arr[j]/n)%10;
        num[calc]++;
    }
 
    for (int k = 1; k < 10; k++){
        num[k] += num[k - 1];
    }
 
    for (int l = nodes - 1; l >= 0; l--){
        int place = num[(arr[l]/n)%10] - 1;
        out[place] = arr[l];
        outord[place] = ord[l];
        int calc = (arr[l]/n)%10;
        num[calc]--;
    }

    for (int m = 0; m < nodes; m++){
        arr[m] = out[m];
        ord[m] = outord[m];
    }
}
 
void radix(int* arr, int* ord, int nodes){
    int max = getMax(arr, nodes);

    for (int n = 1; max/n > 0; n *= 10){
        cSort(arr, ord, nodes, n);
    }
}