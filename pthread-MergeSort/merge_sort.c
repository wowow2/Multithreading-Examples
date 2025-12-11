#include "merge_sort.h"

void merge(int* array, int left, int mid, int right) {
    int p1 = mid - left + 1;
    int p2 = right - mid;

    int* L = (int*)malloc(p1 * sizeof(int));
    int* R = (int*)malloc(p2 * sizeof(int));

    for (int i = 0; i < p1; i++)
        L[i] = array[left + i];

    for (int j = 0; j < p2; j++)
        R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < p1 && j < p2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < p1) {
        array[k++] = L[i++];
    }

    while (j < p2) {
        array[k++] = R[j++];
    }

    free(L);
    free(R);
}

void* merge_sort(void* args) {
    MergeSortArgs* ms_args = (MergeSortArgs*)args;
    int left = ms_args->left;
    int right = ms_args->right;
    int* array = ms_args->array;

    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSortArgs left_args = {array, left, mid};
        MergeSortArgs right_args = {array, mid + 1, right};

        pthread_t left_thread, right_thread;

        // Create threads for left and right halves and run in parallel
        pthread_create(&left_thread, NULL, merge_sort, &left_args);
        pthread_create(&right_thread, NULL, merge_sort, &right_args);
        
        // Wait for both threads to finish
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        // Merge the sorted halves
        merge(array, left, mid, right);
    }

    return NULL;
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
    const int SIZE = 100; // Example size
    int array[SIZE];

    populate_input_txt("input.txt", array, SIZE);

    MergeSortArgs args = {array, 0, SIZE - 1};
    merge_sort(&args);

    // Print sorted array
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}