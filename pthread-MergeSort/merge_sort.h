#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

typedef struct {
    int* array;
    int left;
    int right;
} MergeSortArgs;

void* merge_sort(void* args);
void merge(int* array, int left, int mid, int right);

#endif // MERGE_SORT_H