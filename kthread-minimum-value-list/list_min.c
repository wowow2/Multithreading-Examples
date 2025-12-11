#include "list_min.h"

void* list_min(void* args) {
    ListMinArgs* list_min_args = (ListMinArgs*)args;
    int* array = list_min_args->array;
    int start = list_min_args->start;
    int end = list_min_args->end;

    int local_min = array[start];
    for (int i = start + 1; i <= end; i++) {
        if (array[i] < local_min) {
            local_min = array[i];
        }
    }

    int* ret = malloc(sizeof(int));
    *ret = local_min;
    return ret;
}

void populate_input_txt(const char* filename, int* array, int size) {
    FILE* file = fopen(filename, "w");

    // populate with random integers
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000; // Random integers between 0 and 999
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);
}

int main() {
    int size = 1000;
    int k = 8; // number of threads 
    if (k > size) k = size;

    int* array = (int*)malloc(size * sizeof(int));
    populate_input_txt("input.txt", array, size);

    pthread_t threads[k];
    ListMinArgs args[k];

    int base = size / k;
    int rem = size % k;
    int idx = 0;
    for (int t = 0; t < k; t++) {
        int chunk = base + (t < rem ? 1 : 0);
        args[t].array = array;
        args[t].start = idx;
        args[t].end = idx + chunk - 1;
        idx += chunk;
        pthread_create(&threads[t], NULL, list_min, &args[t]);
    }

    int global_min = INT_MAX;
    for (int t = 0; t < k; t++) {
        void* res;
        pthread_join(threads[t], &res);
        int local = *(int*)res;
        free(res);
        if (local < global_min) global_min = local;
    }

    printf("Minimum value: %d\n", global_min);
    free(array);
    return 0;
}
