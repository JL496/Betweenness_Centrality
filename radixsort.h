#ifndef __RADIXSORT_H__
#define __RADIXSORT_H__

int getMax(int* a, int n);
void radix(int* arr, int* ord, int nodes);
void cSort(int* arr, int* ord, int nodes, int x, int thread_count);

#endif
