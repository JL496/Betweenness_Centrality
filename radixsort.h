#ifndef __RADIXSORT_H__
#define __RADIXSORT_H__

int getMax(int* a, int n);
void radix(int* arr, int* ord, int nodes, int thread_count);
void cSort(int* arr, int* ord, int nodes, int x);

#endif
