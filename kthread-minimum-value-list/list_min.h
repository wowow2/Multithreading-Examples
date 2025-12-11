#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef LIST_MIN_H
#define LIST_MIN_H

typedef struct {
    int* array;
    int start;
    int end;
} ListMinArgs;

void* list_min(void* args);
void populate_input_txt(const char* filename, int* array, int size);


#endif // LIST_MIN_H